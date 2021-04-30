#pragma once
#include <Windows.h>
#include <memory>
#include <string>
#include <tchar.h>
#include <sstream>
#include <vector>
#include <include/cef_base.h>
#include <include/cef_task.h>
using std::shared_ptr;
using std::unique_ptr;
using std::vector;
using std::string;
using std::wstring;
namespace seraphim {

	static const wchar_t* TAG = L"<seraphim>";
	static const wchar_t* kCmdVisitDom  = L"VISIT_DOM_CMD" ;
	static const wchar_t* kMessageBrowserCreated= L"BR_MSG_BROWSER_CREATE";
	static const wchar_t* kKeyUserID = L"KEY_USER_ID";
	static const wchar_t* kKeyParentID = L"KEY_PAREMT_ID";
	static const int kIndexUserID = 0;
	static const int kIndexParentID = 1;
	static int  kDataId{ 100 };
	extern int kTopBrowserUserID;
	extern int kChildBrowserUserID;
};