#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shlwapi.h>
#include <shellapi.h>
#include <string>
#include <codecvt>
#include <fstream>
#include  <vector>
#include <string>
#include "log.h"

//static const wchar_t* TAG = L"<seraphim>";
using std::vector;
using std::wstring;
using std::string;

#pragma comment(lib,"shlwapi.lib")

#define HELPER_A2W(x) Tools::a2w(x)
#define HELPER_W2A(x) Tools::w2a(x)
#define HELPER_W2U(x) Tools::w2u(x)
#define HELPER_U2W(x) Tools::u2w(x)
#define HELPER_A2U(x) Tools::a2u(x)
#define HELPER_U2A(x) Tools::u2a(x)
using std::string;
namespace seraphim {
	class Tools
	{
	public:
		static std::wstring u2w(const std::string& utf8Str)
		{
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
			return conv.from_bytes(utf8Str);
		}

		static std::string w2u(const std::wstring& utf16Str)
		{
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
			return conv.to_bytes(utf16Str);
		}

		static std::string u2a(const std::string& str)
		{
			std::wstring w;
			auto l = MultiByteToWideChar(CP_UTF8, NULL, str.c_str(), -1, NULL, NULL);
			w.resize(l - 1);
			l = MultiByteToWideChar(CP_UTF8, NULL, str.c_str(), -1, &w[0], l);
			l = WideCharToMultiByte(CP_ACP, NULL, w.c_str(), -1, NULL, NULL, NULL, NULL);
			std::string u;
			u.resize(l - 1);
			l = WideCharToMultiByte(CP_ACP, NULL, w.c_str(), -1, &u[0], l, NULL, NULL);
			return u;
		}

		static std::string a2u(const std::string& str)
		{
			std::wstring w;
			auto l = MultiByteToWideChar(CP_ACP, NULL, str.c_str(), -1, NULL, NULL);
			w.resize(l - 1);
			l = MultiByteToWideChar(CP_ACP, NULL, str.c_str(), -1, &w[0], l);
			l = WideCharToMultiByte(CP_UTF8, NULL, w.c_str(), -1, NULL, NULL, NULL, NULL);
			std::string u;
			u.resize(l - 1);
			l = WideCharToMultiByte(CP_UTF8, NULL, w.c_str(), -1, &u[0], l, NULL, NULL);
			return u;
		}

		static std::wstring a2w(const std::string& str)
		{
			std::wstring w;
			auto l = MultiByteToWideChar(CP_ACP, NULL, str.c_str(), -1, NULL, NULL);
			w.resize(l - 1);
			l = MultiByteToWideChar(CP_ACP, NULL, str.c_str(), -1, &w[0], l);
			return w;
		}

		static std::string w2a(const std::wstring& w)
		{
			auto l = WideCharToMultiByte(CP_ACP, NULL, w.c_str(), -1, NULL, NULL, NULL, NULL);
			std::string a;
			a.resize(l - 1);
			l = WideCharToMultiByte(CP_ACP, NULL, w.c_str(), -1, &a[0], l, NULL, NULL);
			return a;
		}

		static __int64 ZipFloder(const string& srcDirect, const string& archivePath) {
			do {
				string strPath = PathUnExpandEnv(srcDirect);
				string dstFile = PathUnExpandEnv(archivePath);
				if (!FileExist(strPath))
				{
					break;
				}

				// 压缩
				string str7zexe = GetAppBasePath("7za.exe");
				if (!FileExist(str7zexe))
				{
					break;
				}
				string strDestPath = dstFile;
				createFolderForPath(strDestPath);

				string strParam = "a \"-o" + strDestPath + "\" ";
				if (Tools::IsFolder(strPath))
				{
					string strFolder = Tools::replace_all(strPath, "/", "\\");
					if (strFolder.at(strFolder.length() - 1) != '\\')
					{
						strFolder.append("\\*");
					}
					else
					{
						strFolder.append("*");
					}
					strParam += "\"" + strFolder + "\"";// / y / r";
				}
				else
				{
					strParam += "\"" + strPath + "\"";// / y / r";
				}
				strParam += "-y -r";
				SHELLEXECUTEINFOA info = {};
				info.cbSize = sizeof info;
				info.fMask = SEE_MASK_NOCLOSEPROCESS;
				info.lpVerb = "open";
				info.lpFile = str7zexe.c_str();
				info.lpParameters = strParam.c_str();
				info.nShow = SW_HIDE;
				OutputDebugStringA(strParam.c_str());
				//WLOG(10,L"<seraphim>",)
				bool ret;
				ret = ShellExecuteExA(&info);
				if (ret && info.hProcess != NULL) {
					WaitForSingleObject(info.hProcess, INFINITE);
				}
				DWORD  nResult;
				GetExitCodeProcess(info.hProcess, &nResult);
			} while (0);

			return 0;
		}

		static void UnzipFile(const string& zipFile, const string dstPath) {
			do {
				string strPath = PathUnExpandEnv(zipFile);
				string dstFile = PathUnExpandEnv(dstPath);
				if (!FileExist(strPath))
				{
					break;
				}

				// 压缩
				string str7zexe = GetAppBasePath("7za.exe");
				if (!FileExist(str7zexe))
				{
					break;
				}
				string strDestPath = dstFile;
				createFolderForPath(strDestPath);

				string strParam = "e -y  \"-o" + strDestPath + "\" ";
				if (Tools::IsFolder(strPath))
				{
					string strFolder = Tools::replace_all(strPath, "/", "\\");
					if (strFolder.at(strFolder.length() - 1) != '\\')
					{
						strFolder.append("\\*");
					}
					else
					{
						strFolder.append("*");
					}
					strParam += "\"" + strFolder + "\"";
				}
				else
				{
					strParam += "\"" + strPath + "\"";
				}
				SHELLEXECUTEINFOA info = {};
				info.cbSize = sizeof info;
				info.fMask = SEE_MASK_NOCLOSEPROCESS;
				info.lpVerb = "open";
				info.lpFile = str7zexe.c_str();
				info.lpParameters = strParam.c_str();
				info.nShow = SW_HIDE;
				wstring msg = a2w(strParam);
				bool ret;
				ret = ShellExecuteExA(&info);
				if (ret && info.hProcess != NULL) {
					WaitForSingleObject(info.hProcess, INFINITE);
				}
				DWORD  nResult;
				GetExitCodeProcess(info.hProcess, &nResult);
			} while (0);
		}

		static HANDLE  UrlMapFile(const wstring& url, const wstring& rootpath, BOOL  bWrite) {
			HANDLE h = NULL;
			do {
				wstring file_path;
				wstring file_name;
				wstring root_path = rootpath;
				if (!rootpath.empty()) {
					char c = rootpath[rootpath.length() - 1];
					if (c != L'/' && c != L'\\') {
						root_path += '/';
					}
				}

				const auto url_len = url.length();
				auto itr = url.find(L"http://");
				if (itr != -1) {
					file_path = url.substr(6, url_len - 7);
				}
				else {
					itr = url.find(L"https://");
					if (itr == -1)
						break;
					file_path = url.substr(7, url_len - 8);
				}

				file_path = root_path + file_path;
				auto itr_second = file_path.find_last_of(L'/');
				if (itr_second == -1)
					break;

				file_name = file_path.substr(itr_second + 1, file_path.length() - itr_second);
				file_path = file_path.substr(0, itr_second + 1);
				createFolderForPath(file_path);
				auto full_path = file_path + file_name;
				DWORD flag = GENERIC_READ;
				DWORD  cd = OPEN_ALWAYS;// CreationDisposition
				if (bWrite) {
					flag = GENERIC_WRITE;
					cd = CREATE_ALWAYS;
				}
				h = CreateFileW(full_path.c_str(), flag, 0, NULL, cd, FILE_ATTRIBUTE_NORMAL, NULL);
				if (h == INVALID_HANDLE_VALUE) {
					auto code = GetLastError();
					WLOG(10, L"<>", L"MapUrl2FIle Error code =", GetLastError());
				}
			} while (0);
			return h;
		}

		static HANDLE  UrlMapFile(const string& url, const string& rootpath, BOOL  bWrite) {
			HANDLE h = NULL;
			do {
				string file_path;
				string file_name;
				string root_path = rootpath;
				if (!rootpath.empty()) {
					char c = rootpath[rootpath.length() - 1];
					if (c != '/' && c != '\\') {
						root_path += '/';
					}
				}

				const auto url_len = url.length();
				auto itr = url.find("http://");
				if (itr != -1) {
					file_path = url.substr(6, url_len - 7);
				}
				else {
					itr = url.find("https://");
					if (itr == -1)
						break;
					file_path = url.substr(7, url_len - 7);
				}

				file_path = root_path + file_path;
				auto itr_second = file_path.find_last_of('/');
				if (itr_second == -1)
					break;

				file_name = file_path.substr(itr_second + 1, file_path.length() - itr_second);
				file_path = file_path.substr(0, itr_second + 1);
				createFolderForPath(file_path);
				auto full_path = file_path + file_name;
				DWORD flag = GENERIC_READ;
				DWORD  cd = OPEN_ALWAYS;// CreationDisposition
				if (bWrite) {
					flag = GENERIC_WRITE;
					cd = CREATE_ALWAYS;
				}
				h = CreateFileA(full_path.c_str(), flag, 0, NULL, cd, FILE_ATTRIBUTE_NORMAL, NULL);
				if (h == NULL) {
					//WLOG(10, TAG, L"MapUrl2FIle Error code =", GetLastError());
				}
			} while (0);
			return h;
		}

		static bool IsFolder(const std::string& targetFile) {
			auto attr = GetFileAttributesA(targetFile.c_str());
			return (attr & FILE_ATTRIBUTE_DIRECTORY);
		}

		static bool FileExist(const std::string& targetFile) {
			auto attr = GetFileAttributesA(targetFile.c_str());
			return attr != INVALID_FILE_ATTRIBUTES;
		}
		static bool DeleteFile(const std::string& path) {
			::DeleteFileA(path.c_str());
			return true;
		};

		static std::wstring& replace_all(std::wstring& str, const std::wstring& old_value, const std::wstring& new_value)
		{
			while (true) {
				std::wstring::size_type pos(0);
				if ((pos = str.find(old_value)) != std::string::npos)
					str.replace(pos, old_value.length(), new_value);
				else break;
			}
			return str;
		}
		static std::string& replace_all(std::string& str, const std::string& old_value, const std::string& new_value)
		{
			while (true) {
				std::string::size_type pos(0);
				if ((pos = str.find(old_value)) != std::string::npos)
					str.replace(pos, old_value.length(), new_value);
				else break;
			}
			return str;
		}

		static void createFolderForPath(std::wstring strPath) {
			replace_all(strPath, L"/", L"\\");

			int iPos = strPath.find_last_of(L'\\');
			std::wstring strFolder;
			if (iPos != -1)
			{
				strFolder = strPath.substr(0, iPos);
				if (!PathIsDirectoryW(strFolder.c_str()))
				{
					createFolderForPath(strFolder);
					::CreateDirectoryW(strFolder.c_str(), NULL);
				}
			}
		}

		static void createFolderForPath(std::string strPath) {
			replace_all(strPath, "/", "\\");

			int iPos = strPath.find_last_of('\\');
			std::string strFolder;
			if (iPos != -1)
			{
				strFolder = strPath.substr(0, iPos);
				if (!PathIsDirectoryA(strFolder.c_str()))
				{
					createFolderForPath(strFolder);
					::CreateDirectoryA(strFolder.c_str(), NULL);
				}
			}
		}
		static void  Unix2SystemTime(time_t t, SYSTEMTIME* s) {
			ZeroMemory(s, sizeof(SYSTEMTIME));
			do {
				char buffer[50];
				tm* _tm = localtime(&t);
				if (_tm == nullptr)
					break;
				s->wYear = _tm->tm_year + 1900;
				s->wMonth = _tm->tm_mon + 1;
				s->wDay = _tm->tm_mday;
				s->wHour = _tm->tm_hour;
				s->wMinute = _tm->tm_min;
				s->wSecond = _tm->tm_sec;
			} while (0);

			return;
		}

		static string GetTimeFormFileName(const string& fileName, const string& pref) {
			auto szName = fileName;
			replace_all(szName, "/", "\\");
			int itr = szName.rfind('\\');
			//itr = itr < 0 ? 0 : itr;
			int cn = szName.length() - itr - 1;
			auto baseName = szName.substr(itr + 1, cn);
			time_t _t;
			string fromat = (pref);
			fromat.append("%I64d.zip");
			auto c = sscanf(baseName.c_str(), fromat.c_str(), &_t);
			(void)c;
			SYSTEMTIME sysTime;
			Unix2SystemTime(_t, &sysTime);
			char buf[MAX_PATH] = { 0 };

			sprintf(buf, "%d-%d-%d %d:%d:%d", sysTime.wYear, sysTime.wMonth, sysTime.wDay,
				sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
			std::string strTime(buf);
			return strTime;
		};

		static __int64 System2UnixTime(const SYSTEMTIME& sysTime)
		{
			char buffer[50];
			sprintf(buffer, "%d-%d-%d %d:%d:%d", sysTime.wYear, sysTime.wMonth, sysTime.wDay,
				sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
			std::string strTime(buffer);
			//printf("当前系统时间：%s\n", strTime);

			struct tm tm;
			memset(&tm, 0, sizeof(tm));

			auto c = sscanf(buffer, "%d-%d-%d %d:%d:%d",
				&tm.tm_year, &tm.tm_mon, &tm.tm_mday,
				&tm.tm_hour, &tm.tm_min, &tm.tm_sec);

			tm.tm_year -= 1900;
			tm.tm_mon--;
			time_t  lt = mktime(&tm); //如果想获取(秒级)的值，这里就可以直接返回
			//下一步llt，是转化成(毫秒级)的Unix时间戳
			time_t llt = lt * 1000 + sysTime.wMilliseconds;
			return llt;
		}

		static std::string PathUnExpandEnv(const std::string& str) {
			std::string ret;
			ret.resize(MAX_PATH);
			auto c = ExpandEnvironmentStringsA(str.c_str(), &ret[0], MAX_PATH);
			ret.resize(c - 1);
			return std::move(ret);
		}

		static __int64 GetFileSize(const string& path)
		{
			__int64 nRet = -1;

			FILE* fp = NULL;
			fopen_s(&fp, path.c_str(), "r");
			if (fp)
			{
				_fseeki64(fp, 0, SEEK_END);
				nRet = _ftelli64(fp);
				_fseeki64(fp, 0, SEEK_SET);
				fclose(fp);
			}

			return nRet;
		}

		static __int64 GetFolderSize(const string& path)
		{
			__int64 nSize = 0;
			string strRootPath = path + "\\";
			string strRoot = strRootPath + "*.*";
			WIN32_FIND_DATAA fd;
			HANDLE hFind = FindFirstFileA(strRoot.c_str(), &fd);
			if (INVALID_HANDLE_VALUE == hFind)
				return nSize;
			while (FindNextFileA(hFind, &fd))
			{
				if (strcmp(fd.cFileName, ".") == 0 || strcmp(fd.cFileName, "..") == 0)
					continue;
				string strPath = strRootPath + fd.cFileName;
				if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					nSize += GetFolderSize(strPath);
				else
				{
					HANDLE hFile = CreateFileA(strPath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
					if (INVALID_HANDLE_VALUE == hFile)
						continue;
					LARGE_INTEGER size;
					if (::GetFileSizeEx(hFile, &size))
					{
						nSize += size.QuadPart;
					}
					CloseHandle(hFile);
				}
			}
			FindClose(hFind);
			return nSize;
		}

		static std::string GetBasePath(const string& exePath) {
			string  fullPath(exePath);
			replace_all(fullPath, "\\", "/");
			auto pos = fullPath.find_last_of('/');
			auto  path = fullPath.substr(0, pos);
			return path;
		}
		static std::string GetAppBasePath(const std::string& file)
		{
			std::string path(MAX_PATH, '\0');
			GetModuleFileNameA(0, &path[0], MAX_PATH);
			path.resize(strlen(path.c_str()));
			auto pos = path.find_last_of("\\");
			path = path.substr(0, pos);
			path.resize(MAX_PATH);
			if (file.length() > 0) {
				PathAppendA(&path[0], file.c_str());
			}
			auto len = strlen(path.c_str());
			path.resize(len);
			return path;
		}

		static std::string ReadFile(const char* path)
		{
			std::ifstream t2(path, std::ios::binary);
			std::string strRet = std::move(std::string((std::istreambuf_iterator<char>(t2)),
				std::istreambuf_iterator<char>()));
			t2.close();
			return strRet;
		}

		static std::string GenerateGUIDA()
		{
			char buf[64] = { 0 };
			GUID guid;

			if (CoCreateGuid(&guid))
			{
				return std::move(std::string(""));
			}

			sprintf(buf,
				"%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X",
				guid.Data1, guid.Data2, guid.Data3,
				guid.Data4[0], guid.Data4[1], guid.Data4[2],
				guid.Data4[3], guid.Data4[4], guid.Data4[5],
				guid.Data4[6], guid.Data4[7]);

			return std::move(std::string(buf));
		}

		static void EnumeDirectFiles(const string& path, vector<string>& dst) {
			do {
				char szFind[MAX_PATH];
				WIN32_FIND_DATAA FindFileData;
				strcpy(szFind, path.c_str());
				strcat(szFind, "*.*");
				HANDLE hFind = ::FindFirstFileA(szFind, &FindFileData);
				if (INVALID_HANDLE_VALUE == hFind)
					break;
				while (1)
				{
					//cout << FindFileData.cFileName;
					dst.push_back(FindFileData.cFileName);
					if (!FindNextFileA(hFind, &FindFileData))
						break;
				}
				FindClose(hFind);
			} while (0);
		}
	};
};
