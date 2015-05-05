
#ifndef LINEARPROBE_H
#define LINEARPROBE_H

#include <utility>
#include <vector>
#include <functional>
#include "sparse-array.h"
#include "resize.h"

namespace cs375{
    template <class Key>
    class linearProbe{
        
    private:
        std::size_t tableSize;
        //holds the key values
        sparse_array <Key> sArray;
        //false signifies nothing was there
        //true signifies there is or was something there
        std::vector <bool> bitVector;
        
        std::size_t searchKeyPrivate(const Key &k){
            std::hash<Key> hash_fn;
            //mods the hashvalue to be within the table
            std::size_t hashIndex = hash_fn(k) % tableSize;
            
            while(bitVector[hashIndex]){
                auto ptr = sArray.at(hashIndex);
                //if the value isn't equal to k and its not a nullptr we need to keep searching
                if(!ptr || *ptr != k){
                    //iterates through the array
                    //true signifies that location is full or used to be full
                    if(bitVector[hashIndex]){
                        hashIndex++;
                    }
                    //signifies this location never had a value so no need to search further
                    else{
                        return -1;
                    }
                    //loops back around if we hit end of table
                    if(hashIndex == tableSize){
                        hashIndex = 0;
                    }
                }
                //if the value is equal to k we come here
                else{
                    return hashIndex;
                }
            }
            return -1;
        }
        
        
    public:
        
        //Default constructor
        linearProbe():
            tableSize(17), sArray(tableSize),bitVector(tableSize){

        }
        //Constructor with size
        linearProbe(std::size_t arraySize):
            tableSize(arraySize), sArray(tableSize), bitVector(tableSize){
        }
        
        //returns sparse array size
        std::size_t size(){
            return sArray.size();
        }
        
        //return tableSize
        std::size_t tSize(){
            return tableSize;
        }
        
        //inserts a key
        //returns false if key is already in table
        bool insertKey(const Key &k){
            std::hash<Key> hash_fn;
            std::size_t hashIndex = hash_fn(k) % tableSize;
            
            //if load factor is hit then must transfer items to new sparse array
            if(should_resize(0.75f, tableSize, sArray.size()+1)){
                
                std::size_t newTableSize = next_table_size(tableSize);
                std::size_t oldTableSize = tableSize;
                tableSize = newTableSize;
                
                //create a new probe because we can just copy our info into the new probe
                linearProbe probe1{newTableSize};
                //goes through the whole array and copies into the new probe's array
                for(std::size_t i = 0; i < oldTableSize; i++){
                    if(sArray.contains(i)){
                        probe1.insertKey(*sArray.at(i));
                    }
                }
                //swap the probes so we now have the new probe with larger array size
                std::swap(*this, probe1);
            }
            //while the hash value is full
            while(sArray.contains(hashIndex)){
                if(*sArray.at(hashIndex) == k){
                    return false;
                }
                hashIndex++;
                //loops back around to the beginning of the table to check for empty slots
                if(hashIndex == tableSize){
                    hashIndex = 0;
                }
            }
            //empty slot found
            sArray.emplace(hashIndex,k);
            bitVector[hashIndex] = true;
            return true;
        }
        
        //returns true if key is found
        bool searchKey(const Key &k){
            return searchKeyPrivate(k) != (std::size_t) -1;
        }
        
        //deletes the key if it exists
        bool deleteKey(const Key &k){
            std::size_t hashIndex = searchKeyPrivate(k);
            //if hashIndex is -1 it means the key doesn't exist
            if(hashIndex != (std::size_t)-1){
                sArray.erase(hashIndex);
                return true;
            }
            return false;
        }
    };
}
#endif  //LINEARPROBE_H
