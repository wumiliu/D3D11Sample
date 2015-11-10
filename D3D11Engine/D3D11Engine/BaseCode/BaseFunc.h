#pragma once
#include "HpD3D9Type.h"

using namespace std;
wchar_t* gAnsiToUnicode(const char* szStr);
std::string UnicodeToANSI(const wchar_t* str);
 std::string& trim(std::string &s);


void		SplitInt(const string& strText, vector<int>& setNum, char cSplitChar, bool bCheckDoubleStr = false);
void		Split(const string& strText, vector<string>& setString, char cSplitChar, bool bCheckDoubleStr = false);
void CommentOutFunction(String& code, const String& signature);