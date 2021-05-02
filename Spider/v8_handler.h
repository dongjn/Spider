#pragma once
#include "common.h"
#include <include/cef_v8.h>
#include <vector>
#include<bitset>

using std::vector;
using std::bitset;
namespace seraphim {
	class V8Handler : public CefV8Handler {
		IMPLEMENT_REFCOUNTING(V8Handler);
		DISALLOW_COPY_AND_ASSIGN(V8Handler);
	private:
		CefRefPtr<CefBrowser> mBrowser;

	public:
		V8Handler(CefRefPtr<CefBrowser> browser) :mBrowser(browser) {
		};

		bool Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception) override;
	private:
	};
};