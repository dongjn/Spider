#pragma once
#include <include/cef_dom.h>
#include <functional>
namespace seraphim {
	inline  CefRefPtr<CefDOMNode>  SkipTextNode(CefRefPtr<CefDOMNode> node) {
		CefRefPtr<CefDOMNode> rst = nullptr;
		while (node.get() != nullptr && rst.get() == nullptr) {
			if (node->GetType() == DOM_NODE_TYPE_TEXT) {
				node = node->GetNextSibling();
				continue;
			}
			rst = node;
		}
		return rst;
	}

	inline bool NeedSkip(CefRefPtr<CefDOMNode> node) {
		return node.get() == nullptr || node->GetType() == DOM_NODE_TYPE_TEXT || node->GetType() == DOM_NODE_TYPE_COMMENT;
	}
	inline CefRefPtr<CefDOMNode> SearchSlibling(CefRefPtr<CefDOMNode> node,std::function<bool(CefRefPtr<CefDOMNode>)>  op) {
		CefRefPtr<CefDOMNode> rst;
		while (!op(node)) {
			node = node->GetNextSibling();
		}
		return rst;
	}

};