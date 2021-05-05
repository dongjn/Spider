#include "common.h"
#include "cef_log_utility.h"
#include "common_log.h"
#include "dom_matcher.h"
#include "dom_utility.h"

namespace seraphim {




	void DOMNodeNameMatcher::Match(vector<CefRefPtr<DOMNode>> vNodes)
	{
		do {
			for (CefRefPtr<DOMNode> mine_node : vNodes) {
				auto node = mine_node->node_;
				int index = 0;
				auto child = node->GetFirstChild();
				auto m = SearchSlibling(child, [this,mine_node,&index](CefRefPtr<CefDOMNode>  n)->bool {
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
						if (mIndex == -1 || index++ == mIndex) {
							CefRefPtr<DOMNode> r_node = new DOMNode(n);
							mine_node->AddChild(r_node);
							break;
						}
					} while (0);
					return rst;
					});
			}
		} while (0);
		DOMNodeMatcher::Match(vNodes);
		return ;
	}

	void DOMNodePerpertyMatcher::Match(vector<CefRefPtr<DOMNode>> vNodes)
	{
		vector <CefRefPtr<DOMNode>> vResutl;
		//do {
		//	for ( auto & node : vNodes) {
		//		int index = 0;
		//		auto child = node->node_->GetFirstChild();
		//		SearchSlibling(child, [&vResutl, this, &index](CefRefPtr<DOMNode>  n)->bool {
		//			bool  rst = false;
		//			do {
		//				if (n.get() == nullptr) {
		//					rst = true;
		//					break;
		//				}
		//				if (NeedSkip(n)) {
		//					break;
		//				}
		//				if (!n->node_->HasElementAttribute(mPerpertyName)) {
		//					break;
		//				}
		//				auto value = n->node_->GetElementAttribute(mPerpertyName);
		//				if (!mPerpertyValue.empty() &&  mPerpertyValue.compare(value) != 0)
		//					break;

		//				if (mIndex == -1) {
		//					//vResutl.push_back(n);
		//					break;
		//				}
		//				if (index++ == mIndex) {
		//					//vResutl.push_back(n);
		//					rst = true;
		//				}
		//			} while (0);
		//			return rst;
		//			});

		//	}
		//} while (0);
		
		return DOMNodeMatcher::Match(vNodes);
	}

	void  DOMNodeMatcher::Match(vector<CefRefPtr<DOMNode>> vNode)
	{
		if (next_) {
			for (auto node : vNode)
			{
				auto childer = node->children;
				next_->Match(childer);
			}
		}
		return;
	}

};


