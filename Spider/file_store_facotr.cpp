#pragma warning(disable :26812)
#include "file_store_facotr.h"
#include "common_log.h"
#include "common.h"
#include "common_tools.hpp"
#include <sstream>
#undef min
#undef max
namespace seraphim {
	FileStoreFactor::FileStoreFactor(const string& path, const string& baseName, const string& suffixName) :mBasePath(path), mBaseName(baseName), mSuffixName(suffixName)
	{
		Tools::CreateFolderForPath(mBasePath);
	}

	CefRefPtr<CefResponseFilter> FileStoreFactor::MakeFilter()
	{
		std::stringstream ss;
		ss << mBasePath << mBaseName << count++ << mSuffixName;
		//ss <<

		auto name = ss.str();
		auto h = CreateFileA(name.c_str(), GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
		auto code = GetLastError();
		CefRefPtr <ResponseFilter> rst = new ResponseFilter(h);
		return rst;
	}
	static bool once = true;
	bool FileStoreFactor::ResponseFilter::InitFilter()
	{
		bool rst = false;
		if (once) {
			rst = true;
			once = false;
		}
		return true;
	}

	CefResponseFilter::FilterStatus FileStoreFactor::ResponseFilter::Filter(void* data_in, size_t data_in_size, size_t& data_in_read, void* data_out, size_t data_out_size, size_t& data_out_written)
	{
		if (data_in_size == 0 || data_in == nullptr) {
			WLOG(10, TAG, L"");
			data_in_read = 0;
			data_out_written = 0;
			FlushFileBuffers(fHandle);
			CloseHandle(fHandle);
			fHandle = NULL;
			return RESPONSE_FILTER_DONE;
		}
		DWORD dwWrite;
		int cb = std::min(data_in_size, data_out_size);
		memcpy(data_out, data_in, cb);
		data_out_written = cb;
		data_in_read = cb;
		WriteFile(fHandle, data_in, cb, &dwWrite, nullptr);
		return CefResponseFilter::FilterStatus::RESPONSE_FILTER_NEED_MORE_DATA;
	}

	FileStoreFactor::ResponseFilter::~ResponseFilter()
	{
		if (fHandle)
			CloseHandle(fHandle);
	}
};