#pragma once
#include <include/cef_browser.h>

namespace seraphim {
	class BrowserBase : public virtual CefBrowser {
		IMPLEMENT_REFCOUNTING(BrowserBase);
		DISALLOW_COPY_AND_ASSIGN(BrowserBase);
	};
};