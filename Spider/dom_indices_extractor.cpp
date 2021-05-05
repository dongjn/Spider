//#include "dom_indices_extractor.h"
//#include <vector>
//#include "common.h"
//#include "cef_log_utility.h"
//#include "common_log.h"
//#include "dom_utility.h"
//namespace seraphim {
//	using std::vector;
//	
//
//	CefRefPtr<CefDOMNode> DomIndicesExtractor::ErgodicNode(CefRefPtr<CefDOMNode> node, int deep)
//	{
//		if (deep > mIndeices.size() - 1)
//			return node;
//		if (!node->HasChildren()) {
//			throw DOMError{ deep ,L"Error Of None Child Node !", node };
//		}
//		if (NeedSkip(node)) {
//			throw  DOMError{ deep,L"Error Of Node's Type !",node };
//		}
//
//		auto child = node->GetFirstChild();
//		child = SkipTextNode(child);
//		int index = mIndeices[deep];
//		for (; index > 0 && child.get() != nullptr;) {
//			child = child->GetNextSibling();
//			if (NeedSkip(child)) {
//				continue;
//			}
//			index--;
//		}
//		if (child.get() == nullptr) {
//			throw DOMError{ deep, L"Error Of Not Find Node", node };
//		}
//
//		return ErgodicNode(child, ++deep);
//	}
//
//	DomIndicesExtractor::DomIndicesExtractor(const vector<int>& indices, const vector<CefString>& properties, bool isArray) :mPropertyKeys(properties), mISArray(isArray), mIndeices(indices)
//	{
//	}
//	void DomIndicesExtractor::Extraction(CefRefPtr<CefDOMNode> node, vector <DOMNode>& infos)
//	{
//		//auto node = document->GetBody();
//		//node = node->GetFirstChild();
//		//node = SkipHeadText(node);
//
//		auto dst = ErgodicNode(node, 0);
//		WLOG(10, TAG, L"Extractor node", dst);
//		if (!mISArray) {
//			DOMNode info;
//			info.value = node->GetValue();
//			info.rect = node->GetElementBounds();
//			for (auto& key : mPropertyKeys) {
//				auto property = node->GetElementAttribute(key);
//				info.properties.insert(std::make_pair(key, property));
//			}
//		}
//		else {
//		}
//	}
//};