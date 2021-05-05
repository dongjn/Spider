#pragma once
#include <include/cef_dom.h>
#include <vector>
#include "dom_error.h"
#include "dom_node.h"
namespace seraphim {
	using std::vector;
	class DOMNodeMatcher : CefBaseRefCounted {
		IMPLEMENT_REFCOUNTING(DOMNodeMatcher);
		DISALLOW_COPY_AND_ASSIGN(DOMNodeMatcher);
	protected:
		DOMNodeOP  op_{nullptr};
		CefRefPtr<DOMNodeMatcher>  next_{ nullptr };
	public:
		DOMNodeMatcher() = default;
		void 	Append(CefRefPtr<DOMNodeMatcher> matcher) {
			if (nullptr == next_) {
				next_ = matcher;
			}
			else {
				next_->Append(matcher);
			}
		}
		virtual void Match(vector<CefRefPtr<DOMNode>> vNode);
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
		DOMNodeNameMatcher(CefString name, int index = -1,DOMNodeOP op = nullptr) :mName(name), mIndex(index){
			op_ = op;
		};
		virtual void Match(vector<CefRefPtr<DOMNode>> node) override;
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
		DOMNodePerpertyMatcher(CefString name, int index = -1,DOMNodeOP op = nullptr) :mPerpertyName(name), mIndex(index) {
			op_ = op;
		};
		DOMNodePerpertyMatcher(CefString name, CefString value, int index = -1) :mPerpertyName(name), mPerpertyValue(value), mIndex(index) {
		};
		virtual void Match(vector<CefRefPtr<DOMNode>> node) override;
	};
	class DOMNOdeParentMatcher : public DOMNodeMatcher {
		IMPLEMENT_REFCOUNTING(DOMNOdeParentMatcher);
		DISALLOW_COPY_AND_ASSIGN(DOMNOdeParentMatcher);
	public:
		DOMNOdeParentMatcher() = default;
		DOMNOdeParentMatcher(DOMNodeOP op){
			op_ = op;
		}
		virtual void  Match(vector<CefRefPtr<DOMNode>> vNode) {
			vector<CefRefPtr<DOMNode>> vResult;
			//for (CefRefPtr<CefDOMNode> node : vNode) {
			//	auto parent = node->GetParent();
			//	//vResult.push_back(parent);
			//	}
			DOMNodeMatcher::Match(vResult);
			return ;
			
		};

	};

	//operator CefRefPtr<CefDOMNode>()
};