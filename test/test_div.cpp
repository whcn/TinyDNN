#include "gtest/gtest.h"
#include "core.h"
#include "operator.h"

//TEST(BasicOperation, Div_Simple) {
//    Variable x1(4);
//    Variable x2(2);
//    Variable y = x1 / x2;
//    ASSERT_EQ(y.GetData(), 2);
//    y.Backward();
//    ASSERT_EQ(x1.GetGrad(), 0.5);
//    ASSERT_EQ(x2.GetGrad(), -1);
//}
//
//TEST(BasicOperation, Div_SameVariable) {
//    Variable x1(3);
//    Variable y = x1 / x1;
//    ASSERT_EQ(y.GetData(), 1);
//    y.Backward();
//    ASSERT_EQ(x1.GetGrad(), 0);
//}
//
//TEST(BasicOperation, Div_MultiVariable) {
//    Variable x1(8);
//    Variable x2(4);
//    Variable x3(2);
//    Variable y = x1 / x2 / x3;
//    ASSERT_EQ(y.GetData(), 1);
//    y.Backward();
//    ASSERT_EQ(x1.GetGrad(), 0.125);
//    ASSERT_EQ(x2.GetGrad(), -0.25);
//    ASSERT_EQ(x3.GetGrad(), -0.5);
//}
//
//TEST(BasicOperation, Div_RightScalar) {
//    Variable x(4);
//    Variable y = x / 2;
//    ASSERT_EQ(y.GetData(), 2);
//    y.Backward();
//    ASSERT_EQ(x.GetGrad(), 0.5);
//}
//
//TEST(BasicOperation, Div_LeftScalar) {
//    Variable x(2);
//    Variable y = 4 / x;
//    ASSERT_EQ(y.GetData(), 2);
//    y.Backward();
//    ASSERT_EQ(x.GetGrad(), -1);
//}
