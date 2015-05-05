
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
        //contains 0 and 1s where 0 signifies nothing was ever there
        //1 signifies something is or was there
        std::vector <int> bitVector;
        
        std::size_t searchKeyPrivate(Key k){
            std::hash<Key> hash_fn;
            std::size_t hashValue = hash_fn(k) % tableSize;
            
            //checks the array
            while(sArray.contains(hashValue)){
                if(*sArray.at(hashValue) != k){
                //iterates through the array
                //1 signifies that location is full or used to be full
                    if(bitVector[hashValue]){
                        hashValue++;
                    }
                //signifies this location never had a value so no need to search further
                    else{
                        return -1;
                    }
                //loops back around if we hit end of table
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
        
        
    public:
        linearProbe():
            tableSize(17), sArray(tableSize),bitVector(tableSize){

        }
        //Constructor
        linearProbe(std::size_t arraySize):
            tableSize(arraySize), sArray(tableSize), bitVector(tableSize){
        }
        
        std::size_t size(){
            return sArray.size();
        }
        
        std::size_t tSize(){
            return tableSize;
        }
        
        void insertKey(Key k){
            std::hash<Key> hash_fn;
            std::size_t hashValue = hash_fn(k) % tableSize;
            
            //if load factor is hit then must transfer items to new sparse array
            if(should_resize(0.75f, tableSize, sArray.size()+1)){
                
                std::size_t newTableSize = next_table_size(tableSize);
                std::size_t oldTableSize = tableSize;
                tableSize = newTableSize;
                
                linearProbe probe1{newTableSize};
                for(std::size_t i = 0; i < oldTableSize; i++){
                    if(sArray.contains(i)){
                        probe1.insertKey(*sArray.at(i));
                    }
                }
                std::swap(*this, probe1);
            }
            //while the hash value if full
            while(sArray.contains(hashValue)){
                //loops back around to the beginning of the table to check for empty slots
                hashValue++;
                if(hashValue == tableSize){
                    hashValue = 0;
                }
            }
            //empty slot found
            sArray.emplace(hashValue,k);
            bitVector[hashValue] = 1;
        }
        
        //returns index of the key k
        bool searchKey(Key k){
            return searchKeyPrivate(k) != (std::size_t) -1;
        }
        
        bool deleteKey(Key k){
            std::size_t hashValue = searchKeyPrivate(k);
            if(hashValue != (std::size_t)-1){
                sArray.erase(hashValue);
                return true;
            }
            return false;
        }
    };
}
#endif  //LINEARPROBE_H
