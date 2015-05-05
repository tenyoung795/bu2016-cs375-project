#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <string>

#include "gtest/gtest.h"
#include "doubleLinearProbe.h"

namespace cs375 {
    
    class doubleLinearTest : public ::testing::Test {
    protected:
        doubleLinearProbe<std::string> dProbe;
        doubleLinearProbe<int> dProbeInt;

    };
    
    TEST_F(doubleLinearTest,StartsEmpty){
        EXPECT_EQ(0,dProbe.size());
    }
    
    TEST_F(doubleLinearTest, insertFirst){
        dProbe.insertKey("hello");
        EXPECT_TRUE(dProbe.searchKey("hello"));
    }
    
    TEST_F(doubleLinearTest, tableResize){
        dProbe.insertKey("thing1");
        dProbe.insertKey("thing2");
        dProbe.insertKey("thing3");
        dProbe.insertKey("thing4");
        dProbe.insertKey("thing5");
        dProbe.insertKey("thing6");
        dProbe.insertKey("thing7");
        dProbe.insertKey("thing8");
        dProbe.insertKey("thing9");
        dProbe.insertKey("thing10");
        dProbe.insertKey("thing11");
        dProbe.insertKey("thing12");
        dProbe.insertKey("thing13");
        dProbe.insertKey("thing14");
        EXPECT_EQ(37,dProbe.tSize());
    }
    
    TEST_F(doubleLinearTest, DeleteExist){
        dProbe.insertKey("thing10");
        EXPECT_TRUE(dProbe.deleteKey("thing10"));
        EXPECT_FALSE(dProbe.deleteKey("thing10"));
        EXPECT_FALSE(dProbe.deleteKey("stanley"));
    }
    
    TEST_F(doubleLinearTest, searchExist){
        dProbe.insertKey("brandon");
        EXPECT_FALSE(dProbe.searchKey("ten-young"));
        EXPECT_TRUE(dProbe.searchKey("brandon"));
        
    }
    
    TEST_F(doubleLinearTest, collisionRes){
        dProbeInt.insertKey(1);
        dProbeInt.insertKey(2);
        dProbeInt.insertKey(18);
        dProbeInt.insertKey(17);
        
        EXPECT_EQ(1,dProbeInt.searchKeyIndex(1));
        EXPECT_EQ(2,dProbeInt.searchKeyIndex(2));
        EXPECT_EQ(0,dProbeInt.searchKeyIndex(18));
        EXPECT_EQ(16,dProbeInt.searchKeyIndex(17));
        
    }
    
}