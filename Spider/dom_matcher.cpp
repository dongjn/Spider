#include "common.h"
#include "cef_log_utility.h"
#include "common_log.h"
#include "dom_matcher.h"
#include "dom_utility.h"
#include <any>
namespace seraphim {




	void DOMNodeNameMatcher::Match(vector<shared_ptr<DOMNode>> vNodes)
	{
		for (shared_ptr<DOMNode> mine_node : vNodes) {
			auto node = mine_node->GetNode();
			int index = 0;
			auto child = node->GetFirstChild();
			SearchSlibling(child, [this, mine_node, &index](CefRefPtr<CefDOMNode>  n)->bool {
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
					shared_ptr<DOMNode> r_node = std::make_shared<DOMNode>(n,op_);

					if (mIndex == -1) {
						mine_node->AddChild(r_node);
						rst = false;
						break;
					}
					if (index++ == mIndex) {
						mine_node->AddChild(r_node);
						rst = true;
					}
				} while (0);
				return rst;
				});
		}
		DOMNodeMatcher::Match(vNodes);
		return;
	}

	void DOMNodePerpertyMatcher::Match(vector<shared_ptr<DOMNode>> vNodes)
	{
		do {
			for (auto& node : vNodes) {
				int index = 0;
				auto child = node->GetNode()->GetFirstChild();
				SearchSlibling(child, [this, node, &index](CefRefPtr<CefDOMNode>  n)->bool {
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
							rst == false;
							break;
						}
						auto value = n->GetElementAttribute(mPerpertyName);
						if (!mPerpertyValue.empty() && mPerpertyValue.compare(value) != 0) {
							rst = false;
							break;
						}
						if (mIndex != -1 && index++ != mIndex) {
							rst = false;
							break;
						}

						shared_ptr<DOMNode> r_node = std::make_shared<DOMNode>(n,op_);// = new DOMNode(n, op_);
						node->AddChild(r_node);
					} while (0);
					return rst;
					});
			}
		} while (0);

		return DOMNodeMatcher::Match(vNodes);
	}

	void  DOMNodeMatcher::Match(vector<shared_ptr<DOMNode>> vNode)
	{
		if (mNextLayer) {
			for (auto node : vNode)
			{
				auto childer = node->children;
				mNextLayer->Match(childer);
			}
		}
		return;
	}

};


