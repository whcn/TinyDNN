#include "gtest/gtest.h"
#include "core.h"
#include "utils.h"


TEST(Graphviz, Add) {
    Variable x1(1, "x1");
    Variable x2(2, "x2");
    Variable x3(3, "x3");
    Variable y = x1 + x2 + x3;
    CreateDotFile(y, "graph.dot");
}
