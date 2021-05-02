#pragma once
#include <include/cef_base.h>
#include <include/cef_browser.h>
#include "visitor_base.h"
namespace seraphim {
	class VisitorHandler : public virtual CefBaseRefCounted {
		IMPLEMENT_REFCOUNTING(VisitorHandler);
		DISALLOW_COPY_AND_ASSIGN(VisitorHandler);
	private:
		CefRefPtr<CefFrame>  mFrame{nullptr};
	
	public:
		

	};
};