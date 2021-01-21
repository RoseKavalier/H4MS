#pragma once
#include "stdafx.h"

class Path
{
public:
	static BOOL    IsDirectory(LPCTSTR name);
	static BOOL    IsDirectory(DWORD attribute);
	static BOOL    IsFile(LPCTSTR name);
	static BOOL    IsFile(DWORD attribute);
	static BOOL    IsValid(LPCTSTR name);
	static BOOL    IsValid(DWORD attribute);
	static BOOL    FileExists(LPCTSTR name);
	static BOOL    FileExists(DWORD attribute);
	static BOOL    CreateDir(const TString& dir);
	static DWORD   GetAttributes(LPCTSTR name);
	static TString CurrentDirectory();
	static BOOL    SetDirectory(LPCTSTR dir);
	static BOOL    SetDirectory(const TString& dir);
	static TString ProcessPath();
	static TString ModulePath(HMODULE hmodule);
	static TString GetDir(const TString& path);
	static TString DirUp(const TString& dir);
	static TString GetPathName(const TString& file);
	static TString GetPathName(LPCTSTR file);
	static LPCTSTR Extension(LPCTSTR file_name);
	static LPCTSTR Extension(const TString& file_name);

	class iterator
	{
	public:
		iterator(const TString& filename);
		iterator(HANDLE handle);
		~iterator();
		iterator& operator*();
		iterator& operator++();
		LPCTSTR   Extension() const;
		TString   FilePath() const;
		LPCTSTR   FileName() const;
		DWORD     Attributes() const;
		DWORD     FilseSize() const;
		BOOL      IsDirectory() const;
		BOOL      IsFile() const;
		BOOL      IsValid() const;
		BOOL      FileExists() const;
		BOOL      operator==(const iterator& other) const;
		BOOL      operator!=(const iterator& other) const;
	private:
		HANDLE m_handle;
		WIN32_FIND_DATA m_data;
	};

public:
	Path(const Path& path);
	Path(const TString& path);
	Path(LPCTSTR path);
	Path(Path&& path);
	Path& operator=(Path&& path);

	iterator begin() const;
	iterator end() const;

	Path&  operator=(const Path& path);
	Path&  operator+=(const Path& path);
	Path   operator/(const Path& path);
	Path&  operator/=(const Path& path);
	BOOL   operator!=(const Path& path) const;
	BOOL   operator==(const Path& path) const;
	Path&  Append(const Path& path);
	BOOL   IsValid() const;
	BOOL   IsDirectory() const;
	BOOL   IsFile() const;
	BOOL   IsRoot() const;
	BOOL   CreateDir() const;
	BOOL   FileExists() const;
	BOOL   ReplaceExtension(const TString& ext);
	TString GetExtension() const;
	operator LPCTSTR() const;
	const TString& GetPath() const;
private:
	TString  m_path;
	DWORD    m_attributes;
};

class DirectoryChanger
{
public:
	DirectoryChanger(const TString& path);
	DirectoryChanger(const TString& path, bool& successfully_changed);
	DirectoryChanger(LPCTSTR path);
	DirectoryChanger(LPCTSTR path, bool& successfully_changed);
	~DirectoryChanger();
	bool IsModified() const;
private:
	TCHAR m_currentDirectory[MAX_PATH];
	bool m_success;
};