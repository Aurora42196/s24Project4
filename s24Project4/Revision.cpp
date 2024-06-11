//
//  Revision.cpp
//  s24Project4
//
//  Created by Cameron Maiden on 6/10/24.
//

#include "Revision.h"
#include "utilities.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void createRevision(istream& fold, istream& fnew, ostream& frevision)
{
    
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

