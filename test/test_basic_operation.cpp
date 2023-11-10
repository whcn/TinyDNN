#include "gtest/gtest.h"
#include "core.h"

TEST(BasicOperation, Add_Simple) {
    Variable x1(1);
    Variable x2(2);
    Variable y = x1 + x2;
    ASSERT_EQ(y.GetData(), 3);
    y.Backward();
    ASSERT_EQ(x1.GetGrad(), 1);
    ASSERT_EQ(x2.GetGrad(), 1);
}

TEST(BasicOperation, Add_SameVariable) {
    Variable x1(3);
    Variable y = x1 + x1;
    ASSERT_EQ(y.GetData(), 6);
    y.Backward();
    ASSERT_EQ(x1.GetGrad(), 2);
}

TEST(BasicOperation, Add_MultiVariable) {
    Variable x1(1);
    Variable x2(2);
    Variable x3(3);
    Variable y = x1 + x2 + x3;
    ASSERT_EQ(y.GetData(), 6);
    y.Backward();
    ASSERT_EQ(x1.GetGrad(), 1);
    ASSERT_EQ(x2.GetGrad(), 1);
    ASSERT_EQ(x3.GetGrad(), 1);
}
