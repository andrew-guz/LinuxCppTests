#ifndef _VARIANT_H_
#define _VARIANT_H_

#include <variant>
#include <string>

class Variant final
{
public:
    Variant() = default;

    Variant(bool value);

    Variant(int value);

    Variant(float value);

    Variant(const std::string& value);

    Variant(const Variant& other);

    virtual ~Variant() = default;

    Variant& operator=(bool value);

    Variant& operator=(int value);

    Variant& operator=(float value);

    Variant& operator=(const std::string& value);

    bool operator==(const Variant& other) const;

    bool operator!=(const Variant& other) const;

public:
    bool isEmpty() const;

    bool toBool() const;

    int toInt() const;

    float toFloat() const;

    std::string toString() const;

private:
    bool                                        _isEmpty = true;
    std::variant<bool, int, float, std::string> _data;
};

#endif //_VARIANT_H_
