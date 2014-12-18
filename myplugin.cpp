#include <cstring>
#include <iostream>

/* We are going to overwrite all passes, in order to be called just after the
 * C++ AST construction. */

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
#include "text_dumper.h"
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

	std::cout << "Plugin loaded" << std::endl;

	// Disable assembly output.
	//
	asm_file_name = HOST_BIT_BUCKET;

	// Register callbacks.
	//
	register_callback(plugin_info->base_name,
			PLUGIN_PRE_GENERICIZE,
			&gate_callback,
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
	std::cout << std::endl;
}

extern "C" void gate_callback (void* arg, void*)
{
  // If there were errors during compilation,
  // let GCC handle the exit.
  //
  if (errorcount || sorrycount)
    return;
 
  //
  // Process AST. Issue diagnostics and set r
  // to 1 in case of an error.
  //
  std::cerr << "processing " << main_input_filename << std::endl;

  tree decl = (tree) arg;
  int tc = TREE_CODE(decl);
  tree id = DECL_NAME(decl);
  const char* name (id ? IDENTIFIER_POINTER (id) : "<unnamed>");

  std::cerr << tree_code_name[tc] << " " << name
       << " at " << DECL_SOURCE_FILE (decl) << ":"
       << DECL_SOURCE_LINE (decl) << std::endl;

  auto dumper = std::unique_ptr<Dumper>(new TextDumper());
  walk_through(decl,*dumper);
  std::cout << std::endl;
}



