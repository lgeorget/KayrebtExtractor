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

#include "cgrapher4gcc.h"
#include "expr_factory.h"
#include "expression.h"
#include "dumper.h"
#include "text_dumper.h"
#include "activity_graph_dumper.h"
#include "bad_tree_exception.h"
#include "bad_gimple_exception.h"

int plugin_is_GPL_compatible;

extern "C" {

static struct plugin_info myplugin_info =
{
	"0.0.1", // version
	"Later...", //help
};

static struct plugin_gcc_version myplugin_version =
{
	"4.8.3", //basever
	"", // datestamp
	"", // devphase
	"", // revision
	"", // configuration arguments
};

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

extern "C" int plugin_init (struct plugin_name_args *plugin_args,
                        struct plugin_gcc_version *version)
{
	if (strcmp(version->basever,myplugin_version.basever) != 0) {
		return -1; // incompatible
	}

	struct register_pass_info actdiag_extractor_pass_info = {
		.pass				= &actdiag_extractor_pass.pass,
		.reference_pass_name		= "cfg",
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

static void walk_through_current_fn(Dumper& dumper)
{

	unsigned i;
	const_tree str, op;
	gimple stmt;
	gimple_stmt_iterator gsi;

	try {
		std::shared_ptr<FunctionBody> e = ExprFactory::INSTANCE.build(cfun);
		e->accept(dumper);
	} catch(BadTreeException& e) {
		std::cerr << "***Error detected***\n" <<
			e.what() << std::endl;
		throw e;
	}
}

static bool look_for_target(const char* current_fn, const char* filename)
{
	std::ifstream fns(filename);
	bool found = false;
	std::string fn;
	while (fns && !fns.eof() && !found) {
		fns >> fn;
		std::cerr << "Comparing " << fn << " against " << current_fn << std::endl;
		found = strcmp(current_fn, fn.data()) == 0;
	}
	fns.close();
	return found;
}

extern "C" unsigned int actdiag_extractor ()
{
  // If there were errors during compilation,
  // let GCC handle the exit.
  //
  if (errorcount || sorrycount)
    return 0;

  // Name of the function currently being parsed
  const char* name = function_name(cfun);
  bool found = false;
  bool graph = true;
  for (unsigned int i=0 ; i<functions->argc && (!found || graph) ; i++) {
	if (strcmp(functions->argv[i].key, "fn") == 0)
		found = strcmp(name,functions->argv[i].value) == 0;
	else if (strcmp(functions->argv[i].key, "text") == 0)
		graph = false;
	else if (strcmp(functions->argv[i].key,"fn_list") == 0)
		found = look_for_target(name, functions->argv[i].value);
  }

  if (found)
  {
	  std::ofstream out(std::string(main_input_filename) + ".dump", std::ofstream::app);
	  if (!out) {
		  std::cerr << "Couldn't open dump file, skipping." << std::endl;
		  return 0;
	  }

	  out << "Function " << name << std::endl;
	  if (graph) {
		  auto dumper = ActivityGraphDumper();
		  walk_through_current_fn(dumper);
		  out << dumper.graph();
	  } else {
		  auto dumper = TextDumper(&out);
		  walk_through_current_fn(dumper);
	  }
	  out << std::endl << "-------------------------" << std::endl << std::endl;
	  out.close();
  }

  return 0;
}

extern "C" void prepare_dump_file (void*, void*)
{
  std::cerr << "processing " << main_input_filename << std::endl;

  std::ofstream out(std::string(main_input_filename) + ".dump", std::ofstream::trunc);
  if (!out)
	  std::cerr << "Couldn't open dump file." << std::endl;
}


