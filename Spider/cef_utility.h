#pragma once
#include <include/cef_base.h>
#include <string>
#include <sstream>
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
	//public typedef enum { DOM_NODE_TYPE_UNSUPPORTED = 0, DOM_NODE_TYPE_ELEMENT, DOM_NODE_TYPE_ATTRIBUTE, DOM_NODE_TYPE_TEXT, DOM_NODE_TYPE_CDATA_SECTION, DOM_NODE_TYPE_PROCESSING_INSTRUCTIONS, DOM_NODE_TYPE_COMMENT, DOM_NODE_TYPE_DOCUMENT, DOM_NODE_TYPE_DOCUMENT_TYPE, DOM_NODE_TYPE_DOCUMENT_FRAGMENT, } cef_dom_node_type_t;

}
