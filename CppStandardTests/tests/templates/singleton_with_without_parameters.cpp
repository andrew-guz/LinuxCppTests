#include "../catch.hpp"

template<typename T, typename ...Types>
class Singleton
{  
protected:
    Singleton() = default;

public:
    virtual ~Singleton() = default;

  	static T* Instance()
    {
        static T s_instance;
        return &s_instance;
    }
  
    static T* Instance(const Types& ...args)
    {
     	static T s_instance { args... };
      	return &s_instance;
    }
};

template<typename T>
class Singleton<T>
{  
protected:
    Singleton() = default;

public:
    virtual ~Singleton() = default;

  	static T* Instance()
    {
        static T s_instance;
        return &s_instance;
    }
};

struct A : public Singleton<A, int>
{
	A(int i = 6) : _i(i) {}
    
	int _i;
};

struct B : public Singleton<B>
{
    int _i = 7;
};

TEST_CASE("Create singleton with/without ctor parameters")
{
    REQUIRE(A::Instance(5)->_i == 5);
    REQUIRE(A::Instance()->_i == 6);
    REQUIRE(B::Instance()->_i == 7);
}
