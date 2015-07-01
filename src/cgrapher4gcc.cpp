/**
 * \file cgrapher4gcc.cpp
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Entry point of the plugin
 */
#include <iostream>
#include <fstream>
#include <string>

#include "configurator.h"

#include <gcc-plugin.h>

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
	static std::unique_ptr<Configurator> global_config;

	/**
	 * \brief Basic information about the plugin
	 */
	static struct plugin_info myplugin_info =
	{
		"1.0", // version
		"KayrebtDumper: a GCC plugin to dump activity graphs from C functions", //help
	};

	/**
	 * \brief Plugin version information
	 */
	static struct plugin_gcc_version myplugin_version =
	{
		"4.8", //basever
		"2015-05-15", // datestamp
		"beta", // devphase
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
 * \brief Attempt to open and troncate the file where everything must be dumped
 * and parse configuration file
 *
 * If something goes wrong when opening the dump file, the error will be caught
 * again later, and we don't want to make GCC crash altogether. However, if the
 * configuration file is not found, this is a fatal error and we do want GCC to
 * crash.
 */
static void prepare_dumping(void*, void*)
{
	std::cerr << "processing " << main_input_filename << std::endl;

	std::ofstream out(std::string(main_input_filename) + ".dump", std::ofstream::trunc);
	if (!out) {
		std::cerr << "Couldn't open dump file." << std::endl;
	}

	std::string configFile = "config";
	bool found = false;
	for (unsigned int i=0 ; i<functions->argc && !found ; i++) {
		if (strcmp(functions->argv[i].key, "config_file") == 0) {
			configFile = functions->argv[i].value;
			found = true;
		} else {
			std::cerr << "Discarded unknown parameter: " << functions->argv[i].key << std::endl;
		}
	}

	std::ifstream config(configFile);
	if (!config) {
		std::cerr << "Couldn't open config file \"" << configFile << "\", fatal error." << std::endl;
	} else {
		global_config.reset(new Configurator(configFile, main_input_filename));
	}
	config.close();
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
	// Check that GCC base version starts with "4.8"
	if (strncmp(version->basever,myplugin_version.basever,3) != 0) {
		std::cerr << "Sadly, the KayrebtExtractor GCC plugin is only "
			"available for GCC 4.8 for now." << std::endl;
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
			&prepare_dumping,
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
 * \brief Extract an activity diagram for every function reached if a graph
 * is asked for it
 *
 * If there is a compilation error, no graph is produced.
 * \return 0 even if there is an error, in order to build as many graphs as
 * possible without making GCC crash, except if the error is global (missing
 * configuration file...)
 */
extern "C" unsigned int actdiag_extractor()
{
	// If there were errors during compilation,
	// let GCC handle the exit.
	if (errorcount || sorrycount)
		return 0;

	if (!global_config) {
		std::cerr << "Configuration not found!" << std::endl;
		return -1;
	}

	// Name of the function currently being parsed
	const char* name = function_name(cfun);
#ifndef NDEBUG
	std::cerr << "Reached: " << name << std::endl;
#endif
	bool found = global_config->mustGraph(name);
#ifndef NDEBUG
	std::cerr << "Must be graphed: " << std::boolalpha << found << std::endl;
#endif

	if (found)
	{
		std::ofstream out(std::string(main_input_filename) + ".dump", std::ofstream::app);
		if (!out) {
			std::cerr << "Couldn't open dump file, skipping." << std::endl;
			return 0;
		} else {
#ifndef NDEBUG
			std::cerr << "Dumping into " << main_input_filename << ".dump" << std::endl;
#endif
		}

		std::cerr << "Trying to graph function " << name << std::endl;
		out << "Function " << name << std::endl;
#ifndef NDEBUG
		std::cerr << "Initializing the dumper" << std::endl;
#endif
		auto dumper = ActivityGraphDumper(*global_config);
#ifndef NDEBUG
		std::cerr << "Dumper initialized" << std::endl;
#endif
		walk_through_current_fn(dumper);
		dumper.graph().graphVizify(out, global_config->getCategoryDumper());

		out << "\n-------------------------" << std::endl;
		out.close();
	}

	return 0;
}


