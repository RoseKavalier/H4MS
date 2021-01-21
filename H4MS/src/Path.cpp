#include "stdafx.h"
#include "Path.hpp"

 Path::iterator::iterator(const TString & filename) :
	m_handle(FindFirstFile(filename.c_str(), &m_data))
{
}
 Path::iterator::iterator(HANDLE handle) :
	m_handle(handle), m_data()
{
}
 Path::iterator::~iterator()
{
	if (m_handle && m_handle != INVALID_HANDLE_VALUE)
		FindClose(m_handle);
}
 Path::iterator& Path::iterator::operator*()
{
	return *this;
}
 Path::iterator& Path::iterator::operator++()
{
	if (m_handle && m_handle != INVALID_HANDLE_VALUE)
	{
		if (!FindNextFile(m_handle, &m_data))
		{
			FindClose(m_handle);
			m_handle = INVALID_HANDLE_VALUE;
		}
	}
	return *this;
}
 LPCTSTR Path::iterator::Extension() const
{
	return Path::Extension(m_data.cFileName);
}
 TString Path::iterator::FilePath() const
{
	return GetPathName(FileName());
}
 LPCTSTR Path::iterator::FileName() const
{
	return m_data.cFileName;
}
 DWORD Path::iterator::Attributes() const
{
	return m_data.dwFileAttributes;
}
 DWORD Path::iterator::FilseSize() const
{
	return m_data.nFileSizeLow;
}
 BOOL Path::iterator::IsDirectory() const
{
	return Path::IsDirectory(Attributes());
}
 BOOL Path::iterator::IsFile() const
{
	return Path::IsFile(Attributes());
}

 BOOL Path::iterator::IsValid() const
{
	return Path::IsValid(Attributes());
}

 BOOL Path::iterator::FileExists() const
{
	return Path::FileExists(Attributes());
}

 BOOL Path::iterator::operator==(const iterator & other) const
{
	if (this == &other)
		return TRUE;
	return m_handle == other.m_handle;
}

 BOOL Path::iterator::operator!=(const iterator & other) const
{
	return !(*this == other);
}

 BOOL Path::IsDirectory(LPCTSTR name)
{
	return IsDirectory(GetAttributes(name));
}
 BOOL Path::IsFile(LPCTSTR name)
{
	return IsFile(GetAttributes(name));
}
 BOOL Path::IsValid(LPCTSTR name)
{
	return IsValid(GetAttributes(name));
}
 BOOL Path::FileExists(LPCTSTR name)
{
	return FileExists(GetAttributes(name));
}
 BOOL Path::IsDirectory(DWORD attribute)
{
	return IsValid(attribute) && attribute & FILE_ATTRIBUTE_DIRECTORY;
}
 BOOL Path::IsFile(DWORD attribute)
{
	return IsValid(attribute) && !(attribute & FILE_ATTRIBUTE_DIRECTORY);
}
 BOOL Path::IsValid(DWORD attribute)
{
	return attribute != INVALID_FILE_ATTRIBUTES;
}
 BOOL Path::FileExists(DWORD attribute)
{
	return IsValid(attribute) && (attribute & FILE_ATTRIBUTE_ARCHIVE);
}
 DWORD Path::GetAttributes(LPCTSTR name)
{
	return GetFileAttributes(name);
}
 TString Path::CurrentDirectory()
{
	TCHAR tmp[MAX_PATH];
	if (GetCurrentDirectory(MAX_PATH, tmp))
	{
		TString dir(tmp);
		dir += TCHAR('\\');
		return dir;
	}
	return TString();
}
 BOOL Path::SetDirectory(LPCTSTR dir)
 {
	 return SetCurrentDirectory(dir);
 }
 BOOL Path::SetDirectory(const TString & dir)
 {
	 return SetCurrentDirectory(dir.c_str());
 }
 TString Path::ProcessPath()
{
	return ModulePath(NULL);
}
 TString Path::ModulePath(HMODULE hmodule)
{
	TCHAR tmp[MAX_PATH];
	if (GetModuleFileName(hmodule, tmp, MAX_PATH))
	{
		TString path(tmp);
		return GetDir(path);
	}
	return TString();
}
 TString Path::GetDir(const TString & path)
{
	if (path.empty() || path.length() < 3)
		return TString();

	size_t len = path.length() - 1;

	while (len >= 3)
	{
		if (path[len] == TCHAR('/') || path[len] == TCHAR('\\'))
			return TString(path.c_str(), len + 1);

		--len;
	}
	return TString();
}
 TString Path::DirUp(const TString & dir)
{
	if (dir.empty() || dir.length() < 3)
		return TString();

	size_t len = dir.length() - 1;
	BOOL first = TRUE;
	while (len >= 3)
	{
		if (dir[len] == TCHAR('/') || dir[len] == TCHAR('\\'))
		{
			if (!first)
				return TString(dir.c_str(), len + 1);
			first = FALSE;
		}
		--len;
	}
	return TString();
}
 BOOL Path::CreateDir(const TString & dir)
{
	if (dir.empty())
		return false;

	if (CreateDirectory(dir.c_str(), 0))
		return true;

	if (!CreateDir(DirUp(dir))) // recursively create upper directories
		return false;

	return CreateDirectory(dir.c_str(), 0);
}

 TString Path::GetPathName(const TString& file)
{
	return GetPathName(file.c_str());
}

 TString Path::GetPathName(LPCTSTR file)
{
	TCHAR tmp[MAX_PATH + 1];
	if (GetFullPathName(file, MAX_PATH, tmp, NULL))
		return TString(tmp);
	return TString();
}

 LPCTSTR Path::Extension(LPCTSTR file_name)
{
	size_t length, len;
	length = len = Tstrlen(file_name);
	if (len == 0)
		return file_name;
	--len;
	while (len > 0)
	{
		if (file_name[len] == TCHAR('.'))
			return file_name + len + 1;
		--len;
	}
	return file_name + length;
}

 LPCTSTR Path::Extension(const TString& file_name)
{
	UINT32 len = file_name.length();
	if (len == 0)
		return file_name.c_str();
	--len;
	while (len > 0)
	{
		if (file_name[len] == TCHAR('.'))
			return file_name.c_str() + len - 1;
		--len;
	}
	return file_name.c_str() + len;
}

 Path::Path(const Path& path) :
	m_path(path.m_path), m_attributes(path.m_attributes)
{
}
 Path::Path(const TString & path) :
	m_path(path), m_attributes(GetAttributes(path.c_str()))
{
	if (IsDirectory())
	{
		TCHAR last = m_path.back();
		if (last != TCHAR('/') && last != TCHAR('\\'))
			m_path += TCHAR('/');
	}
}
 Path::Path(LPCTSTR path) :
	m_path(path), m_attributes(GetAttributes(path))
{
}

 Path::Path(Path&& path) :
	m_path(std::move(path.m_path)), m_attributes(path.m_attributes)
{
}
 Path & Path::operator=(Path && path)
{
	m_path.clear();
	m_path = std::move(path.m_path);
	m_attributes = path.m_attributes;
	return *this;
}

 Path::iterator Path::begin() const
{
	if (IsDirectory())
	{
		TString p(m_path);
		p += TCHAR('*');
		return iterator(p);
	}
	return iterator(m_path);
}
 Path::iterator Path::end() const
{
	return iterator(INVALID_HANDLE_VALUE);
}
 Path & Path::operator=(const Path & path)
{
	m_path.clear();
	m_path = path.m_path;
	m_attributes = path.m_attributes;
	return *this;
}
 Path & Path::operator+=(const Path & path)
{
	m_path += path.m_path;
	m_attributes = GetAttributes(m_path.c_str());
	return *this;
}
 Path Path::operator/(const Path & path)
{
	TString tmp(m_path);
	if (!(tmp.back() == TCHAR('/') || tmp.back() == TCHAR('\\')))
		tmp += TCHAR('/');
	tmp += path.m_path;
	return Path(tmp);
}
 Path & Path::operator/=(const Path & path)
{
	if (!(m_path.back() == TCHAR('/') || m_path.back() == TCHAR('\\')))
		m_path += TCHAR('/');
	m_path += path.m_path;
	m_attributes = GetAttributes(m_path.c_str());
	return *this;
}
 BOOL Path::operator!=(const Path & path) const
{
	return !(m_path == path.m_path);
}
 BOOL Path::operator==(const Path & path) const
{
	return m_path == path.m_path;
}
 Path & Path::Append(const Path & path)
{
	return operator/=(path);
}
 BOOL Path::IsValid() const
{
	return IsValid(m_attributes);
}
 BOOL Path::IsDirectory() const
{
	return IsDirectory(m_attributes);
}
 BOOL Path::IsFile() const
{
	return IsFile(m_attributes);
}
 BOOL Path::IsRoot() const
{
	if (m_path.length() == 1 && m_path[0] == TCHAR('/'))
		return true;
	return m_path.length() == 3 && m_path[1] == TCHAR(':');
}
 BOOL Path::CreateDir() const
{
	return CreateDir(m_path);
}
 BOOL Path::FileExists() const
{
	return FileExists(m_attributes);
}
 BOOL Path::ReplaceExtension(const TString & ext)
{
	if (ext.empty())
		return FALSE;

	TString currExt = GetExtension();
	if (currExt.empty())
		return FALSE;
	size_t dot = 0;
	if (ext[0] == TCHAR('.'))
		dot = 1;
	m_path.erase(m_path.length() - currExt.length() - dot, TString::npos);
	m_path += ext;
	return TRUE;
}
 TString Path::GetExtension() const
{
	if (!IsFile())
		return TString();

	INT32 pos = m_path.find_last_of(TCHAR('.'));
	if (pos == TString::npos)
		return TString();

	return TString(m_path.c_str() + pos + 1);
}
 const TString& Path::GetPath() const
{
	return m_path;
}
 Path::operator LPCTSTR() const
{
	return m_path.c_str();
}

 DirectoryChanger::DirectoryChanger(const TString & path) : DirectoryChanger(path.c_str())
 {
 }

 DirectoryChanger::DirectoryChanger(const TString & path, bool & successfully_changed) : DirectoryChanger(path)
 {
	 successfully_changed = m_success;
 }

 DirectoryChanger::DirectoryChanger(LPCTSTR path) : m_currentDirectory(), m_success(false)
 {
	 if (GetCurrentDirectory(MAX_PATH, m_currentDirectory))
	 {
		m_currentDirectory[MAX_PATH - 1] = 0;
		m_success = SetCurrentDirectory(path);
	 }
 }

 DirectoryChanger::DirectoryChanger(LPCTSTR path, bool & successfully_changed) : DirectoryChanger(path)
 {
	 successfully_changed = m_success;
 }

 DirectoryChanger::~DirectoryChanger()
 {
	 if (m_success)
		Path::SetDirectory(m_currentDirectory);
 }

 bool DirectoryChanger::IsModified() const
 {
	 return m_success;
 }
