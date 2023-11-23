#include "gtest/gtest.h"
#include "core.h"
#include "operator.h"

//TEST(BasicOperation, Mul_Simple) {
//    Variable x1(1);
//    Variable x2(2);
//    Variable y = x1 * x2;
//    ASSERT_EQ(y.GetData(), 2);
//    y.Backward();
//    ASSERT_EQ(x1.GetGrad(), 2);
//    ASSERT_EQ(x2.GetGrad(), 1);
//}
//
//TEST(BasicOperation, Mul_SameVariable) {
//    Variable x1(3);
//    Variable y = x1 * x1;
//    ASSERT_EQ(y.GetData(), 9);
//    y.Backward();
//    ASSERT_EQ(x1.GetGrad(), 6);
//}
//
//TEST(BasicOperation, Mul_MultiVariable) {
//    Variable x1(1);
//    Variable x2(2);
//    Variable x3(3);
//    Variable y = x1 * x2 * x3;
//    ASSERT_EQ(y.GetData(), 6);
//    y.Backward();
//    ASSERT_EQ(x1.GetGrad(), 6);
//    ASSERT_EQ(x2.GetGrad(), 3);
//    ASSERT_EQ(x3.GetGrad(), 2);
//}
//
//TEST(BasicOperation, Mul_RightScalar) {
//    Variable x(2);
//    Variable y = x * 3;
//    ASSERT_EQ(y.GetData(), 6);
//    y.Backward();
//    ASSERT_EQ(x.GetGrad(), 3);
//}
//
//TEST(BasicOperation, Mul_LeftScalar) {
//    Variable x(2);
//    Variable y = 3 * x;
//    ASSERT_EQ(y.GetData(), 6);
//    y.Backward();
//    ASSERT_EQ(x.GetGrad(), 3);
//}
