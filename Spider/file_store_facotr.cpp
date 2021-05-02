#pragma warning(disable :26812)
#include "file_store_facotr.h"
#include "log.h"
#include "common.h"
#include "common_tools.hpp"
namespace seraphim {

	FileStoreFactor::FileStoreFactor(CefString path, CefString baseName)
	{

	}

	CefRefPtr<CefResponseFilter> FileStoreFactor::MakeFilter()
	{
		CefRefPtr <ResponseFilter> rst = new ResponseFilter();
		rst->fHandle = NULL;
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
		WLOG(10, TAG, L"ResponseFilter::Filter");
		return CefResponseFilter::FilterStatus::RESPONSE_FILTER_NEED_MORE_DATA;
	}

	FileStoreFactor::ResponseFilter::~ResponseFilter()
	{
		CloseHandle(fHandle);
	}

};


