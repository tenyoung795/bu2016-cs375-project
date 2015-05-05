
#ifndef DOUBLELINEARPROBE_H
#define DOUBLELINEARPROBE_H

#include <cstddef>
#include <utility>
#include <vector>
#include <functional>
#include "sparse-array.h"
#include "resize.h"

namespace cs375{
    template <class Key>
    class doubleLinearProbe{
    
    private:
        std::size_t tableSize;
        sparse_array <Key> sArray;
        std::vector <bool> bitVector;
        
        std::size_t searchKeyPrivate(Key k){
            std::hash<Key> hash_fn;
            std::size_t hashIndex = hash_fn(k) % tableSize;
            
            std::size_t count = 1;
            bool evenCount = true;
            
            //while the hash value if full
            while(bitVector[hashIndex]){
                auto ptr = sArray.at(hashIndex);
                if(!ptr || *ptr != k){
                //loops back around to the beginning of the table to check for empty slots
                    if(evenCount){
                        hashIndex = (hashIndex + count) % tableSize;
                        evenCount = false;
                    }
                    else{
                        hashIndex = ((std::ptrdiff_t)hashIndex - (std::ptrdiff_t)count) % tableSize;
                        evenCount = true;
                    }
                    count++;
                }
                else{
                    return hashIndex;
                }
            }
            return -1;
        }
        
    public:
        doubleLinearProbe():
            tableSize(17), sArray(tableSize), bitVector(tableSize){
        }
        
        doubleLinearProbe(std::size_t arraySize):
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
            std::size_t hashIndex = hash_fn(k) % tableSize;
            
            //if load factor is hit then must transfer items to new sparse array
            if(should_resize(0.75f, tableSize, sArray.size()+1)){
                
                std::size_t newTableSize = next_table_size(tableSize);
                std::size_t oldTableSize = tableSize;
                tableSize = newTableSize;
                
                doubleLinearProbe probe1{newTableSize};
                for(std::size_t i = 0; i < oldTableSize; i++){
                    if(sArray.contains(i)){
                        probe1.insertKey(*sArray.at(i));
                    }
                }
                std::swap(*this, probe1);
            }
            
            std::size_t counter = 1;
            bool evenCounter = true;
            
            //while the hash value is full
            while(sArray.contains(hashIndex)){
                //loops back around to the beginning of the table to check for empty slots
                if(evenCounter){
                    hashIndex = (hashIndex + counter) % tableSize;
                    evenCounter = false;
                }
                else{
                    hashIndex = ((std::ptrdiff_t)hashIndex - (std::ptrdiff_t)counter) % tableSize;
                    evenCounter = true;
                }
                counter++;
            }
            sArray.emplace(hashIndex, k);
            bitVector[hashIndex] = true;
        }
        
        
        std::size_t searchKeyIndex(Key k){
            return searchKeyPrivate(k);
        }
        //returns index of the key k
        bool searchKey(Key k){
            return searchKeyPrivate(k) != (std::size_t) -1;
        }

        bool deleteKey(Key k){
            std::size_t hashIndex = searchKeyPrivate(k);
            if(hashIndex != (std::size_t)-1){
                sArray.erase(hashIndex);
                return true;
            }
            return false;
        }
    };
}

#endif  //DOUBLELINEARPROBE_H
