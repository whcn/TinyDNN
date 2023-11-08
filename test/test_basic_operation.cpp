#include "gtest/gtest.h"
#include "core.h"

TEST(TestBasicOperation, TestAdd) {
    Variable lhs(1);
    Variable rhs(2);
    std::vector<Variable> args{lhs, rhs};
    auto c = Add()(args);
    ASSERT_EQ(c.GetData(), 3);
}