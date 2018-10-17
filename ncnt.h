#include <iostream>
#include <stdio.h>
#include <string.h>
#include <iomanip>
using namespace std;

//declarations
void countAlpha(char buffer[], size_t bytes_read, int n, bool caseSensitive, bool verbose);
void countBytes(char buffer[], size_t bytes_read, bool hex, bool verbose);
void countNybbles(char buffer[], size_t bytes_read, bool hex, bool verbose);
string intToASCIIHex(int x);
