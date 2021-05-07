#pragma once
#include <include/cef_dom.h>
#include <vector>
#include "dom_error.h"
#include "dom_node.h"

namespace seraphim {
	using std::vector;
	class DOMNodeMatcher :  public std::enable_shared_from_this<DOMNodeMatcher>{
	protected:
		DOMNodeOP  op_{nullptr};
		shared_ptr<DOMNodeMatcher>  mNextLayer{ nullptr };
	public:
		DOMNodeMatcher() = default;
		void 	Append(shared_ptr<DOMNodeMatcher> matcher) {
			if (nullptr == mNextLayer) {
				mNextLayer = matcher;
			}
			else {
				mNextLayer->Append(matcher);
			}
		}
		virtual void Match(vector<shared_ptr<DOMNode>> vNode);
	};
	/**
	 *
	 */
	class DOMNodeNameMatcher :public  DOMNodeMatcher {
	private:
		int mIndex;
		CefString  mName;
	public:
		DOMNodeNameMatcher() = default;
		DOMNodeNameMatcher(CefString name, int index = -1,DOMNodeOP op = nullptr) :mName(name), mIndex(index){
			op_ = op;
		};
		virtual void Match(vector<shared_ptr<DOMNode>> node) override;
	};
	/**
	 *
	 */
	class DOMNodePerpertyMatcher : public DOMNodeMatcher {
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
		virtual void Match(vector<shared_ptr<DOMNode>> node) override;
	};
	class DOMNOdeParentMatcher : public DOMNodeMatcher {
	public:
		DOMNOdeParentMatcher() = default;
		DOMNOdeParentMatcher(DOMNodeOP op){
			op_ = op;
		}
		virtual void  Match(vector<shared_ptr<DOMNode>> vNode) {
			vector<shared_ptr<DOMNode>> vResult;
			DOMNodeMatcher::Match(vResult);
			return ;
		};

	};

	class  MultilayerDOMNodeNameMatcher : public DOMNodeMatcher {
	public:
		MultilayerDOMNodeNameMatcher() = default;

	};


	//operator CefRefPtr<CefDOMNode>()
};