//
//  HashTable.h
//  s24Project4
//
//  Created by Cameron Maiden on 6/9/24.
//

#ifndef HashTable_h
#define HashTable_h

#include <vector>
#include <list>
#include <string>

class HashTable
{
public:
    HashTable();
    void insert(std::string subString, size_t offset);
    bool contains(std::string subString, size_t& offset) const;
    
private:
    unsigned long tablesize = 120011; // using a prime number to help diversify the hashing of the items
    
    struct Node
    {
        Node(std::string s, size_t o) : m_subString(s), m_offset(o) {}
        std::string m_subString;
        size_t m_offset;
    };
    
    std::vector<std::list<Node*>> m_hashTable;
};


#endif /* HashTable_h */
