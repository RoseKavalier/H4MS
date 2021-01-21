#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
#include <windows.h>

#include <string>
#include <vector>
#include <tchar.h>
#include <patcher_x86.hpp>
#include <H4API.hpp>
#include <Plugin.hpp>

#ifdef UNICODE
typedef std::wstring TString;
#define Tstrlen lstrlenW
#define Tifstream std::wifstream
#else
typedef std::string TString;
#define Tstrlen lstrlenA
#define Tifstream std::ifstream
#endif

void ShowError(LPCTSTR message, LPCTSTR file, int line);

#define SHOW_ERROR(message) ::ShowError(message, __FILEW__, __LINE__);

#ifdef UNICODE
TString ansi_to_tstring(const std::string& ansi_string);
#else
TString& ansi_to_tstring(const std::string& ansi_string);
#endif
TString utf8_to_tstring(const std::string& utf8_string);
std::string tstring_to_utf8(const TString& tchar_string);
std::string tstring_to_ansi(const TString& tchar_string);
std::string ansi_to_utf8(const std::string& ansi_string);
std::string utf8_to_ansi(const std::string& utf8_string);
std::wstring ansi_to_wstring(const std::string& ansi_string);
std::wstring utf8_to_wstring(const std::string& utf8_string);
std::string wstring_to_ansi(const std::wstring& wstring);
std::string wstring_to_utf8(const std::wstring& wstring);