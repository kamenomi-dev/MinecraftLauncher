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

#define FMT_UNICODE 0
#define SPDLOG_NO_EXCEPTIONS
#define SPDLOG_WCHAR_TO_UTF8_SUPPORT
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/sinks/stdout_color_sinks.h>

using std::string;
using std::wstring;
using Gdiplus::Rect;
using Gdiplus::Size;
using Gdiplus::Point;

#endif // PCH_H
