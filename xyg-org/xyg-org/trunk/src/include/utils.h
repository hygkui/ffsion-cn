#ifndef UTILS_H_
#define UTILS_H_
#include <string>
using namespace std;

string trim(string& s);

string credential(const char *sid, const char *pwd, const char *domain, const char *nonce, const char *cnonce);

string toString(const int i);

int toInteger(const string str);

#endif /*UTILS_H_*/
