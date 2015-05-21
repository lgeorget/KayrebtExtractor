lib_LTLIBRARIES=libcgrapher4gcc.la
libcgrapher4gcc_la_SOURCES=\
	operator.h\
	operator.cpp\
	activity_graph_dumper.cpp\
	activity_graph_dumper.h\
	asm_expr.cpp\
	asm_expr.h\
	assign_expr.cpp\
	assign_expr.h\
	bad_gimple_exception.cpp\
	bad_gimple_exception.h\
	bad_tree_exception.cpp\
	bad_tree_exception.h\
	function_body.cpp\
	function_body.h\
	call_expr.cpp\
	call_expr.h\
	case_label.cpp\
	case_label.h\
	cgrapher4gcc.cpp\
	cond_expr.cpp\
	cond_expr.h\
	debug.h\
	dumper.h\
	expr_factory.cpp\
	expr_factory.h\
	expression.cpp\
	expression.h\
	goto_expr.cpp\
	goto_expr.h\
	identifier.cpp\
	identifier.h\
	integer_cst.cpp\
	integer_cst.h\
	label.cpp\
	label.h\
	label_expr.cpp\
	label_expr.h\
	nop_expr.cpp\
	nop_expr.h\
	return_expr.cpp\
	return_expr.h\
	string_cst.cpp\
	string_cst.h\
	switch_expr.cpp\
	switch_expr.h\
	value.cpp\
	value.h\
	value_factory.cpp\
	value_factory.h\
	unary.cpp\
	unary.h\
	array_ref.cpp\
	array_ref.h\
	component_ref.cpp\
	component_ref.h\
	constructor.cpp\
	constructor.h\
	mem_ref.cpp\
	mem_ref.h\
	configurator.cpp\
	configurator.h\
	url_finder.cpp\
	url_finder.h\
	make_unique.h
libcgrapher4gcc_la_CXXFLAGS = -std=c++11 -I @gcc_includes@ -I @srcdir@/../activity_diagram/src/ $(YAML_CPP_CFLAGS) $(SQLITE3_CFLAGS)
libcgrapher4gcc_la_LDFLAGS  = -version-info 0:2:0
libcgrapher4gcc_la_LIBADD = ../activity_diagram/src/libactivity_diagram.la $(YAML_CPP_LIBS) $(SQLITE3_LIBS)

install-exec-local:
	$(RM) `gcc -print-file-name=plugin`/cgrapher4gcc.so || true
	$(LN_S) @libdir@/libcgrapher4gcc.so `gcc -print-file-name=plugin`/cgrapher4gcc.so || echo "Couldn't install plugin in `gcc -print-file-name=plugin`"

