//
//  utility.h
//  MathCore
//
//  Created by seraph on 22/7/18.
//  Copyright © 2018年 seraph. All rights reserved.
//

#ifndef utility_h
#define utility_h
//#include"math_core.hpp"
#include<chrono>
#include<ctime>
#include<string>
#include<memory>
#include<sstream>
#include<thread>
#include<iostream>
#include<assert.h>
#include<string>
#ifdef ANDROID
#include<android/log.h>
constexpr  int default_level = ANDROID_LOG_DEBUG;
constexpr int INFO_LEVEL = ANDROID_LOG_INFO;
constexpr int DEBUG_LEVEL = ANDROID_LOG_DEBUG;
constexpr int ERROR_LEVEL = ANDROID_LOG_ERROR;

#else
#ifdef  _WIN32
#include<Windows.h>
#include<atlstr.h>
#include<codecvt>
#include<io.h>
#include<iostream>

constexpr int INFO_LEVEL = 0;
constexpr int DEBUG_LEVEL = 10;
constexpr int ERROR_LEVEL = 20;
constexpr int  default_level =10;

extern void mem_cp_mc(void* dst, const void* src, size_t bytes, int coCore);

struct StrLessComp {
	bool operator()(const std::string& l, const std::string& r) const {
		return strcmp(l.c_str(), r.c_str()) < 0;
	}
};
inline std::wstring string2wstring(const std::string& str, const std::string& locale)
{
	typedef std::codecvt_byname<wchar_t, char, std::mbstate_t> F;
	static std::wstring_convert<F> strCnv(new F(locale));
	return strCnv.from_bytes(str);
};

inline std::string local2stringutf8(const std::string& str, const std::string& locale) {
	typedef std::codecvt_byname<char, char, std::mbstate_t> F;
	static std::wstring_convert<F, char> strCnv(new F(locale));
	wchar_t* p = nullptr;
	//return strCnv.to_bytes(str.c_str());
	return strCnv.from_bytes(str.c_str());
}

inline std::u32string  string2unicode(const std::string& src, const std::string& locale) {
	typedef std::codecvt_byname<char32_t, char, std::mbstate_t> F;
	static std::wstring_convert<F, char32_t> strCnv(new F(locale));
	return strCnv.from_bytes(src.c_str());
}
inline std::u32string utf82unicode(const std::string& src) {
	typedef std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> f;
	static f cvt;
	return cvt.from_bytes(src);
}
inline std::u32string bytes2unicode(const char* bytes, const std::string& locale) {
	typedef std::codecvt_byname<char32_t, char, std::mbstate_t> F;
	static std::wstring_convert<F, char32_t> strCnv(new F(locale));
	return strCnv.from_bytes(bytes);
}
inline std::string GBK_2_UTF8(std::string gbkStr)
{
	std::string outUtf8 = "";
	int n = MultiByteToWideChar(CP_ACP, 0, gbkStr.c_str(), -1, NULL, 0);
	WCHAR* str1 = new WCHAR[n];
	MultiByteToWideChar(CP_ACP, 0, gbkStr.c_str(), -1, str1, n);
	n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
	char* str2 = new char[n];
	WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
	outUtf8 = str2;
	delete[]str1;
	str1 = NULL;
	delete[]str2;
	str2 = NULL;
	return outUtf8;
}

inline std::u32string gbk2unicode(const std::string& bgkStr) {
	auto utfStr = GBK_2_UTF8(bgkStr);
	return utf82unicode(utfStr);
}
inline void windo_log(const char* TAG, std::stringstream& ss) {
	std::stringstream sst;
	auto n = std::chrono::system_clock::now();
	auto ms = n.time_since_epoch();
	auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(ms).count();
	auto const msecs = diff % 1000;

	auto now = std::chrono::system_clock::now();
	std::time_t t = std::chrono::system_clock::to_time_t(now);
	sst << std::ctime(&t) << msecs << "::";
	std::string tmsg = sst.str();

	std::string msg = ss.str();
	//std::cout << msg << std::endl;
	OutputDebugStringA(msg.c_str());
}
#else
#include <chrono>
#include <cinttypes>
#include <ctime>
#include <sstream>
#include <iomanip>
#endif
#endif

namespace seraphim {
	//extern char* TAG;
	using sstream = std::stringstream;
	using std::shared_ptr;
	using std::unique_ptr;
	using std::string;
	using std::wstring;
	extern wstring string2wstring(const string& str);
	extern string  wstring2string(const wstring& wstr);

	//************************************
	// Method:    read_file
	// FullName:  read_file
	// Access:    public static
	// Returns:   uint32_t
	// Qualifier:
	// Parameter: const char * file
	// Parameter: void * buffer
	//************************************
	inline uint32_t read_file(const char* file, void* buffer) {
		size_t bytes = 0;
		FILE* f = nullptr;
		do {
			f = fopen(file, "rb");
			if (f == 0) {
				printf("OpenFile Error %s\n", file);
			};
			assert(f);
			fseek(f, 0, SEEK_END);
			bytes = ftell(f);
			assert(bytes % 4 == 0);
			if (buffer == nullptr) break;
			fseek(f, 0, SEEK_SET);
			fread(buffer, 1, bytes, f);
		} while (false);
		fclose(f);
		return (uint32_t)bytes;
	};

	extern void fill_bmp_head_32(int w, int h, void* bmp);

	inline void _SLog(sstream& stream, int lever, const char* tag) {
#ifdef ANDROID
		int default_level = ANDROID_LOG_INFO;
		if (tag == nullptr || string(tag).empty()) {
			int code = 0;
		}
		auto str = stream.str();
		__android_log_write(lever, tag, stream.str().c_str());
#elif _WIN32
		//OutputDebugStringA(stream.str().c_str());
		windo_log(tag, stream);

#else
		std::cout << tag << stream.str() << std::endl;
#endif
		return;
	}



	template<typename T, typename ...Args>
	inline void _SLog(sstream& stream, int level, const char* TAG, T t, Args ...args) {
		stream << t;
		_SLog(stream, level, TAG, args...);
	};

	template<typename ...Args>
	inline void WLOG(int level, const char* tag, Args ...arg) {
		if (level > default_level) {
			sstream s;//= new std::stringstream();
			//s << std::hex;
			s << tag;
			_SLog(s, level, tag, arg...);
		}
	};

	template<typename T>
	inline void WLOG(std::wstringstream& ss, const T& t) {
		ss << t;
		OutputDebugString(ss.str().c_str());
	}
	template<>
	inline void WLOG<CString>(std::wstringstream& ss, const CString& str) {
		BSTR wstr = str.AllocSysString();
		ss << wstr << std::endl;
		OutputDebugString(ss.str().c_str());
	}

	template<typename T, typename ...Args>
	inline void WLOG(std::wstringstream& ss, T t, Args ...args) {
		ss << t << " ";
		WLOG(ss, args...);
	}

	template<typename ...Args>
	inline void WLOG(int level, const wchar_t* tag, Args ...args) {
		if (level >= default_level) {
			std::wstringstream ss;
			ss << L"[" << tag << L"]";
			if (level >= ERROR_LEVEL) {
				ss << L"<ERROR>" << " ";
			}
			else if (level >= DEBUG_LEVEL) {
				ss << L"<DEBUG>" << " ";
			}
			else if (level >= INFO_LEVEL) {
				ss << L"<INFO>" << " ";
			}
			auto tid = GetCurrentThreadId();
			ss << L"[" << tid << L"]";
			WLOG(ss, args...);
		}
	}
};
#endif /* utility_h */
#pragma once
