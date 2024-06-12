//
//  main.cpp
//  s24Project4
//
//  Created by Cameron Maiden on 6/9/24.
//

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <cassert>
#include "Revision.h"
#include "HashTable.h"
using namespace std;

bool runtest(string oldName, string newName, string revisionName, string newName2)
{
    if (revisionName == oldName  ||  revisionName == newName  ||
        newName2 == oldName  ||  newName2 == revisionName  ||
        newName2 == newName)
    {
        cerr << "Files used for output must have names distinct from other files" << endl;
        return false;
    }
    ifstream oldFile(oldName, ios::binary);
    if (!oldFile)
    {
        cerr << "Cannot open " << oldName << endl;
        return false;
    }
    ifstream newFile(newName, ios::binary);
    if (!newFile)
    {
        cerr << "Cannot open " << newName << endl;
        return false;
    }
    ofstream revisionFile(revisionName, ios::binary);
    if (!revisionFile)
    {
        cerr << "Cannot create " << revisionName << endl;
        return false;
    }
    createRevision(oldFile, newFile, revisionFile);
    revisionFile.close();

    oldFile.clear();   // clear the end of file condition
    oldFile.seekg(0);  // reset back to beginning of the file
    ifstream revisionFile2(revisionName, ios::binary);
    if (!revisionFile2)
    {
        cerr << "Cannot read the " << revisionName << " that was just created!" << endl;
        return false;
    }
    ofstream newFile2(newName2, ios::binary);
    if (!newFile2)
    {
        cerr << "Cannot create " << newName2 << endl;
        return false;
    }
    assert(revise(oldFile, revisionFile2, newFile2));
    newFile2.close();

    newFile.clear();
    newFile.seekg(0);
    ifstream newFile3(newName2, ios::binary);
    if (!newFile)
    {
        cerr << "Cannot open " << newName2 << endl;
        return false;
    }
    if ( ! equal(istreambuf_iterator<char>(newFile), istreambuf_iterator<char>(),
                 istreambuf_iterator<char>(newFile3), istreambuf_iterator<char>()))
    {
        cerr << newName2 << " is not identical to " << newName
        << "; test FAILED" << endl;
        return false;
    }
    return true;
}

int main()
{
    assert(runtest("greeneggs1.txt", "greeneggs2.txt", "revision.txt", "newGreenEggs.txt"));
    assert(runtest("strange1.txt", "strange2.txt", "revision.txt", "newStrange.txt"));
//    assert(runtest("mallmart1.txt", "mallmart2.txt", "revision.txt", "newMallmart.txt"));
    assert(runtest("warandpeace1.txt", "warandpeace2.txt", "revision.txt", "newWarandPeace.txt"));
//    ofstream outfile("results.txt");
//    if(! outfile)
//    {
//        cerr << "Error: Cannot create results.txt!" << endl;
//        exit(1);
//    }
//    outfile << "This will be written to the file" << endl;
//    outfile << "2 + 2 = " << 2+2 << endl;
//    outfile << "This will also be written to the same file (I think...)" << endl;
//
//    ifstream infile("greeneggs1.txt");    // infile is a name of our choosing
//    if ( ! infile )                // Did opening the file fail?
//    {
//        cerr << "Error: Cannot open data.txt!" << endl;
//        exit(1);
//    }
//
//    string w;
//    infile >> w;
//    string line;
//    getline(infile, line);
//    char c;
//    infile.get(c);
//
//    cout << "word extracted from infile: " << w << endl;
//    cout << "line extracted from the infile: " << line << endl;
//    cout << "char extracted from the infile: " << c << endl;

//    HashTable ht;
//    size_t offset = 4;
//    size_t o;
//    ht.insert("this is a test insert", offset);
//    assert(ht.contains("this is a test insert", o));
//    assert(!ht.contains("this is a test", o));
//    assert(o == 4);
//    
//    ifstream oldFile("greeneggs1.txt");
//    if ( ! oldFile )                // Did opening the file fail?
//    {
//        cerr << "Error: Cannot open data.txt!" << endl;
//        exit(1);
//    }
//
//    ifstream revisionFile("revFile.txt");
//    ofstream newFile("newFile.txt");
//    assert(revise(oldFile, revisionFile, newFile));
//
    cerr << "Test PASSED" << endl;
}

/////////// TEST 2 GIVEN BY SMALLBERG

//#include <iostream>
//#include <sstream>  // for istringstream and ostringstream
//#include <string>
//#include <cassert>
//using namespace std;
//
//void runtest(string oldtext, string newtext)
//{
//    istringstream oldFile(oldtext);
//    istringstream newFile(newtext);
//    ostringstream revisionFile;
//    createRevision(oldFile, newFile, revisionFile);
//    string result = revisionFile.str();
//    cout << "The revision file length is " << result.size()
//    << " and its text is " << endl;
//    cout << result << endl;
//    
//    oldFile.clear();   // clear the end of file condition
//    oldFile.seekg(0);  // reset back to beginning of the stream
//    istringstream revisionFile2(result);
//    ostringstream newFile2;
//    assert(revise(oldFile, revisionFile2, newFile2));
//    assert(newtext == newFile2.str());
//}
//
//int main()
//{
//    runtest("There's a bathroom on the right.",
//            "There's a bad moon on the rise.");
//    runtest("ABCDEFGHIJBLAHPQRSTUVPQRSTUV",
//            "XYABCDEFGHIJBLETCHPQRSTUVPQRSTQQ/OK");
//    cout << "All tests passed" << endl;
//}
