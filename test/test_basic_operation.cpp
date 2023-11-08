#include "gtest/gtest.h"
#include "core.h"

TEST(TestBasicOperation, TestAdd) {
    Variable a(1);
    Variable b(2);
    auto c = Add()(a, b);
    ASSERT_EQ(c.GetData(), 3);
}