#include "common.h"
#include "cef_log_utility.h"
#include "common_log.h"
#include "dom_matcher.h"
#include "dom_utility.h"

namespace seraphim {




	vector<CefRefPtr<CefDOMNode>> DOMNodeNameMatcher::Match(vector<CefRefPtr<CefDOMNode>> vNodes)
	{
		vector <CefRefPtr<CefDOMNode>> vResutl;
		do {
			for (auto& node : vNodes) {
				int index = 0;
				auto child = node->GetFirstChild();
				auto m = SearchSlibling(child, [&vResutl,this,&index](CefRefPtr<CefDOMNode>  n)->bool {
					bool  rst = false;
					do {
						if (n.get() == nullptr) {
							rst = true;
							break;
						}
						if (NeedSkip(n)) {
							break;
						}
						auto name = n->GetName();
						if (name.empty()) {
							break;
						}
						if (name.compare(mName) != 0) {
							break;
						}
						if (mIndex == -1) {
							vResutl.push_back(n);
							break;
						}
						if (index++ == mIndex) {
							vResutl.push_back(n);
							rst = true;
						}
					} while (0);
					return rst;
					});

			}
		} while (0);
		return DOMNodeMatcher::Match(vResutl);
	}

	vector<CefRefPtr<CefDOMNode>> DOMNodePerpertyMatcher::Match(vector<CefRefPtr<CefDOMNode>> vNodes)
	{
		vector <CefRefPtr<CefDOMNode>> vResutl;
		do {
			for (auto& node : vNodes) {
				int index = 0;
				auto child = node->GetFirstChild();
				SearchSlibling(child, [&vResutl, this, &index](CefRefPtr<CefDOMNode>  n)->bool {
					bool  rst = false;
					do {
						if (n.get() == nullptr) {
							rst = true;
							break;
						}
						if (NeedSkip(n)) {
							break;
						}
						if (!n->HasElementAttribute(mPerpertyName)) {
							break;
						}
						auto value = n->GetElementAttribute(mPerpertyName);
						if (!mPerpertyValue.empty() &&  mPerpertyValue.compare(value) != 0)
							break;

						if (mIndex == -1) {
							vResutl.push_back(n);
							break;
						}
						if (index++ == mIndex) {
							vResutl.push_back(n);
							rst = true;
						}
					} while (0);
					return rst;
					});

			}
		} while (0);
		
		return DOMNodeMatcher::Match(vNodes);
	}

	vector <CefRefPtr<CefDOMNode>> DOMNodeMatcher::Match(vector<CefRefPtr<CefDOMNode>> node) throw(DOMError)
	{
		if (next) {
			return next->Match(node);
		}
		return node;
	}

};


