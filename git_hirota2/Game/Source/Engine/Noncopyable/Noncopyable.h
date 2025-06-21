#pragma once
class Noncopyable
{
protected:
    Noncopyable() {}
    ~Noncopyable() {}
private:
    void operator =(const Noncopyable& src);
    Noncopyable(const Noncopyable& src);
};

