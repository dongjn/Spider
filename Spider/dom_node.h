#pragma once
#include <include/cef_dom.h>
#include <functional>
#include <include/cef_dom.h>
#include <vector>
#include<memory>
#include "common.h"
#include "cef_log_utility.h"
#include "common_log.h"
using std::vector;
using std::shared_ptr;
namespace seraphim {
	class DOMNode;
	using DOMNodeOP = std::function<void(shared_ptr<DOMNode>  node)>;
	class DOMNode :  public std::enable_shared_from_this<DOMNode>{
	private:
		vector <shared_ptr<DOMNode>>  children;
		mutable	std::function<void(shared_ptr<DOMNode>  self)>  op_{nullptr};
		CefRefPtr<CefDOMNode>  mCefNode{ nullptr };
	public:

		CefRefPtr<CefDOMNode> GetNode() {
			assert(mCefNode);
			return mCefNode;
		};
		friend  class DOMNodeMatcher;
		void AddChild(shared_ptr<DOMNode> child) {
			children.push_back(child);
		}


		const vector<shared_ptr<DOMNode>>& GetChildren() {
			return children;
		}
		DOMNode() = default;
		DOMNode(CefRefPtr<CefDOMNode> node, DOMNodeOP op = nullptr) :mCefNode(node), op_(op) {
		}
		void SetOperator(DOMNodeOP  op) const{
			op_ = op;
		}
		DOMNode& operator =(CefRefPtr<CefDOMNode> node){
			mCefNode = node;
			return *this;
		}
		void Process() {
			if (op_)
				op_(shared_from_this());
			for (auto& child : children) {
				child->Process();
			}
		}

		friend 	inline wstringstream& operator<<(wstringstream& os, shared_ptr<DOMNode> node) {
			os << node->mCefNode;
			return os;

		}
	};


};
