#include "Value.h"

namespace ZIR
{
    std::string Value::ident() const
    {
        return "%" + name;
    }

    std::string IntValue::toStr() const
    {
        if (!isConst)
            return "[Int var " + name + "]";
        return "[Int const " + name + " = " + std::to_string(val) + "]";
    }

    std::string ArrValue::toStr() const
    {
        std::stringstream ss;
        if (!isConst)
            ss << "[Array var " << name;
        else
            ss << "[Array const " << name;
        ss << ", size " << size;
        if (!isConst)
        {
            for (auto i : val)
                ss << " " << i;
        }
        ss << "]";
        return ss.str();
    }
}