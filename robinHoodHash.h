
#ifndef ROBINHOODHASH_H
#define ROBINHOODHASH_H

#include <utility>
#include <vector>
#include <functional>
#include "sparse-array.h"
#include "resize.h"

namespace cs375 {
    template <class Key>
    class robinHoodHash{
    private:
        std::size_t tableSize;
        sparse_array <Key> robinArray;
        std::vector <bool> bitVector;
        std::vector <int> distanceVector;
        
        
        
    public:
        
        robinHoodHash():
            tableSize(17), robinArray(tableSize),bitVector(tableSize),distanceVector(tableSize){
        }
        
        robinHoodHash(std::size_t arraySize):
            tableSize(arraySize), robinArray(tableSize),bitVector(tableSize),distanceVector(tableSize){
        }
        
        std::size_t size(){
            return robinArray.size();
        }
        
        std::size_t tSize(){
            return tableSize;
        }
        
        void insertKey(Key k){
            std::hash <Key> hash_fn;
            std::size_t hashValue = hash_fn(k) % tableSize;
            
            if(should_resize(0.75f, tableSize, robinArray.size()+1)){
                
                std::size_t newTableSize = next_table_size(tableSize);
                std::size_t oldTableSize = tableSize;
                tableSize = newTableSize;
                
                robinHoodHash robin1(newTableSize);
                for(std::size_t i = 0; i < oldTableSize; i++){
                    if(robinArray.contains(i)){
                        robin1.insertKey(*robinArray.at(i));
                    }
                }
                std::swap(*this, robin1);
            }
            
            int currentDistance = 0;
            Key currentKey = k;

            while(robinArray.contains(hashValue)){
                if(currentDistance > distanceVector[hashValue]){
                    std::swap(currentDistance, distanceVector[hashValue]);
                    std::swap(currentKey,*robinArray.at(hashValue));
                }
                currentDistance++;
                hashValue++;
                if(hashValue == tableSize){
                    hashValue = 0;
                }
            }
            robinArray.emplace(hashValue, currentKey);
            bitVector[hashValue] = 1;
            distanceVector[hashValue] = currentDistance;
        }
        
        std::size_t searchKeyIndex(Key k){
            std::hash<Key> hash_fn;
            std::size_t hashValue = hash_fn(k) % tableSize;
            
            int currentDistance = 0;
            
            while(robinArray.contains(hashValue)){
                if(*robinArray.at(hashValue) != k){
                    //1 signifies that location is full or used to be full
                    if(bitVector[hashValue] && distanceVector[hashValue] >= currentDistance){
                        hashValue++;
                        currentDistance++;
                    }
                    //signfies this location never had a value
                    //or that the current distance is greater than distance at this location and should've been inserted here
                    else{
                        return -1;
                    }
                    
                    if(hashValue == tableSize){
                        hashValue = 0;
                    }
                }
                else{
                    return hashValue;
                }
            }
            return -1;
        }
        
        bool searchKey(Key k){
            return searchKeyIndex(k) != (std::size_t) -1;
        }
        
        bool deleteKey(Key k){
            std::size_t hashValue = searchKeyIndex(k);
            if(hashValue != (std::size_t)-1){
                robinArray.erase(hashValue);
                return true;
            }
            return false;
        }
    };
}

#endif //ROBINHOODHASH_H
