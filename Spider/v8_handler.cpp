#include "v8_handler.h"
#include "log.h"

namespace seraphim {
	static const CefString  gGameIdKeyName = L"game_id";
	static const CefString  gAccountIdKeyName = L"account_id";
	static const CefString gPlatformName = L"platform_name";
	static const CefString gProcessName = L"process_name";
	static const CefString gIDKeyName = L"id";
	static const CefString gTokenKeyName = L"token";
	static const CefString gListKeyName = L"list";
	static const CefString gNameKeyName = L"name";
	static const CefString gExeKeyName = L"exe";
	static const CefString gAcceleratorKeyName = L"accelerator";
	static const CefString gToolKeyName = L"tool";
	static const CefString gDirectxKeyName = L"directx";
	static const CefString gISSupportArchiveKeyName = L"is_support_archive";
	static const CefString gArchiveCheckKeyName = L"archive_check";
	static const CefString gArchivePathKeyName = L"archive_path";

	CefRefPtr<seraphim::V8Handler> V8Handler::self_{ nullptr };

	bool V8Handler::Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
	{
		const std::wstring szName = name.ToWString();
		return true;
	}

	CefRefPtr<seraphim::V8Handler> V8Handler::Make(CefRefPtr<CefBrowser> browser)
	{
		if (self_.get() == nullptr) {
			self_ = new V8Handler(browser);
		}
		return self_;
	}
};