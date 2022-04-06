#ifndef STRVEC_H_
#define STRVEC_H_

#include <memory>
#include <algorithm>
#include <string>
using namespace std;

class StrVec{
public:
    StrVec():elements(nullptr),first_free(nullptr),cap(nullptr){}
    StrVec(initializer_list<string>);
    StrVec(const StrVec&);
    StrVec &operator=(const StrVec&);
    ~StrVec();
    void push_back(const string&);
    size_t size() const {return first_free - elements;}
    size_t capacity() const {return cap - elements;}
    string *begin() const { return elements;}
    string *end() const {return first_free;}
    void reserve(size_t n);
    void resize(size_t n);
    void resize(size_t n, const string &s);

private:
    static allocator<string> alloc; //分配元素
    //被添加元素的函数所使用
    void chk_n_alloc()
    {
        if (size() == capacity()) 
            reallocate();
    }

    pair<string*, string*> alloc_n_copy(const string*,const string*);
    void free();       //销毁元素并释放内存
    void reallocate(); //获得更多内存并拷贝已有元素
    string *elements; //指向数组首元素的指针
    string *first_free; //指向数组第一个空闲元素的指针
    string *cap; //指向数组尾元素的指针
};


StrVec::StrVec(initializer_list<string> il)
{
	auto newdata = alloc_n_copy(il.begin(), il.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}

void StrVec::push_back(const string &s)
{
    chk_n_alloc();//确保有足够的空间容纳新元素
    alloc.construct(first_free++,s); //在first_free指向的元素中构造s的副本
}

pair<string* , string*> StrVec::alloc_n_copy(const string *b, const string *e)
{
    auto data = alloc.allocate(e-b); // 分配空间保存给定范围的元素
    //初始化并返回一个pair，该pair由data和uninitialized_copy的返回值构成
    return {data,uninitalized_copy(b,e,data)};
}

void Strvec::free()
{
    //不能传递给deallocate一个空指针，如果elements为0，函数什么也不做
    if(elements){
        //逆序销毁旧元素
        for(auto p = first_free; P != elements;)
            alloc.destroy(--p);
        alloc.deallocate(elements,cap - elements);
    }
}

// void StrVec::free()
// {
// 	if(elements)
// 	{
// 		std::for_each(elements, first_free, [this](std::string &p){ alloc.destroy(&p); });
// 		alloc.deallocate(elements, cap-elements);
// 	}
// }

StrVec::StrVec(const STrVec &s)
{
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = newdata.second;
}

StrVec::~StrVec(){
    free();
}

StrVec& StrVec::operator=(const StrVec &rhs)
{
    auto newdata = alloc_n_copy(rhs.begin(),rhs.end());
    free();
    elements = newdata.first;
    first_free = newdata.second;
    return *this;
}

void StrVec::reallocate()
{
    auto newcapacity = size()? 2 * size() : 1; //分配当前大小两倍的内存空间
    auto newdata = alloc.allocate(newcapacity); //分配新内存
    auto dest = newdata; //指向新数组中的下一个空闲位置
    auto elem = elements; //指向旧数组中下一个元素
    for(size_t i = 0; i != size(); i++)
        alloc.construct(dest++,std::move(*elem++)); //调用move表示希望使用string的移动构造函数
    free(); // 一旦我们移动完元素就释放旧内存空间
    elements = newdata;
    first_free = dest;
    cap = = elements + newcapacity;
}

void StrVec::reserve(size_t n)
{
    
    if( n < capacity())
        return;
    auto newdata = alloc.allocate(n); //分配新内存
    auto dest = newdata; //指向新数组中的下一个空闲位置
    auto elem = elements; //指向旧数组中下一个元素
    for(size_t i = 0; i != size(); i++)
        alloc.construct(dest++,std::move(*elem++)); //调用move表示希望使用string的移动构造函数
    free(); // 一旦我们移动完元素就释放旧内存空间
    elements = newdata;
    first_free = dest;
    cap = = elements + n;
}

void StrVec::resize(size_t n ,  const string &s)
{
    if(n < size())
    {
        while(n < size())
            alloc.destroy(--first_free);
    }
    else if (n > size())
    {
        while(n > size())
            push_back(s);
    }
}

void StrVec::resize(size_t n)
{
    resize(n,string());
}