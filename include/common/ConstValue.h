#pragma once

#include "common/Type.h" // Update this path to the correct relative path to Type.h
#include <variant> 
#include <string>
#include <vector>
#include <unordered_map>

#define TODO(s) do { printf("todo: %s\n", s); std::exit(0); } while (0)

struct ConstValue //存储常量值
{   
    std::variant<
        int,          // 整型（对应int）
        float         // 浮点型（对应float）
    > data;
    TYPE type; // 类型

    public:
    ConstValue() : data(0), type(TYPE::TYPE_INT) {} // Default constructor


    ConstValue(int value, TYPE t)
    {
        data = value;
        type = t;
    }

    // ConstValue(std::initializer_list<std::variant<int, float>> init_list, TYPE t)
    // {
    //     if (init_list.size() == 1)
    //     {
    //         data = *init_list.begin();
    //         type = t;
    //     }
    //     else
    //     {
    //         TODO("Unsupported initializer list size for ConstValue");
    //     }
    // }

    ConstValue(std::variant<int, float> value, TYPE t)
    {
        data = value;
        type = t;
    }
    ConstValue(float value, TYPE t)
    {
        data = value;
        type = t;
    }

    int getInt() const
    {
        if (std::holds_alternative<int>(data)) {
            return std::get<int>(data);
        } 
        else {
            TODO("Unsupported type in ConstValue");
            return 0; // Unreachable
        }
    }
    int getFloat() const
    {
        if (std::holds_alternative<float>(data)) {
            return std::get<float>(data);
        }
        else {
            TODO("Unsupported type in ConstValue");
            return 0; // Unreachable
        }
    }

    void intToFloat()
    {
        if (std::holds_alternative<int>(data)) {
            data = static_cast<float>(std::get<int>(data));
            type = TYPE_FLOAT;
        } 
        else if(std::holds_alternative<float>(data)) {
            // Already a float, do nothing
        } 
        else
        {
            TODO("Unsupported type in ConstValue");
        }
    }

    void floatToInt()
    {
        if(std::holds_alternative<float>(data))
        {
            data = static_cast<int>(std::get<float>(data));
            type = TYPE_INT;
        }
        else if(std::holds_alternative<int>(data))
        {
            // Already a int, do no thing
        }
        else
        {
            TODO("Unsupported type in ConstValue");
        }
    }

    void print() const
    {
        if(type == TYPE::TYPE_INT)
        {
            printf("ConstValue: %d\n", std::get<int>(data));
        }
        else if(type == TYPE::TYPE_FLOAT)
        {
            printf("ConstValue: %f\n", std::get<float>(data));
        }
        else
        {
            TODO("不支持的类型");
        }
    }

    std::string toString() const
    {
        if(type == TYPE::TYPE_INT)
        {
            return std::to_string(std::get<int>(data));
        }
        else if(type == TYPE::TYPE_FLOAT)
        {
            return std::to_string(std::get<float>(data));
        }
        else
        {
            TODO("不支持的类型");
            return "";
        }
    }

    ConstValue operator+ (const ConstValue& other) const
    {
        if(type == TYPE_INT && other.type == TYPE_INT)
        {
            return {std::get<int>(data) + std::get<int>(other.data), TYPE_INT};
        }
        else if(type == TYPE_FLOAT && other.type == TYPE_FLOAT)
        {
            return {std::get<float>(data) + std::get<float>(other.data), TYPE_FLOAT};
        }
        else if(type == TYPE_INT && other.type == TYPE_FLOAT)
        {
            return {std::get<int>(data) + std::get<float>(other.data), TYPE_FLOAT};
        }
        else if(type == TYPE_FLOAT && other.type == TYPE_INT)
        {
            return {std::get<float>(data) + std::get<int>(other.data), TYPE_FLOAT};
        }
        else
        {
            TODO("不支持的类型相加");
            return {};
        }
    }

    ConstValue operator- (const ConstValue& other) const
    {
        if(type == TYPE_INT && other.type == TYPE_INT)
        {
            return {std::get<int>(data) - std::get<int>(other.data), TYPE_INT};
        }
        else if(type == TYPE_FLOAT && other.type == TYPE_FLOAT)
        {
            return {std::get<float>(data) - std::get<float>(other.data), TYPE_FLOAT};
        }
        else if(type == TYPE_INT && other.type == TYPE_FLOAT)
        {
            return {std::get<int>(data) - std::get<float>(other.data), TYPE_FLOAT};
        }
        else if(type == TYPE_FLOAT && other.type == TYPE_INT)
        {
            return {std::get<float>(data) - std::get<int>(other.data), TYPE_FLOAT};
        }
        else
        {
            TODO("不支持的类型相减");
            return {};
        }
    }

    ConstValue operator* (const ConstValue& other) const
    {
        if(type == TYPE_INT && other.type == TYPE_INT)
        {
            return {std::get<int>(data) * std::get<int>(other.data), TYPE_INT};
        }
        else if(type == TYPE_FLOAT && other.type == TYPE_FLOAT)
        {
            return {std::get<float>(data) * std::get<float>(other.data), TYPE_FLOAT};
        }
        else if(type == TYPE_INT && other.type == TYPE_FLOAT)
        {
            return {std::get<int>(data) * std::get<float>(other.data), TYPE_FLOAT};
        }
        else if(type == TYPE_FLOAT && other.type == TYPE_INT)
        {
            return {std::get<float>(data) * std::get<int>(other.data), TYPE_FLOAT};
        }
        else
        {
            TODO("不支持的类型相乘");
            return {};
        }
    }
    ConstValue operator/ (const ConstValue& other) const
    {
        if(type == TYPE_INT && other.type == TYPE_INT)
        {
            return {std::get<int>(data) / std::get<int>(other.data), TYPE_INT};
        }
        else if(type == TYPE_FLOAT && other.type == TYPE_FLOAT)
        {
            return {std::get<float>(data) / std::get<float>(other.data), TYPE_FLOAT};
        }
        else if(type == TYPE_INT && other.type == TYPE_FLOAT)
        {
            return {std::get<int>(data) / std::get<float>(other.data), TYPE_FLOAT};
        }
        else if(type == TYPE_FLOAT && other.type == TYPE_INT)
        {
            return {std::get<float>(data) / std::get<int>(other.data), TYPE_FLOAT};
        }
        else
        {
            TODO("不支持的类型相除");
            return {};
        }
    }
    ConstValue operator% (const ConstValue& other) const
    {
        if(type == TYPE_INT && other.type == TYPE_INT)
        {
            return {std::get<int>(data) % std::get<int>(other.data), TYPE_INT};
        }
        else
        {
            TODO("不支持的类型取模");
            return {};
        }
    }
    ConstValue operator== (const ConstValue& other) const
    {
        if(type == TYPE_INT && other.type == TYPE_INT)
        {
            return {std::get<int>(data) == std::get<int>(other.data), TYPE_INT};
        }
        else if(type == TYPE_FLOAT && other.type == TYPE_FLOAT)
        {
            return {std::get<float>(data) == std::get<float>(other.data), TYPE_INT};
        }
        else if(type == TYPE_INT && other.type == TYPE_FLOAT)
        {
            return {std::get<int>(data) == std::get<float>(other.data), TYPE_INT};
        }
        else if(type == TYPE_FLOAT && other.type == TYPE_INT)
        {
            return {std::get<float>(data) == std::get<int>(other.data), TYPE_INT};
        }
        else
        {
            TODO("不支持的类型相等比较");
            return {};
        }
    }
    ConstValue operator!= (const ConstValue& other) const
    {
        if(type == TYPE_INT && other.type == TYPE_INT)
        {
            return {std::get<int>(data) != std::get<int>(other.data), TYPE_INT};
        }
        else if(type == TYPE_FLOAT && other.type == TYPE_FLOAT)
        {
            return {std::get<float>(data) != std::get<float>(other.data), TYPE_INT};
        }
        else if(type == TYPE_INT && other.type == TYPE_FLOAT)
        {
            return {std::get<int>(data) != std::get<float>(other.data), TYPE_INT};
        }
        else if(type == TYPE_FLOAT && other.type == TYPE_INT)
        {
            return {std::get<float>(data) != std::get<int>(other.data), TYPE_INT};
        }
        else
        {
            TODO("不支持的类型不等比较");
            return {};
        }
    }
    ConstValue operator< (const ConstValue& other) const
    {
        if(type == TYPE_INT && other.type == TYPE_INT)
        {
            return {std::get<int>(data) < std::get<int>(other.data), TYPE_INT};
        }
        else if(type == TYPE_FLOAT && other.type == TYPE_FLOAT)
        {
            return {std::get<float>(data) < std::get<float>(other.data), TYPE_INT};
        }
        else if(type == TYPE_INT && other.type == TYPE_FLOAT)
        {
            return {std::get<int>(data) < std::get<float>(other.data), TYPE_INT};
        }
        else if(type == TYPE_FLOAT && other.type == TYPE_INT)
        {
            return {std::get<float>(data) < std::get<int>(other.data), TYPE_INT};
        }
        else
        {
            TODO("不支持的类型小于比较");
            return {};
        }
    }
    ConstValue operator> (const ConstValue& other) const
    {
        if(type == TYPE_INT && other.type == TYPE_INT)
        {
            return {std::get<int>(data) > std::get<int>(other.data), TYPE_INT};
        }
        else if(type == TYPE_FLOAT && other.type == TYPE_FLOAT)
        {
            return {std::get<float>(data) > std::get<float>(other.data), TYPE_INT};
        }
        else if(type == TYPE_INT && other.type == TYPE_FLOAT)
        {
            return {std::get<int>(data) > std::get<float>(other.data), TYPE_INT};
        }
        else if(type == TYPE_FLOAT && other.type == TYPE_INT)
        {
            return {std::get<float>(data) > std::get<int>(other.data), TYPE_INT};
        }
        else
        {
            TODO("不支持的类型大于比较");
            return {};
        }
    }
    ConstValue operator<= (const ConstValue& other) const
    {
        if(type == TYPE_INT && other.type == TYPE_INT)
        {
            return {std::get<int>(data) <= std::get<int>(other.data), TYPE_INT};
        }
        else if(type == TYPE_FLOAT && other.type == TYPE_FLOAT)
        {
            return {std::get<float>(data) <= std::get<float>(other.data), TYPE_INT};
        }
        else if(type == TYPE_INT && other.type == TYPE_FLOAT)
        {
            return {std::get<int>(data) <= std::get<float>(other.data), TYPE_INT};
        }
        else if(type == TYPE_FLOAT && other.type == TYPE_INT)
        {
            return {std::get<float>(data) <= std::get<int>(other.data), TYPE_INT};
        }
        else
        {
            TODO("不支持的类型小于等于比较");
            return {};
        }
    }
    ConstValue operator>= (const ConstValue& other) const
    {
        if(type == TYPE_INT && other.type == TYPE_INT)
        {
            return {std::get<int>(data) >= std::get<int>(other.data), TYPE_INT};
        }
        else if(type == TYPE_FLOAT && other.type == TYPE_FLOAT)
        {
            return {std::get<float>(data) >= std::get<float>(other.data), TYPE_INT};
        }
        else if(type == TYPE_INT && other.type == TYPE_FLOAT)
        {
            return {std::get<int>(data) >= std::get<float>(other.data), TYPE_INT};
        }
        else if(type == TYPE_FLOAT && other.type == TYPE_INT)
        {
            return {std::get<float>(data) >= std::get<int>(other.data), TYPE_INT};
        }
        else
        {
            TODO("不支持的类型大于等于比较");
            return {};
        }
    }
    ConstValue operator&& (const ConstValue& other) const
    {
        if(type == TYPE_INT && other.type == TYPE_INT)
        {
            return {std::get<int>(data) && std::get<int>(other.data), TYPE_INT};
        }
        else if(type == TYPE_FLOAT && other.type == TYPE_FLOAT)
        {
            return {std::get<float>(data) && std::get<float>(other.data), TYPE_INT};
        }
        else if(type == TYPE_INT && other.type == TYPE_FLOAT)
        {
            return {std::get<int>(data) && std::get<float>(other.data), TYPE_INT};
        }
        else if(type == TYPE_FLOAT && other.type == TYPE_INT)
        {
            return {std::get<float>(data) && std::get<int>(other.data), TYPE_INT};
        }
        else
        {
            TODO("不支持的类型与运算");
            return {};
        }
    }
    ConstValue operator|| (const ConstValue& other) const
    {
        if(type == TYPE_INT && other.type == TYPE_INT)
        {
            return {std::get<int>(data) || std::get<int>(other.data), TYPE_INT};
        }
        else if(type == TYPE_FLOAT && other.type == TYPE_FLOAT)
        {
            return {std::get<float>(data) || std::get<float>(other.data), TYPE_INT};
        }
        else if(type == TYPE_INT && other.type == TYPE_FLOAT)
        {
            return {std::get<int>(data) || std::get<float>(other.data), TYPE_INT};
        }
        else if(type == TYPE_FLOAT && other.type == TYPE_INT)
        {
            return {std::get<float>(data) || std::get<int>(other.data), TYPE_INT};
        }
        else
        {
            TODO("不支持的类型或运算");
            return {};
        }
    }
    ConstValue operator! () const
    {
        if(type == TYPE_INT)
        {
            return {!std::get<int>(data), TYPE_INT};
        }
        else if(type == TYPE_FLOAT)
        {
            return {!std::get<float>(data), TYPE_INT};
        }
        else
        {
            TODO("不支持的类型取反");
            return {};
        }
    }
    ConstValue operator- () const
    {
        if(type == TYPE_INT)
        {
            return {-std::get<int>(data), TYPE_INT};
        }
        else if(type == TYPE_FLOAT)
        {
            return {-std::get<float>(data), TYPE_FLOAT};
        }
        else
        {
            TODO("不支持的类型取反");
            return {};
        }
    }
    ConstValue operator+ () const
    {
        if(type == TYPE_INT)
        {
            return {std::get<int>(data), TYPE_INT};
        }
        else if(type == TYPE_FLOAT)
        {
            return {std::get<float>(data), TYPE_FLOAT};
        }
        else
        {
            TODO("不支持的类型取正");
            return {};
        }
    }
    
};


struct MultipleConstValue  //多重常量值
{
    std::variant<
        int,          // 整型（对应int）
        float,         // 浮点型（对应float）
        std::vector < MultipleConstValue >  // 数组的嵌套结构
    > data;
    TYPE type; // 类型

    public:
    MultipleConstValue() : data(0), type(TYPE::TYPE_INT) {} // Default constructor
    MultipleConstValue(ConstValue value)
    {
        if (std::holds_alternative<int>(value.data)) {
            data = std::get<int>(value.data);
        } else if (std::holds_alternative<float>(value.data)) {
            data = std::get<float>(value.data);
        } else {
            TODO("Unsupported type in ConstValue for MultipleConstValue assignment");
        }
        type = value.type;
    }
    MultipleConstValue(int value, TYPE t)
    {
        data = value;
        type = t;
    }
    MultipleConstValue(float value, TYPE t)
    {
        data = value;
        type = t;
    }

    MultipleConstValue operator[](int index) const
    {
        if (std::holds_alternative<std::vector<MultipleConstValue>>(data)) {
            const auto& vec = std::get<std::vector<MultipleConstValue>>(data);
            if (index < 0 || index >= static_cast<int>(vec.size())) {
                TODO("Index out of bounds in MultipleConstValue");
            }
            return vec[index];
        } else {
            TODO("Unsupported type in MultipleConstValue for indexing");
        }
    }

    bool isArray() const
    {
        return std::holds_alternative<std::vector<MultipleConstValue>>(data);
    }

    // 只读访问（const 版本，返回 const 引用）
    const std::vector<MultipleConstValue>& getArray() const
    {
        if (isArray()) {
            return std::get<std::vector<MultipleConstValue>>(data);
        } else {
            TODO("Not an array in MultipleConstValue");
        }
    }
 
    // 可写访问（非 const 版本，返回非 const 引用）
    std::vector<MultipleConstValue>& getArray() 
    {
        if (isArray()) {
            return std::get<std::vector<MultipleConstValue>>(data);
        } else {
            TODO("Not an array in MultipleConstValue");
        }
    }

    ConstValue getConstValue()
    {
        if (std::holds_alternative<int>(data)) {
            return ConstValue(std::get<int>(data), TYPE_INT);
        } else if (std::holds_alternative<float>(data)) {
            return ConstValue(std::get<float>(data), TYPE_FLOAT);
        } else {
            TODO("Unsupported type in MultipleConstValue");
        }
    }

    int getInt()
    {
        if (std::holds_alternative<int>(data)) {
            return std::get<int>(data);
        } 
        else {
            TODO("Unsupported type in MultipleConstValue");
        }
    }

    int getFloat()
    {
        if (std::holds_alternative<float>(data)) {
            return std::get<float>(data);
        }
        else {
            TODO("Unsupported type in MultipleConstValue");
        }
    }
    

    void addToArray(MultipleConstValue value)
    {
        if (isArray()) {
            std::get<std::vector<MultipleConstValue>>(data).push_back(value);
        } else {
            TODO("Not an array in MultipleConstValue");
        }
    }

    void print() const
    {
        printf("type: %d, ", type);
        if (std::holds_alternative<int>(data)) {
            printf("int: %d\n", std::get<int>(data));
        } else if (std::holds_alternative<float>(data)) {
            printf("float: %f\n", std::get<float>(data));
        } else if (std::holds_alternative<std::vector<MultipleConstValue>>(data)) {
            printf("array: [");
            for (const auto& item : std::get<std::vector<MultipleConstValue>>(data)) {
                item.print();
            }
            printf("]\n");
        } else {
            TODO("Unsupported type in MultipleConstValue");
        }
    }
    void toString() const
    {
        if (std::holds_alternative<int>(data)) {
            printf("int: %d\n", std::get<int>(data));
        } else if (std::holds_alternative<float>(data)) {
            printf("float: %f\n", std::get<float>(data));
        } else if (std::holds_alternative<std::vector<MultipleConstValue>>(data)) {
            printf("array: [");
            for (const auto& item : std::get<std::vector<MultipleConstValue>>(data)) {
                item.toString();
            }
            printf("]\n");
        } else {
            TODO("Unsupported type in MultipleConstValue");
        }
    }
};