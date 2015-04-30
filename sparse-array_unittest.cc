#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <string>

#include "gtest/gtest.h"

#include "sparse-array.h"

namespace cs375 {

// Test with nastier types to additionally test memory correctness.
class SparseArrayTest : public ::testing::Test {
    protected:
    sparse_array<std::string> array{17};
};

TEST_F(SparseArrayTest, StartsEmpty) {
    EXPECT_EQ(0, array.size());
}

TEST_F(SparseArrayTest, Contains_Nonexistent) {
    EXPECT_FALSE(array.contains(0));
}

TEST_F(SparseArrayTest, At_Nonexistent) {
    EXPECT_EQ(nullptr, array.at(0));
}

TEST_F(SparseArrayTest, Erase_Nonexistent) {
    EXPECT_FALSE(array.erase(0));
}

TEST_F(SparseArrayTest, Insert_Nonexistent) {
    auto result = array.emplace(0, "Hello");
    ASSERT_NE(nullptr, result);
    EXPECT_EQ("Hello", *result);
}

TEST_F(SparseArrayTest, Insert_Nonexistent_IncreasesSize) {
    array.emplace(0, "Hello");
    EXPECT_EQ(1, array.size());
}

TEST_F(SparseArrayTest, Contains_Existent) {
    array.emplace(0, "Hello");
    EXPECT_TRUE(array.contains(0));
}

TEST_F(SparseArrayTest, At_Existent) {
    auto expected = array.emplace(0, "Hello");
    EXPECT_EQ(expected, array.at(0));
}

TEST_F(SparseArrayTest, Erase_Existent) {
    array.emplace(0, "Hello");
    EXPECT_TRUE(array.erase(0));
}

TEST_F(SparseArrayTest, Erase_Existent_DecreasesSize) {
    array.emplace(0, "Hello");
    array.erase(0);
    EXPECT_EQ(0, array.size());
}

TEST_F(SparseArrayTest, Insert_Existent) {
    array.emplace(0, "Hello");
    EXPECT_EQ(nullptr, array.emplace(0, "Goodbye"));
}

TEST_F(SparseArrayTest, Insert_Twice) {
    array.emplace(1, "Hello");
    auto result = array.emplace(0, "Goodbye");
    ASSERT_NE(nullptr, result);
    EXPECT_EQ("Goodbye", *result);
}

TEST_F(SparseArrayTest, Erase_FirstInserted) {
    array.emplace(1, "Hello");
    array.emplace(0, "Goodbye");
    EXPECT_TRUE(array.erase(1));
}

TEST_F(SparseArrayTest, Erase_SecondInserted) {
    array.emplace(1, "Hello");
    array.emplace(0, "Goodbye");
    EXPECT_TRUE(array.erase(0));
}

TEST_F(SparseArrayTest, Iteration_Empty) {
    EXPECT_EQ(array.end(), array.begin());
}

TEST_F(SparseArrayTest, Iteration_SizeOne) {
    array.emplace(0, "Hello");

    ASSERT_EQ(1, std::distance(array.begin(), array.end()));
    std::string expected[] = {"Hello"};
    EXPECT_TRUE(std::is_permutation(std::begin(expected), std::end(expected), array.begin()));
}

TEST_F(SparseArrayTest, Iteration_SizeTwo) {
    array.emplace(1, "Hello");
    array.emplace(0, "Goodbye");

    ASSERT_EQ(2, std::distance(array.begin(), array.end()));
    std::string expected[] = {"Hello", "Goodbye"};
    EXPECT_TRUE(std::is_permutation(std::begin(expected), std::end(expected), array.begin()));
}

TEST(SparseArrayDestructorTest, DoesDestroy) {
    bool destroyed = false;
    struct nontrivally_destroyable {
        bool &destroyed;
        ~nontrivally_destroyable() {
            destroyed = true;
        }
    };
    {
        sparse_array<nontrivally_destroyable> arr(17);
        arr.emplace(1, destroyed);
    }
    ASSERT_TRUE(destroyed);
}

}
