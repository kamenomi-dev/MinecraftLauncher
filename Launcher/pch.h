#pragma once

#ifndef __PCH_H__
#define __PCH_H__

// Unicode support.
#ifndef _UNICODE
#define _UNICODE
#endif

#include <dwmapi.h>
#include <windows.h>
#include <windowsx.h>
#pragma comment(lib, "Dwmapi.lib")
#pragma comment(lib, "Msimg32.lib")

#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")

#include <memory>
#include <string>
#include <unordered_map>

using namespace std::literals;

using std::make_unique;
using std::unique_ptr;

using std::wstring;
using std::unordered_map;

#endif // _PCH_H__