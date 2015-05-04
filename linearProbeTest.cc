#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <string>

#include "gtest/gtest.h"
#include "linearProbe.h"

namespace cs375 {

class linearTest : public ::testing::Test {
    protected:
    linearProbe<std::string> probe;
};

    TEST_F(linearTest,StartsEmpty){
        EXPECT_EQ(0,probe.size());
    }
    
    TEST_F(linearTest, insertFirst){
        probe.insertKey("hello");
        EXPECT_TRUE(probe.searchKey("hello"));
    }
}