#pragma once
#include <include/cef_base.h>
#include <include/cef_request.h>
#include <include/cef_browser.h>
#include <include/cef_response.h>
namespace seraphim {
	class RequestMatcherBase :public CefBaseRefCounted {
		IMPLEMENT_REFCOUNTING(RequestMatcherBase);
		DISALLOW_COPY_AND_ASSIGN(RequestMatcherBase);
	protected:
		CefRefPtr<RequestMatcherBase> first_{ nullptr };
		CefRefPtr<RequestMatcherBase> second_{ nullptr };
		bool  bOR_;
		RequestMatcherBase(CefRefPtr<RequestMatcherBase> first, CefRefPtr<RequestMatcherBase> second, bool bOR) :first_(first), second_(second), bOR_(bOR) {
		};
	public:
		RequestMatcherBase() = default;
		CefRefPtr<RequestMatcherBase>  CompositeOR(CefRefPtr<RequestMatcherBase> other) {
			return new RequestMatcherBase(this, other, true);
		}
		CefRefPtr<RequestMatcherBase>  CompositeAND(CefRefPtr<RequestMatcherBase> other) {
			return new RequestMatcherBase(this, other, false);
		}
		virtual bool Matching(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, CefRefPtr<CefResponse> response) {
			if (bOR_)
				return first_->Matching(browser, frame, request, response) || second_->Matching(browser, frame, request, response);
			else
				return first_->Matching(browser, frame, request, response) && second_->Matching(browser, frame, request, response);
		}
	};

	class ResourceTypeMatcher : public RequestMatcherBase {
		IMPLEMENT_REFCOUNTING(ResourceTypeMatcher);
		DISALLOW_COPY_AND_ASSIGN(ResourceTypeMatcher);
	private:
		CefRequest::ResourceType type_;
	public:
		ResourceTypeMatcher(CefRequest::ResourceType type) :type_(type) {};

		virtual bool Matching(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, CefRefPtr<CefResponse> response)  override {
			return type_ == request->GetResourceType();
		}
	};

	class RequertURLMatcher : public RequestMatcherBase {
		IMPLEMENT_REFCOUNTING(RequertURLMatcher);
		DISALLOW_COPY_AND_ASSIGN(RequertURLMatcher);
	private:
		CefString  url_;
	public:
		RequertURLMatcher(CefString url) :url_(url) {};
		virtual bool Matching(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, CefRefPtr<CefResponse> response)  override {
			auto url = request->GetURL();
			return url.compare(url_) == 0;
		}
	};

	class MimetypeMatcher : public RequestMatcherBase {
		IMPLEMENT_REFCOUNTING(MimetypeMatcher);
		DISALLOW_COPY_AND_ASSIGN(MimetypeMatcher);
	private:
		CefString  mimeType_;
	public:
		MimetypeMatcher(CefString mimeType) :mimeType_(mimeType) {
		};
		virtual bool Matching(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, CefRefPtr<CefResponse> response)  override {
			auto mimeType = response->GetMimeType();
			return mimeType.compare(mimeType_) == 0;
		}
	};
};