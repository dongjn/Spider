#pragma once
#include <include/cef_dom.h>
#include <vector>
#include "dom_error.h"
namespace seraphim {
	using std::vector;
	class DOMNodeMatcher : CefBaseRefCounted {
		IMPLEMENT_REFCOUNTING(DOMNodeMatcher);
		DISALLOW_COPY_AND_ASSIGN(DOMNodeMatcher);
	protected:
		CefRefPtr<DOMNodeMatcher>  next{ nullptr };
	public:
		DOMNodeMatcher() = default;

		void 	Append(CefRefPtr<DOMNodeMatcher> matcher) {
			if (nullptr == next) {
				next = matcher;
			}
			else {
				next->Append(matcher);
			}
		}
		virtual vector <CefRefPtr<CefDOMNode>>  Match(vector<CefRefPtr<CefDOMNode>> node)  throw(DOMError);

	};
	/**
	 *
	 */
	class DOMNodeNameMatcher :public  DOMNodeMatcher {
		IMPLEMENT_REFCOUNTING(DOMNodeNameMatcher);
		DISALLOW_COPY_AND_ASSIGN(DOMNodeNameMatcher);
	private:
		int mIndex;
		CefString  mName;
	public:
		DOMNodeNameMatcher() = default;
		DOMNodeNameMatcher(CefString name, int index = -1) :mName(name), mIndex(index) {

		};
		virtual vector<CefRefPtr<CefDOMNode>> Match(vector<CefRefPtr<CefDOMNode>> node) override;
	};
	/**
	 *
	 */
	class DOMNodePerpertyMatcher : public DOMNodeMatcher {
		IMPLEMENT_REFCOUNTING(DOMNodePerpertyMatcher);
		DISALLOW_COPY_AND_ASSIGN(DOMNodePerpertyMatcher);
	private:
		int mIndex{ -1 };
		CefString mPerpertyName;
		CefString mPerpertyValue;
	public:
		DOMNodePerpertyMatcher() = default;
		DOMNodePerpertyMatcher(CefString name, int index = -1) :mPerpertyName(name), mIndex(index) {
		};
		DOMNodePerpertyMatcher(CefString name, CefString value, int index = -1) :mPerpertyName(name), mPerpertyValue(value), mIndex(index) {
		};
		virtual vector<CefRefPtr<CefDOMNode>> Match(vector<CefRefPtr<CefDOMNode>> node) override;
	};
	class DOMNOdeParentMatcher : public DOMNodeMatcher {
		IMPLEMENT_REFCOUNTING(DOMNOdeParentMatcher);
		DISALLOW_COPY_AND_ASSIGN(DOMNOdeParentMatcher);
	public:
		DOMNOdeParentMatcher() = default;
		virtual vector<CefRefPtr<CefDOMNode>> Match(vector<CefRefPtr<CefDOMNode>> vNode) {
			vector<CefRefPtr<CefDOMNode>> vResult;
			for (auto& node : vNode) {
				auto parent = node->GetParent();
				vResult.push_back(parent);
				}

			return DOMNodeMatcher::Match(vResult);
			
		};

	};


};