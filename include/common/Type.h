#pragma once

#include <variant> 
#include <string>
#include <vector>
#include <unordered_map>

#define TODO(s) do { printf("todo: %s\n", s); std::exit(0); } while (0)

enum TYPE { TYPE_VOID, TYPE_INT, TYPE_FLOAT, TYPE_STRING, TYPE_ERROR };

struct MuiltipleType
{
    public:
    std::variant <TYPE,std::vector<MuiltipleType>> data;
    
    MuiltipleType() : data(TYPE::TYPE_VOID) {} // Default constructor
    MuiltipleType(TYPE t) : data(t) {} // Constructor with TYPE
    MuiltipleType(std::vector<MuiltipleType> vec)
    {
        data = vec;
    }

    bool isArray() const
    {
        return std::holds_alternative<std::vector<MuiltipleType>>(data);
    }

    // 只读访问（const 版本，返回 const 引用）
    const std::vector<MuiltipleType>& getArray() const
    {
        if (isArray()) {
            return std::get<std::vector<MuiltipleType>>(data);
        } else {
            TODO("Not an array in MuiltipleType");
        }
    }
    // 可写访问（非 const 版本，返回引用）
    std::vector<MuiltipleType>& getArray()
    {
        if (isArray()) {
            return std::get<std::vector<MuiltipleType>>(data);
        } else {
            TODO("Not an array in MuiltipleType");
        }
    }

};