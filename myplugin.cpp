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

#include <tree-iterator.h>

#include "myplugin.h"
#include "expr_factory.h"
#include "expression.h"
#include "dumper.h"
#include "activity_graph_dumper.h"
#include "bad_tree_exception.h"

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

}


extern "C" int plugin_init (struct plugin_name_args *plugin_info,
                        struct plugin_gcc_version *version)
{
	if (strcmp(version->basever,myplugin_version.basever) != 0) {
		return -1; // incompatible
	}

	// Disable assembly output.
	//
//	asm_file_name = HOST_BIT_BUCKET;

	// Register callbacks.
	//
	register_callback(plugin_info->base_name,
			PLUGIN_PRE_GENERICIZE,
			&gate_callback,
			(void*) plugin_info);
	register_callback(plugin_info->base_name,
			PLUGIN_START_UNIT,
			&prepare_dump_file,
			0);

	return 0;
}

extern "C" void walk_through(tree decl, Dumper& dumper)
{
	tree subdecl = BIND_EXPR_BODY(DECL_SAVED_TREE(decl));

	std::shared_ptr<Expression> e = ExprFactory::INSTANCE.build(subdecl);
	try {
		e->accept(dumper);
	} catch(BadTreeException& e) {
		std::cerr << "***Error detected***\n" <<
			e.what() << std::endl;
		throw e;
	}
}

extern "C" void gate_callback (void* arg, void* plugin_args)
{
  // If there were errors during compilation,
  // let GCC handle the exit.
  //
  if (errorcount || sorrycount)
    return;

  tree decl = (tree) arg;
  struct plugin_name_args* functions = (struct plugin_name_args*) plugin_args;

  int tc = TREE_CODE(decl);
  tree id = DECL_NAME(decl);
  const char* name (id ? IDENTIFIER_POINTER (id) : "<unnamed>");

  std::cerr << tree_code_name[tc] << " " << name
       << " at " << DECL_SOURCE_FILE (decl) << ":"
       << DECL_SOURCE_LINE (decl) << std::endl;

  bool found = false;
  for (unsigned int i=0 ; i<functions->argc && !found ; i++) {
	found = strcmp(name,functions->argv->key) == 0;
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
	  walk_through(decl,dumper);
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


