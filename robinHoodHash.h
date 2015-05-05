
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
        //holds the key values
        sparse_array <Key> robinArray;
        //false signifies nothing was there
        //true signifies there is or was something there
        std::vector <bool> bitVector;
        //distance vector holds the distance from the index that the value wanted to be inserted at
        std::vector <std::size_t> distanceVector;
        
        
    public:
        
        //Default constructor
        robinHoodHash():
            tableSize(17), robinArray(tableSize),bitVector(tableSize),distanceVector(tableSize){
        }
        
        //Constructor with size
        robinHoodHash(std::size_t arraySize):
            tableSize(arraySize), robinArray(tableSize),bitVector(tableSize),distanceVector(tableSize){
        }
        
        //returns sparse array size
        std::size_t size(){
            return robinArray.size();
        }
        
        //return tableSize
        std::size_t tSize(){
            return tableSize;
        }
        
        //inserts the key into the sparse array
        //returns false if key is already in table
        bool insertKey(Key k){
            std::hash <Key> hash_fn;
            std::size_t hashValue = hash_fn(k) % tableSize;
            
            //if load factor is hit then must transfer items to new sparse array
            if(should_resize(0.75f, tableSize, robinArray.size()+1)){
                
                std::size_t newTableSize = next_table_size(tableSize);
                std::size_t oldTableSize = tableSize;
                tableSize = newTableSize;
                
                //create a new robin hood so we can get a larger array and we can just copy everything over
                robinHoodHash robin1(newTableSize);
                //goes through the whole array and copis into the new robin hood array
                for(std::size_t i = 0; i < oldTableSize; i++){
                    if(robinArray.contains(i)){
                        robin1.insertKey(*robinArray.at(i));
                    }
                }
                //swap the robin hoods so we now have the new robin hood with larger array size
                std::swap(*this, robin1);
            }
            
            //need to keep track of distance
            //distance is used in robin hood hashing
            //a value that has traveled a greater distance from the hashIndex it wanted to be placed at initially can kick out a value that has traveled a smaller distance even if that value is closer to where it wanted to be initially inserted
            std::size_t currentDistance = 0;

            //while the hash array is full
            while(robinArray.contains(hashValue)){
                if (*robinArray.at(hashValue) == k) {
                    return false;
                }
                if(currentDistance > distanceVector[hashValue]){
                    std::swap(currentDistance, distanceVector[hashValue]);
                    std::swap(k,*robinArray.at(hashValue));
                }
                currentDistance++;
                hashValue++;
                if(hashValue == tableSize){
                    hashValue = 0;
                }
            }
            robinArray.emplace(hashValue, std::move(k));
            bitVector[hashValue] = true;
            distanceVector[hashValue] = currentDistance;
            return true;
        }
        
        std::size_t searchKeyIndex(const Key &k){
            std::hash<Key> hash_fn;
            std::size_t hashValue = hash_fn(k) % tableSize;
            
            std::size_t currentDistance = 0;
            
            while(bitVector[hashValue]) {
                auto ptr = robinArray.at(hashValue);
                if(!ptr || *ptr != k){
                    //1 signifies that location is full or used to be full
                    if(distanceVector[hashValue] >= currentDistance){
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
        
        bool searchKey(const Key &k){
            return searchKeyIndex(k) != (std::size_t) -1;
        }
        
        bool deleteKey(const Key &k){
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
