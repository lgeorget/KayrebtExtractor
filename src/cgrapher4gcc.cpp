/**
 * \file cgrapher4gcc.cpp
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Entry point of the plugin
 */
#include <iostream>
#include <fstream>
#include <string>

#include <gcc-plugin.h>

#include <config.h>
#include <system.h>
#include <coretypes.h>
#include <tree.h>
#include <tree-pass.h>
#include <intl.h>

#include <tm.h>
#include <diagnostic.h>

#include <function.h>
#include <tree-iterator.h>
#include <gimple.h>

#include "expr_factory.h"
#include "expression.h"
#include "dumper.h"
#include "activity_graph_dumper.h"
#include "bad_tree_exception.h"
#include "bad_gimple_exception.h"

/**
 * \brief Must-be-defined value for license compatibility
 */
int plugin_is_GPL_compatible;

extern "C" {
static unsigned int actdiag_extractor();

/**
 * \brief Basic information about the plugin
 */
static struct plugin_info myplugin_info =
{
	"0.2", // version
	"Later...", //help
};

/**
 * \brief Plugin version information
 */
static struct plugin_gcc_version myplugin_version =
{
	"4.8.3", //basever
	"2015-03-03", // datestamp
	"alpha", // devphase
	"", // revision
	"", // configuration arguments
};

/**
 * \brief Definition of the new pass added by the plugin
 */
struct gimple_opt_pass actdiag_extractor_pass =
{
	{
		GIMPLE_PASS, /* type */
		"activity diagram extractor", /* name */
		OPTGROUP_NONE, /* optinfo_flags */
		NULL, /* gate */
		actdiag_extractor, /* execute */
		NULL, /* sub */
		NULL, /* next */
		0, /* static_pass_number */
		TV_NONE, /* tv_id */
		PROP_gimple_any, /* properties_required */
		0, /* properties_provided */
		0, /* properties_destroyed */
		0, /* todo_flags_start */
		0, /* todo_flags_finish */
	}
};

}

static struct plugin_name_args* functions;

/**
 * \brief Attempt to open the file where everything must be dumped
 *
 * If something goes wrong, the error is actually caught later.
 */
static void prepare_dump_file (void*, void*)
{
  std::cerr << "processing " << main_input_filename << std::endl;

  std::ofstream out(std::string(main_input_filename) + ".dump", std::ofstream::trunc);
  if (!out)
	  std::cerr << "Couldn't open dump file." << std::endl;
}


/**
 * \brief Plugin entry point
 * \param plugin_args the command line options passed to the plugin
 * \param version the plugin version information
 * \return 0 if everything went well, -1 if the plugin is incompatible with
 * the active version of GCC
 */
extern "C" int plugin_init (struct plugin_name_args *plugin_args,
                        struct plugin_gcc_version *version)
{
	if (strcmp(version->basever,myplugin_version.basever) != 0) {
		return -1; // incompatible
	}

	struct register_pass_info actdiag_extractor_pass_info = {
		.pass				= &actdiag_extractor_pass.pass,
		.reference_pass_name		= "ssa",
		.ref_pass_instance_number	= 1,
		.pos_op				= PASS_POS_INSERT_BEFORE
	};

	functions = plugin_args;

	register_callback("actdiag_extraction",
			PLUGIN_PASS_MANAGER_SETUP,
			NULL,
			&actdiag_extractor_pass_info);
	register_callback("prepare_dump_file",
			PLUGIN_START_UNIT,
			&prepare_dump_file,
			NULL);

	return 0;
}

/**
 * \brief Build the activity diagram for the function currently being compiled
 * \param dumper the object building the activity diagram
 */
static void walk_through_current_fn(Dumper& dumper)
{
	try {
#ifndef NDEBUG
		std::cerr << "Walking through the function" << std::endl;
#endif
		std::shared_ptr<FunctionBody> e = ExprFactory::INSTANCE.build(cfun);
		e->accept(dumper);
	} catch(BadTreeException& e) {
		std::cerr << "***Error detected***\n" << e.what() << std::endl;
		throw e;
	}
}

/**
 * \brief Check in the functions list whether the current function is to be
 * graphed
 * \param current_fn the current function name
 * \param filename the file containing the functions to graph, this is a
 * parameter that can be passed to the plugin
 * \return true if and only if the function must be graphed
 */
static bool look_for_target(const char* current_fn, const char* filename)
{
	std::ifstream fns(filename);
	bool found = false;
	std::string fn;
	while (fns && !fns.eof() && !found) {
		fns >> fn;
#ifndef NDEBUG
		std::cerr << "Comparing " << fn << " against " << current_fn << std::endl;
#endif
		found = strcmp(current_fn, fn.data()) == 0;
	}
	fns.close();
#ifndef NDEBUG
	std::cerr << "Graphing " << current_fn << ": " << std::boolalpha << found << std::endl;
#endif
	return found;
}

/**
 * \brief Extract an activity diagram for every function reached if a graph
 * is asked for it
 *
 * If there is a compilation error, no graph is produced.
 * \return 0 even if there is an error, in order to build as many graphs as
 * possible without making GCC crash
 */
extern "C" unsigned int actdiag_extractor()
{
  // If there were errors during compilation,
  // let GCC handle the exit.
  //
  if (errorcount || sorrycount)
    return 0;

  // Name of the function currently being parsed
  const char* name = function_name(cfun);
#ifndef NDEBUG
  std::cerr << "Reached: " << name << std::endl;
#endif
  bool found = false;
  for (unsigned int i=0 ; i<functions->argc && !found ; i++) {
	if (strcmp(functions->argv[i].key, "fn") == 0)
		found = strcmp(name,functions->argv[i].value) == 0;
	else if (strcmp(functions->argv[i].key,"fn_list") == 0)
		found = look_for_target(name, functions->argv[i].value);
  }
#ifndef NDEBUG
  std::cerr << "Found: " << std::boolalpha << found << std::endl;
#endif

  if (found)
  {
	  std::ofstream out(std::string(main_input_filename) + ".dump", std::ofstream::app);
	  if (!out) {
		  std::cerr << "Couldn't open dump file, skipping." << std::endl;
		  return 0;
	  }

	  std::cerr << "Trying to graph function " << name << std::endl;
	  out << "Function " << name << std::endl;
#ifndef NDEBUG
	  std::cerr << "Initializing the dumper" << std::endl;
#endif
	  auto dumper = ActivityGraphDumper();
#ifndef NDEBUG
	  std::cerr << "Dumper initialized" << std::endl;
#endif
	  walk_through_current_fn(dumper);
	  out << dumper.graph();

	  out << std::endl << "-------------------------" << std::endl << std::endl;
	  out.close();
  }

  return 0;
}


