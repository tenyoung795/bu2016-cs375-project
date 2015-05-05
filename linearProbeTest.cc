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
 
    TEST_F(linearTest, tableResize){
        probe.insertKey("thing1");
        probe.insertKey("thing2");
        probe.insertKey("thing3");
        probe.insertKey("thing4");
        probe.insertKey("thing5");
        probe.insertKey("thing6");
        probe.insertKey("thing7");
        probe.insertKey("thing8");
        probe.insertKey("thing9");
        probe.insertKey("thing10");
        probe.insertKey("thing11");
        probe.insertKey("thing12");
        probe.insertKey("thing13");
        probe.insertKey("thing14");
        EXPECT_EQ(37,probe.tSize());
    }
    
    TEST_F(linearTest, DeleteExist){
        probe.insertKey("thing10");
        EXPECT_TRUE(probe.deleteKey("thing10"));
        EXPECT_FALSE(probe.deleteKey("thing10"));
        EXPECT_FALSE(probe.deleteKey("stanley"));
    }
    
    TEST_F(linearTest, searchExist){
        probe.insertKey("brandon");
        EXPECT_FALSE(probe.searchKey("ten-young"));
        EXPECT_TRUE(probe.searchKey("brandon"));
        
    }
    
    
}