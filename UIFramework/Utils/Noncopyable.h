#pragma once
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
