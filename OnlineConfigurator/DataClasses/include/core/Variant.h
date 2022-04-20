#ifndef _VARIANT_H_
#define _VARIANT_H_

#include <variant>
#include <string>

typedef std::variant<bool, int, float, std::string> VariantType;

template<typename T, typename VARIANT_T>
struct IsVariantMember;

template<typename T, typename... ALL_T>
struct IsVariantMember<T, std::variant<ALL_T...>>  : public std::disjunction<std::is_same<T, ALL_T>...> {};

class Variant final
{
private:

public:
    Variant() = default;

    template<typename T>
    Variant(const T& t) :
        _isEmpty(false),
        _data(t)
    {
        static_assert(IsVariantMember<T, VariantType>::value);
    }

    Variant(const Variant& other);

    virtual ~Variant() = default;

    template<typename T>
    Variant& operator=(const T& t)
    {
        static_assert(IsVariantMember<T, VariantType>::value);

        _isEmpty = false;
        _data = t;
        return *this;
    }

    bool operator==(const Variant& other) const;

    bool operator!=(const Variant& other) const;

public:
    bool isEmpty() const;

    bool toBool() const;

    int toInt() const;

    float toFloat() const;

    std::string toString() const;

private:
    bool        _isEmpty = true;
    VariantType _data;
};

#endif //_VARIANT_H_
