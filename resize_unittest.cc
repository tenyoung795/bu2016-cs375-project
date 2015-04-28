#include <cstddef>

#include "gtest/gtest.h"

#include "resize.h"

namespace cs375 {

TEST(NextTableSize, Zero) {
    EXPECT_EQ(2u, next_table_size(0u));
}

TEST(NextTableSize, One) {
    EXPECT_EQ(2u, next_table_size(1u));
}

TEST(NextTableSize, Two) {
    EXPECT_EQ(5u, next_table_size(2u));
}

TEST(NextTableSize, Three) {
    EXPECT_EQ(7u, next_table_size(3u));
}

TEST(NextTableSize, Five) {
    EXPECT_EQ(11u, next_table_size(5u));
}

TEST(NextTableSize, Seven) {
    EXPECT_EQ(17u, next_table_size(7u));
}

TEST(NextTableSize, Eleven) {
    EXPECT_EQ(23u, next_table_size(11u));
}

TEST(NextTableSize, Thirteen) {
    EXPECT_EQ(29u, next_table_size(13u));
}

TEST(NextTableSize, Seventeen) {
    EXPECT_EQ(37u, next_table_size(17u));
}

TEST(NextTableSize, Nineteen) {
    EXPECT_EQ(41u, next_table_size(19u));
}

TEST(NextTableSize, TwentyThree) {
    EXPECT_EQ(47u, next_table_size(23u));
}

TEST(NextTableSize, SizeMax) {
    EXPECT_EQ(SIZE_MAX, next_table_size(SIZE_MAX));
}

}
