#include "gtest/gtest.h"
#include "core.h"

TEST(BasicOperation, Add_Simple) {
    Variable lhs(1);
    Variable rhs(2);
    std::vector<Variable *> args{&lhs, &rhs};
    auto add = Add();
    auto res = add(args);
    ASSERT_EQ(res.GetData(), 3);
    res.Backward();
    ASSERT_EQ(lhs.GetGrad(), 1);
    ASSERT_EQ(rhs.GetGrad(), 1);
}

TEST(BasicOperation, Add_SameVariable) {
    Variable lhs(3);
    Variable &rhs = lhs;
    std::vector<Variable *> args{&lhs, &rhs};
    auto add = Add();
    auto res = add(args);
    ASSERT_EQ(res.GetData(), 6);
    res.Backward();
    ASSERT_EQ(lhs.GetGrad(), 2);
    ASSERT_EQ(rhs.GetGrad(), 2);
}

TEST(BasicOperation, Add_ThreeVariable) {
    Variable one(2);
    Variable &two = one;
    Variable three(3);
    std::vector<Variable *> args1{&one, &two};
    auto add1 = Add();
    auto res1 = add1(args1);
    ASSERT_EQ(res1.GetData(), 4);
    std::vector<Variable *> args2{&res1, &three};
    auto add2 = Add();
    auto res2 = add2(args2);
    res2.Backward();
    ASSERT_EQ(res2.GetData(), 7);
    ASSERT_EQ(one.GetGrad(), 2);
    ASSERT_EQ(two.GetGrad(), 2);
    ASSERT_EQ(three.GetGrad(), 1);
}
