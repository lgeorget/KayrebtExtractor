#include <iostream>
#include <fstream>
#include <string>

#include <gcc-plugin.h>

#include <config.h>
#include <system.h>
#include <coretypes.h>
#include <tree.h>
#include <intl.h>

#include <c-tree.h>
#include <c-family/c-common.h>
#include <c-family/c-pragma.h>
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

struct gimple_opt_pass actdiag_extractor = {
	{
		.type			= GIMPLE_PASS,
		.name			= "activity diagram extractor",
		.gate			= NULL,
		.execute		= actdiag_extractor,
		.sub			= NULL,
		.next			= NULL,
		.static_pass_number	= 0,
		.tv_id			= TV_NONE,
		.properties_required	= 0,
		.properties_provided	= 0,
		.properties_destroyed	= 0,
		.todo_flags_start	= 0,
		.todo_flags_finish	= 0
};

}


extern "C" int plugin_init (struct plugin_name_args *plugin_info,
                        struct plugin_gcc_version *version)
{
	if (strcmp(version->basever,myplugin_version.basever) != 0) {
		return -1; // incompatible
	}

	struct register_pass_info local_variable_pass_info = {
		.pass				= &actdiag_extractor.pass,
		.reference_pass_name		= "pass_build_cfg",
		.ref_pass_instance_number	= 0,
		.pos_op				= PASS_POS_INSERT_AFTER
	};

	register_callback(plugin_info->base_name,
			PLUGIN_PASS_MANAGER_SETUP,
			&gate_callback,
			(void*) plugin_info);
	register_callback(plugin_info->base_name,
			PLUGIN_START_UNIT,
			&prepare_dump_file,
			0);

	return 0;
}

static void walk_through_current_fn(Dumper& dumper)
{

	unsigned i;
	const_tree str, op;
	basic_block bb;
	gimple stmt;
	gimple_stmt_iterator gsi;

	try {
		FOR_EACH_BB(bb) {
			std::shared_ptr<Expression> e = ExprFactory::INSTANCE.build(bb);
			e->accept(dumper);
		}
	} catch(BadTreeException& e) {
		std::cerr << "***Error detected***\n" <<
			e.what() << std::endl;
		throw e;
	}
}

extern "C" void actdiag_extractor (void, void* plugin_args)
{
  // If there were errors during compilation,
  // let GCC handle the exit.
  //
  if (errorcount || sorrycount)
    return;

  // Name of the function currently being parsed
  const char* name = function_name(cfun);
  bool found = false;
  for (unsigned int i=0 ; i<functions->argc && !found ; i++) {
	found = strcmp(name,functions->argv[i].key) == 0;
  }

  if (found)
  {
	  std::ofstream out(std::string(main_input_filename) + ".dump", std::ofstream::app);
	  if (!out) {
		  std::cerr << "Couldn't open dump file, skipping." << std::endl;
		  return;
	  }

	  out << "Function " << name << std::endl;
	  auto dumper = ActivityGraphDumper();
	  walk_through_current_fn(dumper);
	  out << dumper.graph();
	  out << std::endl << "-------------------------" << std::endl << std::endl;
	  out.close();
  }
}

extern "C" void prepare_dump_file (void*, void*)
{
  std::cerr << "processing " << main_input_filename << std::endl;

  std::ofstream out(std::string(main_input_filename) + ".dump", std::ofstream::trunc);
  if (!out)
	  std::cerr << "Couldn't open dump file." << std::endl;
}


