#include "gtest/gtest.h"
#include "core.h"
#include "operator.h"

TEST(BasicOperation, Simple) {
    Variable x1(2);
    Variable x2(1);
    Variable y = x1 - x2;
    ASSERT_EQ(y.GetData(), 1);
    y.Backward();
    ASSERT_EQ(x1.GetGrad(), 1);
    ASSERT_EQ(x2.GetGrad(), -1);
}

TEST(BasicOperation, SameVariable) {
    Variable x1(3);
    Variable y = x1 - x1;
    ASSERT_EQ(y.GetData(), 0);
    y.Backward();
    ASSERT_EQ(x1.GetGrad(), 0);
}

TEST(BasicOperation, MultiVariable) {
    Variable x1(4);
    Variable x2(2);
    Variable x3(1);
    Variable y = x1 - x2 - x3;
    ASSERT_EQ(y.GetData(), 1);
    y.Backward();
    ASSERT_EQ(x1.GetGrad(), 1);
    ASSERT_EQ(x2.GetGrad(), -1);
    ASSERT_EQ(x3.GetGrad(), -1);
}

TEST(BasicOperation, RightScalar) {
    Variable x(3);
    Variable y = x - 2;
    ASSERT_EQ(y.GetData(), 1);
    y.Backward();
    ASSERT_EQ(x.GetGrad(), 1);
}

TEST(BasicOperation, LeftScalar) {
    Variable x(1);
    Variable y = 2 - x;
    ASSERT_EQ(y.GetData(), 1);
    y.Backward();
    ASSERT_EQ(x.GetGrad(), -1);
}
