#include "stdafx.h"

void ShowError(LPCTSTR message, LPCTSTR file, int line)
{
	TCHAR linetext[32];
	_stprintf_s(linetext, _T("%d"), line);

	TString error(message);
	error = error + _T("\n\nIn file:\n\n") + file + _T("\n\nAt line:\n\n") + linetext;

	MessageBox(nullptr, error.c_str(), _T("H4MS error!"), MB_ICONERROR);
	ExitProcess(0);
}

#ifdef UNICODE
TString ansi_to_tstring(const std::string & ansi_string)
#else
TString ansi_to_tstring(const std::string & ansi_string)
#endif
{
#ifdef UNICODE
	return ansi_to_wstring(ansi_string);
#else
	return ansi_string;
#endif
}

TString utf8_to_tstring(const std::string & utf8_string)
{
#ifdef UNICODE
	return utf8_to_wstring(utf8_string);
#else
	return utf8_to_ansi(utf8_string);
#endif
}

std::string tstring_to_utf8(const TString & tchar_string)
{
#ifdef UNICODE
	return wstring_to_utf8(tchar_string);
#else
	return ansi_to_tstring(tchar_string);
#endif
}

std::string tstring_to_ansi(const TString& tchar_string)
{
	std::string ansi;
#ifdef UNICODE
	return wstring_to_ansi(tchar_string);
#else
	return tchar_string;
#endif
}

std::string ansi_to_utf8(const std::string & ansi_string)
{
	std::wstring wstring = ansi_to_wstring(ansi_string);
	return wstring_to_utf8(wstring);
}

std::string utf8_to_ansi(const std::string & utf8_string)
{
	std::wstring wstring = utf8_to_wstring(utf8_string);
	return wstring_to_ansi(wstring);
}

std::wstring ansi_to_wstring(const std::string & ansi_string)
{
	int nLength = MultiByteToWideChar(CP_ACP, 0, ansi_string.c_str(), -1, NULL, NULL);
	std::wstring unicode;
	unicode.resize(nLength - 1);
	MultiByteToWideChar(CP_ACP, 0, ansi_string.c_str(), -1, &unicode[0], nLength);
	return unicode;
}

std::wstring utf8_to_wstring(const std::string & utf8_string)
{
	int nLength = MultiByteToWideChar(CP_UTF8, 0, utf8_string.c_str(), -1, NULL, NULL);
	std::wstring unicode;
	unicode.resize(nLength - 1);
	MultiByteToWideChar(CP_UTF8, 0, utf8_string.c_str(), -1, &unicode[0], nLength);
	return unicode;
}

std::string wstring_to_ansi(const std::wstring & wstring)
{
	int nLength = WideCharToMultiByte(CP_ACP, 0, wstring.c_str(), -1, NULL, 0, NULL, NULL);
	std::string ansi;
	ansi.resize(nLength - 1);
	WideCharToMultiByte(CP_ACP, 0, wstring.c_str(), -1, &ansi[0], nLength, NULL, NULL);
	return ansi;
}

std::string wstring_to_utf8(const std::wstring & wstring)
{
	int nLength = WideCharToMultiByte(CP_UTF8, 0, wstring.c_str(), -1, NULL, 0, NULL, NULL);
	std::string utf8;
	utf8.resize(nLength - 1);
	WideCharToMultiByte(CP_UTF8, 0, wstring.c_str(), -1, &utf8[0], nLength, NULL, NULL);
	return utf8;
}
