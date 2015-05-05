#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <string>

#include "gtest/gtest.h"
#include "robinHoodHash.h"

namespace cs375 {
    
    class robinTest : public ::testing::Test {
    protected:
        robinHoodHash<std::string> robin;
        robinHoodHash<std::size_t> robinInt;
    };
    
    TEST_F(robinTest,StartsEmpty){
        EXPECT_EQ(0,robin.size());
    }
    
    TEST_F(robinTest, insertFirst){
        robin.insertKey("hello");
        EXPECT_TRUE(robin.searchKey("hello"));
    }
    
    TEST_F(robinTest, tableResize){
        robin.insertKey("thing1");
        robin.insertKey("thing2");
        robin.insertKey("thing3");
        robin.insertKey("thing4");
        robin.insertKey("thing5");
        robin.insertKey("thing6");
        robin.insertKey("thing7");
        robin.insertKey("thing8");
        robin.insertKey("thing9");
        robin.insertKey("thing10");
        robin.insertKey("thing11");
        robin.insertKey("thing12");
        robin.insertKey("thing13");
        robin.insertKey("thing14");
        EXPECT_EQ(37,robin.tSize());
    }
    
    TEST_F(robinTest, DeleteExist){
        robin.insertKey("thing10");
        EXPECT_TRUE(robin.deleteKey("thing10"));
        EXPECT_FALSE(robin.deleteKey("thing10"));
        EXPECT_FALSE(robin.deleteKey("stanley"));
    }
    
    TEST_F(robinTest, searchExist){
        robin.insertKey("brandon");
        EXPECT_FALSE(robin.searchKey("ten-young"));
        EXPECT_TRUE(robin.searchKey("brandon"));
        
    }
    
    TEST_F(robinTest, itemSwap){
        robinInt.insertKey(1);
        robinInt.insertKey(2);
        robinInt.insertKey(18);
        
        EXPECT_EQ(1,robinInt.searchKeyIndex(1));
        EXPECT_EQ(2,robinInt.searchKeyIndex(18));
        EXPECT_EQ(3,robinInt.searchKeyIndex(2));

    }
    
    
}