#pragma once
#include <include/cef_response_filter.h>
namespace seraphim {
	class IResourceStoreFactor : public CefBaseRefCounted {
		IMPLEMENT_REFCOUNTING(IResourceStoreFactor);
		DISALLOW_COPY_AND_ASSIGN(IResourceStoreFactor);
	public:
		IResourceStoreFactor() = default;
		virtual CefRefPtr<CefResponseFilter>  MakeFilter() = 0;
	};
}
