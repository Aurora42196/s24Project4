//
//  Revision.cpp
//  s24Project4
//
//  Created by Cameron Maiden on 6/10/24.
//

#include "Revision.h"
#include "utilities.h"
#include "HashTable.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void createRevision(istream& fold, istream& fnew, ostream& frevision)
{
    if(!fold)
    {
        cerr << "Invalid fold file passed in or in invalid state!" << endl;
        exit(1);
    }
    
    if(!fnew)
    {
        cerr << "Invalid fnew file passed in or in invalid state!" << endl;
        exit(1);
    }
    
    const size_t sequenceLength = 8;
    string oldString;
    string newString;
    
    // Read in the entire contents of the old file into a string.
    // Read the entire contents of the new file into another string.
    char c = '\0';
    while (fold.get(c))
    {
        oldString += c;
    }
    
    char n = '\0';
    while(fnew.get(n))
    {
        newString += n;
    }
    
    // Create a hash table to store the sequences of strings
    HashTable hashTable;
    for (size_t i = 0; i < oldString.size(); i += sequenceLength)
    {
        string oldSeq = oldString.substr(i, sequenceLength);
        hashTable.insert(oldSeq, i);
    }
    
    size_t oldOffset = 0;
    size_t j = 0;
    size_t length = 0;
    for(; j <= newString.size();/* j++*/)
    {
        string newSeq = newString.substr(j, sequenceLength);
        
        if(hashTable.contains(newSeq, oldOffset))
        {
            // This function checks beyond the length of the initial sequence to see if
            // any characters after the length still match the newFile, if it does,
            // we can increment the length to accomodate for that length of the match
            size_t lengthOfMatch = sequenceLength;
            while (j + lengthOfMatch < newString.size() && oldOffset + lengthOfMatch < oldString.size() && newString[j+lengthOfMatch] == oldString[oldOffset + lengthOfMatch])
            {
                lengthOfMatch++;
            }
            
//            length = lengthOfMatch;
            /*Once you have determined how long the match is (call this L),
             write a Copy instruction to the revision file to copy L bytes
             from offset F from the source file.*/
            if(lengthOfMatch >= sequenceLength)
            {
                frevision << "#" << oldOffset << "," << lengthOfMatch; // Copy Instruction
                j += lengthOfMatch;
//                oldOffset = 0;
            }
        }
        else // newSeq was not found in the hash table
        {
            length = 1;
            while (j + length < newString.size())
            {
                if(hashTable.contains(newString.substr(j + length, sequenceLength), oldOffset))
                    break;
                length++;
            }
            // Add the entire newSeq to our revision file
            string checker = newString.substr(j, length);
            bool hasDelimeter = false;
            for(int i = 0; i < checker.size(); i++) // this loop checks the substring in the new file to see if it contains the delimeter we want to use
            {
                if(checker[i] == '/')
                {
                    hasDelimeter = true;
                    break;
                }
            }
            if (hasDelimeter)
            {
                frevision << "+$" << newString.substr(j, length) << "$";
            }
            else
            {
                frevision << "+/" << newString.substr(j, length) << "/"; // Add Instruction
            }
            j += length;
        }
    }
}

bool revise(istream& fold, istream& frevision, ostream& fnew)
{
    // Create two variables to store the contents of the old file and the revision file
    string oldString;
    
    // If either the old file or revision file is in an invalid state then return false
    if(!fold)
        return false;
    if(!frevision)
        return false;
    
    // Copy the contents of the old file into a string
    char c = '\0';
    while (fold.get(c))
    {
        oldString += c;
    }
    
    // Use the getCommand utility function to determine if the revision file contains valid instructions
    while(frevision) //Loop through the revision file until it reached an invalid state
    {
        char cmd = '\0';
        char delim = '\0';
        int length = 0;
        int offset = 0;
        if(!getCommand(frevision, cmd, delim, length, offset))
            return false;
        
        switch (cmd) {
            case '+': // Add instruction
                {
                    if(length < 0)
                        return false;
    //                char c;
    //                while(length > 0) // Add all the characters until you hit the next delimiter
    //                {
    //                    if(!frevision.get(c)) // Handles the case where the length is invalid for the number of characters in the revision file
    //                        return false;
    //
    //                    fnew << c;
    //                    length--;
    //                }
                    string subString;
                    getline(frevision, subString, delim);
                    fnew << subString;
                    break;
                    
                }
            case '#': // Copy instruction
                /*If a Copy instruction specifies a length of 0 and an offset beyond the last 
                 character in the old file (e.g., #12,0 for an old file with 12 or fewer
                 characters), you may either consider it valid (and have it do nothing) or you
                 may consider it invalid (and have revise return false), your choice. */
                if(offset < 0 || length < 0 || offset + length > oldString.size())
                    return false;
                fnew << oldString.substr(offset, length);
                break;
                
            case '\r': // Do-Nothing for new line commands
            case '\n':
                break;
                
            case 'x': // Inidicates the end of the revision file
                break;
                
            default: // Some invalid character other than the required commands were added
                return false;
                break;
        }
    }
    
    return true;
}

