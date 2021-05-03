#include "dom_indices_extractor.h"
#include <vector>
#include "common.h"
#include "cef_log_utility.h"
#include "log.h"
namespace seraphim {
	using std::vector;
	
	inline  CefRefPtr<CefDOMNode>  SkipHeadText(CefRefPtr<CefDOMNode> node) {
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
		return node.get() == nullptr || node->GetType() == DOM_NODE_TYPE_TEXT  || node->GetType() == DOM_NODE_TYPE_COMMENT;
	}

	CefRefPtr<CefDOMNode> DomIndicesExtractor::ErgodicNode(CefRefPtr<CefDOMNode> node, int deep)
	{
		if (deep > mIndeices.size() - 1)
			return node;
		if (!node->HasChildren()) {
			throw DomExtractorError{ deep ,L"Error Of None Child Node !", node };
		}
		if (NeedSkip(node)) {
			throw  DomExtractorError{ deep,L"Error Of Node's Type !",node };
		}

		auto child = node->GetFirstChild();
		child = SkipHeadText(child);
		int index = mIndeices[deep];
		for (; index > 0 && child.get() != nullptr;) {
			child = child->GetNextSibling();
			if (NeedSkip(child)) {
				continue;
			}
			index--;
		}
		if (child.get() == nullptr) {
			throw DomExtractorError{ deep, L"Error Of Not Find Node", node };
		}

		return ErgodicNode(child, ++deep);
	}

	DomIndicesExtractor::DomIndicesExtractor(const vector<int>& indices, const vector<CefString>& properties, bool isArray) :mPropertyKeys(properties), mISArray(isArray), mIndeices(indices)
	{
	}
	void DomIndicesExtractor::Extraction(CefRefPtr<CefDOMNode> node, vector <DomInfo>& infos)
	{
		//auto node = document->GetBody();
		//node = node->GetFirstChild();
		//node = SkipHeadText(node);

		auto dst = ErgodicNode(node, 0);
		WLOG(10, TAG, L"Extractor node", dst);
		if (!mISArray) {
			DomInfo info;
			info.value = node->GetValue();
			info.rect = node->GetElementBounds();
			for (auto& key : mPropertyKeys) {
				auto property = node->GetElementAttribute(key);
				info.properties.insert(std::make_pair(key, property));
			}
		}
		else {
		}
	}
};