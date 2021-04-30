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
	static const  wchar_t* VISIT_DOM_CMD  = L"VISIT_DOM_CMD" ;
	static const wchar_t* kUserIdKey = L"user_id";
	extern int kTopBrowserUserID;
	extern int kChildBrowserUserID;
};