#include <cstddef>

#include <utility>

#include "gtest/gtest.h"

#include "resize.h"

namespace cs375 {

namespace {
using test_case = std::pair<std::size_t, std::size_t>;
}

struct NextTableSizeTest : ::testing::TestWithParam<test_case> {
};

TEST_P(NextTableSizeTest, ReturnsNextPrimeAfterDoubling) {
    auto &&c = GetParam();
    EXPECT_EQ(c.second, next_table_size(c.first));
}

INSTANTIATE_TEST_CASE_P(, NextTableSizeTest,
    ::testing::Values(
        test_case{0, 2},
        test_case{1, 2},
        test_case{2, 5},
        test_case{3, 7},
        test_case{5, 11},
        test_case{7, 17},
        test_case{11, 23},
        test_case{13, 29},
        test_case{17, 37},
        test_case{19, 41},
        test_case{23, 47},
        test_case{SIZE_MAX, SIZE_MAX}
    ));

}
