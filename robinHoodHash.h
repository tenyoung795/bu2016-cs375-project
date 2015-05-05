
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
            std::size_t hashIndex = hash_fn(k) % tableSize;
            
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

            //while the hash array location is full
            while(robinArray.contains(hashIndex)){
                //if the value already exists we return false
                if (*robinArray.at(hashIndex) == k) {
                    return false;
                }
                //if our currentDistance is greater that means we should put our current key and distance that location and hold the key value and distance value that we have just taken the sport of
                //we keep doing this until we an empty spot for us to insert our key and distance into because that way we won't have to hold a new key and distance
                if(currentDistance > distanceVector[hashIndex]){
                    //swap the distances and swap the keys
                    //find a new home for the distance and keys we got
                    std::swap(currentDistance, distanceVector[hashIndex]);
                    std::swap(k,*robinArray.at(hashIndex));
                }
                //increment the distance because we are going to check the next index location
                currentDistance++;
                //increment the index
                hashIndex++;
                //if index is the tableSize we look back around to front of the table
                if(hashIndex == tableSize){
                    hashIndex = 0;
                }
            }
            //this means we have reached a blank index so we can insert our values here
            robinArray.emplace(hashIndex, std::move(k));
            bitVector[hashIndex] = true;
            distanceVector[hashIndex] = currentDistance;
            return true;
        }
        
        //search for the key and return index if found
        //if not return -1
        std::size_t searchKeyIndex(const Key &k){
            std::hash<Key> hash_fn;
            std::size_t hashIndex = hash_fn(k) % tableSize;
            
            std::size_t currentDistance = 0;
            
            //checks to see if a value is or used to exist there
            while(bitVector[hashIndex]) {
                auto ptr = robinArray.at(hashIndex);
                //if the value isn't equal to k and its not null
                if(!ptr || *ptr != k){
                    //if the current value in that hashIndex has a distance greater than or equal to ours than we can't place our value there
                    if(distanceVector[hashIndex] >= currentDistance){
                        hashIndex++;
                        currentDistance++;
                    }
                    //signfies this location never had a value
                    //or that the current distance is greater than distance at this location and should've been inserted here or earlier so since its not here it means that key doesn't exist
                    else{
                        return -1;
                    }
                    //loops around if we hit end of table
                    if(hashIndex == tableSize){
                        hashIndex = 0;
                    }
                }
                else{
                    return hashIndex;
                }
            }
            return -1;
        }
        
        //returns true if key is found
        bool searchKey(const Key &k){
            return searchKeyIndex(k) != (std::size_t) -1;
        }
        
        //returns true if key is found and erases it
        bool deleteKey(const Key &k){
            std::size_t hashIndex = searchKeyIndex(k);
            //if hashIndex is -1 it means the key doesn't exist
            if(hashIndex != (std::size_t)-1){
                robinArray.erase(hashIndex);
                return true;
            }
            return false;
        }
    };
}

#endif //ROBINHOODHASH_H
