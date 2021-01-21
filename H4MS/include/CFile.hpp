#pragma once

#include "stdafx.h"

class CFile
{
public:
	CFile();
	~CFile();
	bool OpenToWrite(const TString& name, bool append);
	bool OpenToRead(const TString& name, bool read_to_buffer);

	template<typename T>
	bool Read(T& data, size_t sz = sizeof(T));
	bool Write(const std::string& utf8_string);
	bool Write(LPCSTR utf8_text);
	bool Write(LPCSTR utf8_text, size_t length);

	const char* begin() const;
	const char* end() const;
	char* begin();
	char* end();

	void Close();

private:
	bool read(void* data, size_t sz);
	bool write(const void* data, size_t sz);

	FILE* m_file;
	size_t m_position;
	size_t m_size;
	std::unique_ptr<char[]> m_buffer;
	const char m_safeEnd;
};

template<typename T>
inline bool CFile::Read(T & data, size_t sz)
{
	return read(reinterpret_cast<void*>(data), sz);
}
