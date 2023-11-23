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

TEST(Graphviz, AddBackward) {
    Variable x1(1, "x1");
    Variable x2(2, "x2");
    Variable y = x1 + x2;
    y.Backward();
    Variable *gx1 = x1.GetGrad();
    gx1->SetName("gx1");
    CreateDotFile(*gx1, "add_backward.dot");
    system("dot -T pdf add_backward.dot -o add_backward.pdf");
}

TEST(Graphviz, MulBackward) {
    Variable x1(1, "x1");
    Variable x2(2, "x2");
    Variable y = x1 * x2;
    y.Backward();
    Variable *gx1 = x1.GetGrad();
    gx1->SetName("gx1");
    CreateDotFile(*gx1, "mul_backward.dot");
    system("dot -T pdf mul_backward.dot -o mul_backward.pdf");
}

TEST(Graphviz, SubBackward) {
    Variable x1(1, "x1");
    Variable x2(2, "x2");
    Variable y = x1 - x2;
    y.Backward();
    Variable *gx1 = x1.GetGrad();
    gx1->SetName("gx1");
    CreateDotFile(*gx1, "sub_backward.dot");
    system("dot -T pdf sub_backward.dot -o sub_backward.pdf");
}

TEST(Graphviz, DivBackward) {
    Variable x1(1, "x1");
    Variable x2(2, "x2");
    Variable y = x1 / x2;
    y.Backward();
    Variable *gx1 = x1.GetGrad();
    gx1->SetName("gx1");
    CreateDotFile(*gx1, "div_backward.dot");
    system("dot -T pdf div_backward.dot -o div_backward.pdf");
}
