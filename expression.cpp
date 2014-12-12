#include <cstdlib>
#include <gcc-plugin.h>
#include <tree.h>
#include "expression.h"

Expression::Expression(tree t) : _expr(t)
{}
