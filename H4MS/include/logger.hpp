#pragma once

#include "stdafx.h"
#include "CFile.hpp"

class Logger
{
public:
	Logger(const TString& directory);
	~Logger();
	void log_debug(LPCSTR utf8);
	void log_debug(const std::string& utf8);
	void log(LPCSTR text);
	void log(const std::string& text);
	void plugin_error(const std::string& name, const std::exception& e);

private:
	bool open();
	void close();
	bool next_error();
	bool write(LPCSTR utf8_string, size_t len);

private:
	CFile m_file;
	TString m_path;
};