#pragma once

#include <iostream>
#include <set>

#include "../parser/node.h"

template <typename T>
std::set<T> operator&(const std::set<T> &a, const std::set<T> &b)
{
    std::set<T> ret;
    for (const auto &i : a)
    {
        if (b.find(i) != b.end())
        {
            ret.insert(i);
        }
    }
    return ret;
}

template <typename T>
std::set<T> operator|(const std::set<T> &a, const std::set<T> &b)
{
    std::set<T> ret;
    for (const auto &i : a)
    {
        ret.insert(i);
    }
    for (const auto &i : b)
    {
        ret.insert(i);
    }
    return ret;
}

template <typename T>
std::set<T> operator-(const std::set<T> &a, const std::set<T> &b)
{
    std::set<T> ret;
    for (const auto &i : a)
    {
        if (b.find(i) == b.end())
        {
            ret.insert(i);
        }
    }
    return ret;
}

template <typename T>
void operator&=(std::set<T> &a, const std::set<T> &b)
{
    for (const auto &i : a)
    {
        if (b.find(i) == b.end())
        {
            a.erase(i);
        }
    }
}

template <typename T>
void operator|=(std::set<T> &a, const std::set<T> &b)
{
    for (const auto &i : b)
    {
        a.insert(i);
    }
}

template <typename T>
void operator-=(std::set<T> &a, const std::set<T> &b)
{
    for (const auto &i : a)
    {
        if (b.find(i) != b.end())
        {
            a.erase(i);
        }
    }
}

template <typename T, typename... Args>
std::shared_ptr<T> makePtr(Args &&...args)
{
    return std::make_shared<T>(args...);
}