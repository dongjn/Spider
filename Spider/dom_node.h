#pragma once
#include <include/cef_dom.h>
#include <functional>
#include <include/cef_dom.h>
#include <vector>
#include "common.h"
#include "cef_log_utility.h"
#include "common_log.h"
using std::vector;
namespace seraphim {
	class DOMNode;
	using DOMNodeOP = std::function<void(CefRefPtr<DOMNode>  node)>;
	//static auto  log_op = [](CefRefPtr<DOMNode> node) {
	//};
	class DOMNode :  public CefBaseRefCounted{
		IMPLEMENT_REFCOUNTING(DOMNode);
		DISALLOW_COPY_AND_ASSIGN(DOMNode);
	private:
		vector < CefRefPtr<DOMNode>>  children;
		std::function<void(CefRefPtr<DOMNode>  self)>  op_{nullptr};
	public:
		friend  class DOMNodeMatcher;
		CefRefPtr<CefDOMNode>  node_{ nullptr };
		void AddChild(CefRefPtr<DOMNode> child) {
			children.push_back(child);
		}
		DOMNode() = default;
		DOMNode(CefRefPtr<CefDOMNode> node, DOMNodeOP op = [](CefRefPtr<DOMNode> n) {
				WLOG(10, TAG,L"<DOMNode>", n->node_);

			}) :node_(node), op_(op) {

		}

		DOMNode& operator =(CefRefPtr<CefDOMNode> node){
			node_ = node;
			return *this;
		}
		void Process() {
			if (op_)
				op_(this);
			for (auto& child : children) {
				child->Process();
			}
		}
	};
	inline wstringstream& operator<<(wstringstream& os, CefRefPtr<DOMNode> node) {
		//os << L"[CefResponse]<" << L"]";// << bound.x << L"," << bound.y << L"," << bound.width << L"," << bound.height << L">";
		return os;
	}

};
