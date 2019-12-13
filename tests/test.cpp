// Copyright 2019 Your Name <your_email>

#include <gtest/gtest.h>
#include <header.hpp>
#include <SharedPtr.h>

TEST(Example, EmptyTest) {
    SharedPtr a = SharedPtr(new int(5));
    auto b = a; // NOLINT
    *b = 7;
    EXPECT_EQ(b.use_count(), 2);
}
