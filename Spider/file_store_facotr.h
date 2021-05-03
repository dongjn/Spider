#pragma once
#include "resource_store_factor_i.h"
#include <string>
namespace seraphim {
	using std::string;
	class FileStoreFactor : public IResourceStoreFactor {
	private:
		int startIndex{ 0 };
		class ResponseFilter : public CefResponseFilter {
		public:
			CefString mUrl;
			HANDLE fHandle{ NULL };
			ResponseFilter() = default;
			ResponseFilter(HANDLE hFile) :fHandle(hFile) {};
			virtual bool InitFilter() override;;
			virtual FilterStatus Filter(void* data_in, size_t data_in_size, size_t& data_in_read, void* data_out, size_t data_out_size, size_t& data_out_written) override;
			~ResponseFilter();
			IMPLEMENT_REFCOUNTING(ResponseFilter);
			DISALLOW_COPY_AND_ASSIGN(ResponseFilter);
		};
	private:
		const string mBasePath;
		const string mBaseName;
		const string mSuffixName;
		int      count{ 0 };
	public:
		FileStoreFactor(const string& path, const string& baseName, const string& suffixName);
		IMPLEMENT_REFCOUNTING(FileStoreFactor);
		DISALLOW_COPY_AND_ASSIGN(FileStoreFactor);

		virtual CefRefPtr<CefResponseFilter> MakeFilter() override;
	};
};