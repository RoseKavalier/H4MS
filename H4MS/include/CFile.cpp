#include "stdafx.h"
#include "CFile.hpp"

CFile::CFile() : m_file(), m_position(), m_size(), m_safeEnd()
{
}

CFile::~CFile()
{
	Close();
}

bool CFile::OpenToWrite(const TString & name, bool append)
{
	return 0 == _tfopen_s(&m_file, name.c_str(), append ? _T("ab+") : _T("wb+"));
}

bool CFile::OpenToRead(const TString & name, bool read_to_buffer)
{
	if (0 != _tfopen_s(&m_file, name.c_str(), _T("rb")))
		return false;

	std::fseek(m_file, 0, SEEK_END);
	m_size = std::ftell(m_file);
	std::fseek(m_file, 0, SEEK_SET);

	if (!read_to_buffer)
		return true;

	m_buffer = std::make_unique<char[]>(m_size);
	return read(m_buffer.get(), m_size);
}

bool CFile::Write(const std::string & utf8_string)
{
	return write(utf8_string.c_str(), utf8_string.length());
}

bool CFile::Write(LPCSTR utf8_text)
{
	return write(utf8_text, strlen(utf8_text));
}

bool CFile::Write(LPCSTR utf8_text, size_t length)
{
	return write(utf8_text, length);
}

const char * CFile::begin() const
{
	if (!m_buffer)
		return &m_safeEnd;
	return m_buffer.get();
}

const char * CFile::end() const
{
	if (!m_buffer)
		return &m_safeEnd;
	return m_buffer.get() + m_size;
}

char * CFile::begin()
{
	if (!m_buffer)
		return const_cast<char*>(&m_safeEnd);
	return m_buffer.get();
}

char * CFile::end()
{
	if (!m_buffer)
		return const_cast<char*>(&m_safeEnd);
	return m_buffer.get() + m_size;
}

void CFile::Close()
{
	if (m_file)
	{
		std::fclose(m_file);
		m_file = nullptr;
	}
}

bool CFile::read(void * data, size_t sz)
{
	if (m_position + sz > m_size)
		return false;

	if (std::fread(data, 1, sz, m_file) != sz)
		return false;
	m_position += sz;
	return true;
}

bool CFile::write(const void * data, size_t sz)
{
	return std::fwrite(data, 1, sz, m_file) == sz;
}
