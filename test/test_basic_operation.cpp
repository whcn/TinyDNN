#include "gtest/gtest.h"
#include "core.h"

TEST(BasicOperation, Add) {
    Variable lhs(1);
    Variable rhs(2);
    std::vector<Variable *> args{&lhs, &rhs};
    auto add = Add();
    auto c = add(args);
    ASSERT_EQ(c.GetData(), 3);
    c.Backward();
    ASSERT_EQ(lhs.GetGrad(), 1);
    ASSERT_EQ(rhs.GetGrad(), 1);
}