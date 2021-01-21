#include "stdafx.h"
#include "logger.hpp"

Logger::Logger(const TString& directory) : m_file(), m_path(directory)
{
	SYSTEMTIME tim;
	GetLocalTime(&tim);
	TCHAR buffer[MAX_PATH];
	m_path += _T("debug\\H4MS debug [");
	_stprintf_s(buffer, _T("%04d.%02d.%02d - %02dh%02dm%02ds"), tim.wYear, tim.wMonth, tim.wDay, tim.wHour, tim.wMinute, tim.wSecond);
	m_path += buffer;
	m_path += _T("].txt");
}

Logger::~Logger()
{
}

void Logger::log_debug(LPCSTR text)
{
#ifdef _DEBUG
	log(text);
#endif
}

void Logger::log_debug(const std::string & text)
{
#ifdef _DEBUG
	log(text);
#endif
}

void Logger::log(LPCSTR text)
{
	if (open())
	{
		write(text, strlen(text));
		next_error();
		close();
	}
}

void Logger::log(const std::string & text)
{
	if (open())
	{
		write(text.c_str(), text.length());
		next_error();
		close();
	}
}

void Logger::plugin_error(const std::string & name, const std::exception & e)
{
	if (open())
	{
		std::string error(u8"Error in module [" + name + u8"]\r\n\t");
		m_file.Write(error);
		m_file.Write(ansi_to_utf8(e.what()));
		next_error();
		close();
	}
}

bool Logger::open()
{
	if (m_path.empty())
		return false;
	return m_file.OpenToWrite(m_path, true);
}

void Logger::close()
{
	m_file.Close();
}

bool Logger::next_error()
{
	constexpr CHAR err[] = "\r\n";
	return write(err, std::size(err) - 1);
}

bool Logger::write(LPCSTR utf8_string, size_t len)
{
	return m_file.Write(utf8_string, len);
}
