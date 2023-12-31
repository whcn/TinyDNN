#include "gtest/gtest.h"
#include "core.h"
#include "operator.h"

TEST(BasicOperation, Add_Simple) {
    Variable x1(1);
    Variable x2(2);
    Variable y = x1 + x2;
    ASSERT_EQ(y.GetData(), 3);
    y.Backward();
    ASSERT_EQ(x1.GetGrad()->GetData(), 1);
    ASSERT_EQ(x2.GetGrad()->GetData(), 1);
}

TEST(BasicOperation, Add_SameVariable) {
    Variable x1(3);
    Variable y = x1 + x1;
    ASSERT_EQ(y.GetData(), 6);
    y.Backward();
    ASSERT_EQ(x1.GetGrad()->GetData(), 2);
}

TEST(BasicOperation, Add_MultiVariable) {
    Variable x1(1);
    Variable x2(2);
    Variable x3(3);
    Variable y = x1 + x2 + x3;
    ASSERT_EQ(y.GetData(), 6);
    y.Backward();
    ASSERT_EQ(x1.GetGrad()->GetData(), 1);
    ASSERT_EQ(x2.GetGrad()->GetData(), 1);
    ASSERT_EQ(x3.GetGrad()->GetData(), 1);
}

TEST(BasicOperation, Add_RightScalar) {
    Variable x(1);
    Variable y = x + 2;
    ASSERT_EQ(y.GetData(), 3);
    y.Backward();
    ASSERT_EQ(x.GetGrad()->GetData(), 1);
}

TEST(BasicOperation, Add_LeftScalar) {
    Variable x(1);
    Variable y = 2 + x;
    ASSERT_EQ(y.GetData(), 3);
    y.Backward();
    ASSERT_EQ(x.GetGrad()->GetData(), 1);
}
