//
//  Revision.h
//  s24Project4
//
//  Created by Cameron Maiden on 6/10/24.
//

#ifndef Revision_h
#define Revision_h

#include <iostream>
#include <fstream>



void createRevision(std::istream& fold, std::istream& fnew, std::ostream& frevision);
/* This function takes the contents of two files, A and A', and produces a revision file containing
 instructions for converting A into A'. Each day, Mallmart will use this function at their
 corporate headquarters to create a new revision file that they will then send to all the devices. */

bool revise(std::istream& fold, std::istream& frevision, std::ostream& fnew);
/* This function takes the content of a file A and a revision file, and will apply the instructions 
 in the revision file to produce a new file A'. Each day, every device will use this function to
 update the previous day's inventory file. */

#endif /* Revision_h */
