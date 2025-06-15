#pragma once

#ifndef _UIFramework_Utils_Noncopyable_H_
#define _UIFramework_Utils_Noncopyable_H_

namespace UIFramework {
namespace Utils {
class Noncopyable {
  public:
    Noncopyable() = default;

    Noncopyable(const Noncopyable&)            = delete;
    Noncopyable(Noncopyable&&)                 = delete;
    Noncopyable& operator=(const Noncopyable&) = delete;
    Noncopyable& operator=(Noncopyable&&)      = delete;

    virtual ~Noncopyable() = default;
};
} // namespace Utils
} // namespace UIFramework

#endif // !_UIFramework_Utils_Noncopyable_H_
