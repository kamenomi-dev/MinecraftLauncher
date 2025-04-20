#pragma once

#ifndef PCH_H
#define PCH_H

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

#include <bit>
#include <stack>
#include <vector>
#include <memory>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <initializer_list>

using namespace std::literals;

using std::make_unique;
using std::unique_ptr;

using std::initializer_list;
using std::stack;
using std::unordered_map;
using std::vector;
using std::wstring;

#endif // PCH_H