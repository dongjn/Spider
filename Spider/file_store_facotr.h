#pragma once
#include "resource_store_factor_i.h"
namespace seraphim {
	class FileStoreFactor : public IResourceStoreFactor {

	private:
		int startIndex{ 0 };
		class ResponseFilter : public CefResponseFilter {
		public:
			CefString mUrl;
			HANDLE fHandle{NULL};
			ResponseFilter() = default;
			virtual bool InitFilter() override;;
			virtual FilterStatus Filter(void* data_in, size_t data_in_size, size_t& data_in_read, void* data_out, size_t data_out_size, size_t& data_out_written) override;
			~ResponseFilter();
			IMPLEMENT_REFCOUNTING(ResponseFilter);
			DISALLOW_COPY_AND_ASSIGN(ResponseFilter);

		};
	private:
		CefString rootPath;
		CefString baseName;
	public:
		FileStoreFactor(CefString path, CefString baseName);
		IMPLEMENT_REFCOUNTING(FileStoreFactor);
		DISALLOW_COPY_AND_ASSIGN(FileStoreFactor);

		virtual CefRefPtr<CefResponseFilter> MakeFilter() override;


	};
};