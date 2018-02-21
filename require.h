//: :require.h
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Test for error conditions in programs
// Local "using namespace std" for old compilers
#ifndef REQUIRE_H
#define REQUIRE_H
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include "globals.h"

inline void Globals::assure(std::ifstream& in, 
  const std::string& filename = "") {
  using namespace std;
  if(!in) {
    fprintf(stderr, "Could not open file %s\n",
      filename.c_str());
    exit(1);
  }
}

inline void Globals::assure(std::ofstream& out, 
  const std::string& filename = "") {
  using namespace std;
  if(!out) {
    fprintf(stderr, "Could not open file %s\n", 
      filename.c_str());
    exit(1);
  }
}

inline void Globals::assure(FILE *file, char* nm)
{
  if (file==NULL) {
    cout << "Could not open " << nm << "!" << endl;
    exit(1);
  }
}

#endif // REQUIRE_H ///:~
