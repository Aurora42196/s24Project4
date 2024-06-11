//
//  utilities.h
//  s24Project4
//
//  Created by Cameron Maiden on 6/10/24.
//

#ifndef utilities_h
#define utilities_h

#include <iostream>
#include <fstream>

////////////////////////////////////////////////////////////////////////////// Functions given to me from Smallberg to help extract instructions from the revision file
bool getInt(std::istream& inf, int& n)
{
    char ch;
    if (!inf.get(ch)  ||  !isascii(ch)  ||  !isdigit(ch))
        return false;
    inf.unget();
    inf >> n;
    return true;
}

bool getCommand(std::istream& inf, char& cmd, char& delim, int& length, int& offset)
{
    if (!inf.get(cmd))
    {
        cmd = 'x';  // signals end of file
        return true;
    }
    switch (cmd)
    {
        case '+':
            return inf.get(delim).good();
        case '#':
        {
            char ch;
            return getInt(inf, offset) && inf.get(ch) && ch == ',' && getInt(inf, length);
        }
        case '\r':
        case '\n':
            return true;
    }
    return false;
}

#endif /* utilities_h */
