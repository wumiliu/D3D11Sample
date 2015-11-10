#include "BaseFunc.h"



void SplitInt(const string& strText, vector<int>& setNum, char szSplitChar, bool bCheckDoubleStr /*= false*/)
{
	char szDestribe[1024] = { 0 };
	strcpy_s(szDestribe, strText.c_str());

	int nIndex = 0;
	const char* pBeg = szDestribe;
	const char* pPos = strchr(pBeg, szSplitChar);
	while (pPos)
	{
		char szTem[255] = { 0 };
		strncpy_s(szTem, pBeg, pPos - pBeg);
		setNum.push_back(atoi(szTem));
		pBeg = pPos + 1;
		pPos = strchr(pPos + 1, szSplitChar);
	}
	setNum.push_back(atoi(pBeg));
}

void Split(const string& strText, vector<string>& setString, char szSplitChar, bool bCheckDoubleStr /*= false*/)
{
	char szDestribe[1024] = { 0 };
	strcpy_s(szDestribe, strText.c_str());

	int nIndex = 0;
	const char* pBeg = szDestribe;
	const char* pPos = strchr(pBeg, szSplitChar);
	while (pPos)
	{
		char szTem[255] = { 0 };
		strncpy_s(szTem, pBeg, pPos - pBeg);
		setString.push_back(szTem);
		pBeg = pPos + 1;
		pPos = strchr(pPos + 1, szSplitChar);
	}
	setString.push_back(pBeg);
}

void CommentOutFunction(String& code, const String& signature)
{
	unsigned startPos = code.find(signature.c_str());
	unsigned braceLevel = 0;
	if (startPos == String::npos)
		return;
	code.insert(startPos, "/*");

	for (unsigned i = startPos + 2 + signature.size(); i < code.size(); ++i)
	{
		if (code[i] == '{')
			++braceLevel;
		else if (code[i] == '}')
		{
			--braceLevel;
			if (braceLevel == 0)
			{
				code.insert(i + 1, "*/");
				return;
			}
		}
	}
}

wchar_t* gAnsiToUnicode(const char* szStr)
{
	int nLen = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szStr, -1, NULL, 0);
	if (nLen == 0)
	{
		return NULL;
	}
	wchar_t* pResult = new wchar_t[nLen];
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szStr, -1, pResult, nLen);
	return pResult;
}

std::string UnicodeToANSI(const wchar_t* str)
{
	char*     pElementText;
	int    iTextLen;
	// wide char to multi char
	iTextLen = WideCharToMultiByte(CP_ACP,
		0,
		str,
		-1,
		NULL,
		0,
		NULL,
		NULL);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, sizeof(char)* (iTextLen + 1));
	::WideCharToMultiByte(CP_ACP,
		0,
		str,
		-1,
		pElementText,
		iTextLen,
		NULL,
		NULL);
	std::string strText;
	strText = pElementText;
	delete[] pElementText;
	return strText;
}

std::string& trim(std::string &s)
{
	if (s.empty())
	{
		return s;
	}
	const std::string drop = " ";
	std::string stTmp = "";
	int nPos = s.find_first_of(drop);
	int i = 0;
	while (nPos != std::string::npos && i <= 8)
	{
		stTmp = s.erase(nPos, 1);
		nPos = s.find_first_of(drop);
		i++;
	}
	// trim right
	s.erase(s.find_last_not_of(drop) + 1);
	// trim left
	return s.erase(0, s.find_first_not_of(drop));
}


