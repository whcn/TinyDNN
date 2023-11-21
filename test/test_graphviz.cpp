#include <cstdlib>

#include "gtest/gtest.h"
#include "core.h"
#include "utils.h"
#include "operator.h"


TEST(Graphviz, Sphere) {
    Variable x(1, "x");
    Variable y(2, "y");
    Variable z = x * x + y * y;
    CreateDotFile(z, "sphere.dot");
    system("dot -T pdf sphere.dot -o sphere.pdf");
}

TEST(Graphviz, Matyas) {
    Variable x1(1, "x1");
    Variable x2(2, "x2");
    Variable y = 0.26 * (x1 * x1 + x2 * x2) - 0.84 * x1 * x2;
    CreateDotFile(y, "matyas.dot");
    system("dot -T pdf matyas.dot -o matyas.pdf");
}

TEST(Graphviz, GoldsteinPrice) {
    Variable x1(1, "x1");
    Variable x2(2, "x2");
    Variable y =
            (1 + (x1 + x1 + 1) * (x1 + x1 + 1) * (19 - 14 * x1 + 3 * x1 * x1 - 14 * x2 + 6 * x1 * x2 + 3 * x2 * x2)) *
            (30 + (2 * x2 - 3 * x2) * (2 * x2 - 3 * x2) *
                  (18 - 32 * x1 + 12 * x1 * x1 + 48 * x2 - 36 * x1 * x2 + 27 * x2 * x2));
    CreateDotFile(y, "goldstein_price.dot");
    system("dot -T pdf goldstein_price.dot -o goldstein_price.pdf");
}
