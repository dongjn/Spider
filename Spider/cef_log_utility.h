#pragma once
#include <string>
#include <sstream>
#include <include/cef_base.h>
#include <include/cef_request.h>
#include <include/cef_response.h>
#include <include/cef_dom.h>
namespace seraphim {
	using  std::wstringstream;
	using std::wstring;
	enum class DomNoteType {
		DOM_NODE_TYPE_UNSUPPORTED = 0,
		DOM_NODE_TYPE_ELEMENT,
		DOM_NODE_TYPE_ATTRIBUTE,
		DOM_NODE_TYPE_TEXT,
		DOM_NODE_TYPE_CDATA_SECTION,
		DOM_NODE_TYPE_PROCESSING_INSTRUCTIONS,
		DOM_NODE_TYPE_COMMENT,
		DOM_NODE_TYPE_DOCUMENT,
		DOM_NODE_TYPE_DOCUMENT_TYPE,
		DOM_NODE_TYPE_DOCUMENT_FRAGMENT
	};

	inline wstringstream& operator<<(wstringstream& os, enum DomNoteType type) {
		switch (type)
		{
		case DomNoteType::DOM_NODE_TYPE_UNSUPPORTED:
			os << L"DOM_NODE_TYPE_UNSUPPORTED";
			break;
		case DomNoteType::DOM_NODE_TYPE_ELEMENT:
			os << L"DOM_NODE_TYPE_ELEMENT";
			break;
		case DomNoteType::DOM_NODE_TYPE_ATTRIBUTE:
			os << L"DOM_NODE_TYPE_ATTRIBUTE";
			break;
		case DomNoteType::DOM_NODE_TYPE_TEXT:
			os << L"DOM_NODE_TYPE_TEXT";
			break;
		case DomNoteType::DOM_NODE_TYPE_CDATA_SECTION:
			os << L"DOM_NODE_TYPE_CDATA_SECTION";
			break;
		case DomNoteType::DOM_NODE_TYPE_PROCESSING_INSTRUCTIONS:
			os << L"DOM_NODE_TYPE_PROCESSING_INSTRUCTIONS";
			break;
		case DomNoteType::DOM_NODE_TYPE_COMMENT:
			os << L"DOM_NODE_TYPE_COMMENT";
			break;
		case DomNoteType::DOM_NODE_TYPE_DOCUMENT:
			os << L"DOM_NODE_TYPE_DOCUMENT";
			break;
		case DomNoteType::DOM_NODE_TYPE_DOCUMENT_TYPE:
			os << L"DOM_NODE_TYPE_DOCUMENT_TYPE";
			break;
		case DomNoteType::DOM_NODE_TYPE_DOCUMENT_FRAGMENT:
			os << L"DOM_NODE_TYPE_DOCUMENT_FRAGMENT";
			break;
		default:
			break;
		}
		return os;
	}

	//inline wstringstream& operator<<(wstringstream& os, const CefString& str) {
	//	wstring msg = str.ToWString();
	//	os << msg;
	//	return os;
	//}

	inline wstringstream& operator<<(wstringstream& os, const CefRect bound) {
		os << L"<" << bound.x << L"," << bound.y << L"," << bound.width << L"," << bound.height << L">";
		return os;
	}

	inline wstringstream& operator<<(wstringstream& os, CefRefPtr<CefRequest> request) {
		os << L"[CefRequest<" << L"]";// << bound.x << L"," << bound.y << L"," << bound.width << L"," << bound.height << L">";
		return os;
	}
	inline wstringstream& operator<<(wstringstream& os, CefRefPtr<CefResponse> request) {
		os << L"[CefResponse]<" << L"]";// << bound.x << L"," << bound.y << L"," << bound.width << L"," << bound.height << L">";
		return os;
	}

	inline wstringstream& operator<<(wstringstream& os, CefRefPtr<CefDOMNode> node) {

		do {
			if (node.get() == nullptr) {
				os << L"node is Empty";
				break;
			}
			auto type = node->GetType();

			os << L"<type=" << type<<L">";
			if (type == DOM_NODE_TYPE_TEXT) {
				auto value = node->GetValue();
				os << L"value = {" << value.ToWString()<< L"}";
				break;
			}

			auto name = node->GetName();
			os << L"<name :" << name.ToWString()<< L">";

			CefDOMNode::AttributeMap  attributeMap;
			node->GetElementAttributes(attributeMap);
			for (auto& attribute : attributeMap) {
				auto key = attribute.first.ToWString();
				auto value = attribute.second.ToWString();
				os << L"{" << key << L":" << value << L"}";
			}
			auto szValue = node->GetValue();
			os << L"value:" << szValue.ToWString();
		} while (0);

		return os;
	}



	inline  bool  operator<(CefRefPtr<CefRequest> l, CefRefPtr<CefRequest> r) {
		bool rst = false;
		do {
			const CefString& lurl = l->GetURL();
			const CefString& rurl = r->GetURL();
			return  lurl.compare(rurl) < 0;
		} while (0);
		return rst;
	}


}