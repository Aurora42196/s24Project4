//
//  HashTable.cpp
//  s24Project4
//
//  Created by Cameron Maiden on 6/9/24.
//

#include "HashTable.h"
#include <functional>
#include <string>
#include <vector>

using namespace std;

HashTable::HashTable()
{
    m_hashTable.resize(tablesize);
}

void HashTable::insert(string subString, size_t offset)
{
//    hash<string> str_hash;
//    size_t hashValue = str_hash(subString);
    size_t bucketNum = hash<string>()(subString) % tablesize;
    
    m_hashTable[bucketNum].push_back(new Node(subString, offset));
}

bool HashTable::contains(string subString , size_t& offset) const
{
    size_t bucketNum = hash<string>()(subString) % tablesize;
    // If the linked list is empty, we know that subString is not in our hash table
    if (m_hashTable.at(bucketNum).empty())
        return false;
    
    // If the linked list is not empty, we iterate through the list to see if we can find our value
    for(auto p = m_hashTable.at(bucketNum).begin(); p != m_hashTable.at(bucketNum).end(); p++)
    {
        // If we found the substring, give the referenece of its offset and return true
        if (subString == (*p)->m_subString)
        {
            offset = (*p)->m_offset;
            return true;
        }
    }
    // we return false if we weren't able to find the substring in our hash table
    return false;
}
