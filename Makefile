SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)
PLUGIN = myplugin
EXEC = $(PLUGIN).so

CXX=g++ #yep, strange but necessary for plugins
CFLAGS=-I/usr/lib/gcc/x86_64-pc-linux-gnu/4.8.3/plugin/include -fPIC
CXXFLAGS=$(CFLAGS) -std=c++11
LDFLAGS=-shared

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

run: $(EXEC)
	gcc -iplugindir=. -fplugin=$(PLUGIN) -shared -fPIC -x c -S test.c

.PHONY : clean

clean :
	rm -rf $(OBJS)

arith_expr.o: arith_expr.cpp arith_expr.h value.h value_factory.h \
 dumper.h bad_tree_exception.h
bad_tree_exception.o: bad_tree_exception.cpp bad_tree_exception.h
bind_expr.o: bind_expr.cpp bind_expr.h expression.h value.h \
 bad_tree_exception.h dumper.h expr_factory.h
call_expr.o: call_expr.cpp call_expr.h expression.h value.h \
 bad_tree_exception.h dumper.h value_factory.h
case_label_expr.o: case_label_expr.cpp bad_tree_exception.h \
 case_label_expr.h expression.h value.h dumper.h value_factory.h
cond_expr.o: cond_expr.cpp cond_expr.h expression.h value.h \
 bad_tree_exception.h dumper.h value_factory.h expr_factory.h
decl_expr.o: decl_expr.cpp decl_expr.h expression.h value.h \
 bad_tree_exception.h dumper.h value_factory.h
dumper.o: dumper.cpp bind_expr.h expression.h value.h call_expr.h \
 case_label_expr.h cond_expr.h decl_expr.h goto_expr.h label_expr.h \
 leaf.h dumper.h modify_expr.h nop_expr.h preincrement_expr.h \
 return_expr.h stmt_list.h switch_expr.h
expr_factory.o: expr_factory.cpp expr_factory.h expression.h arith_expr.h \
 value.h bind_expr.h call_expr.h cond_expr.h case_label_expr.h \
 decl_expr.h goto_expr.h label_expr.h modify_expr.h nop_expr.h \
 preincrement_expr.h return_expr.h switch_expr.h stmt_list.h leaf.h \
 dumper.h
expression.o: expression.cpp expression.h dumper.h
goto_expr.o: goto_expr.cpp bad_tree_exception.h goto_expr.h expression.h \
 value.h dumper.h value_factory.h
identifier.o: identifier.cpp value.h identifier.h bad_tree_exception.h
indirection.o: indirection.cpp value.h value_factory.h \
 bad_tree_exception.h indirection.h
integer_cst.o: integer_cst.cpp integer_cst.h value.h bad_tree_exception.h
label.o: label.cpp value.h value_factory.h bad_tree_exception.h label.h
label_expr.o: label_expr.cpp bad_tree_exception.h label_expr.h \
 expression.h value.h dumper.h value_factory.h
leaf.o: leaf.cpp value.h expression.h dumper.h leaf.h value_factory.h
modify_expr.o: modify_expr.cpp expression.h modify_expr.h value.h \
 bad_tree_exception.h dumper.h value_factory.h
myplugin.o: myplugin.cpp myplugin.h expr_factory.h expression.h dumper.h \
 bad_tree_exception.h
negate_op.o: negate_op.cpp value.h value_factory.h bad_tree_exception.h \
 negate_op.h
nop_expr.o: nop_expr.cpp nop_expr.h expression.h bad_tree_exception.h \
 dumper.h
preincrement_expr.o: preincrement_expr.cpp bad_tree_exception.h dumper.h \
 preincrement_expr.h expression.h value_factory.h value.h
return_expr.o: return_expr.cpp return_expr.h expression.h value.h \
 bad_tree_exception.h dumper.h value_factory.h
stmt_list.o: stmt_list.cpp expression.h bad_tree_exception.h \
 expr_factory.h dumper.h stmt_list.h
string_cst.o: string_cst.cpp string_cst.h value.h bad_tree_exception.h
switch_expr.o: switch_expr.cpp switch_expr.h expression.h \
 bad_tree_exception.h dumper.h value_factory.h expr_factory.h
ternary_op.o: ternary_op.cpp ternary_op.h value.h expression.h \
 bad_tree_exception.h expr_factory.h value_factory.h dumper.h
value.o: value.cpp value.h
value_factory.o: value_factory.cpp value.h value_factory.h arith_expr.h \
 integer_cst.h indirection.h string_cst.h identifier.h ternary_op.h \
 expression.h modify_expr.h cond_expr.h negate_op.h label.h
