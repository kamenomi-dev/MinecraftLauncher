#ifndef PCH_H
#define PCH_H

#pragma comment(lib, "Gdiplus.lib")

#include <windows.h>
#include <windowsx.h>
#include <Gdiplus.h>

#include <map>
#include <list>
#include <mutex>
#include <string>
#include <memory>

using std::wstring;
using Gdiplus::Rect;
using Gdiplus::Size;
using Gdiplus::Point;

#pragma execution_character_set("utf-8")
#include <spdlog/spdlog.h>

#endif // PCH_H
