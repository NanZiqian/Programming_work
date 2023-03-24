#ifndef __STEMIZE__
#define __STEMIZE__

#include "stmr.h"
#include <string.h>
#include <string>
using namespace std;

#define Is_Char(a) ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'))

/// @brief This function stem the word with the help of stmr lib.
string stemize(string word);

#endif