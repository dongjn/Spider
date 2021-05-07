#pragma once
#include <include/cef_app.h>
#include <include/cef_render_handler.h>

namespace seraphim {
	class RenderProcessHandler : virtual public CefApp, virtual public CefRenderProcessHandler {
		IMPLEMENT_REFCOUNTING(RenderProcessHandler);
		DISALLOW_COPY_AND_ASSIGN(RenderProcessHandler);

	public:

		RenderProcessHandler() = default;

		virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() override
		{
			return this;
		}

		virtual void OnBrowserCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefDictionaryValue> extra_info) override;

		virtual void OnBrowserDestroyed(CefRefPtr<CefBrowser> browser) override;

		virtual bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message) override;

		virtual void OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context) override;
	};
};