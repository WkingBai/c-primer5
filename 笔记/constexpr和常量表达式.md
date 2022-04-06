# constexpr 和 常量表达式

1.常量表达式：值不会改变并且在编译过程就能得到计算结果的表达式。
```c++
const int i = 20; //√
int i = 20;// 值会改变（非常量表达式)
const int s2 = get_size();// get_size()直到运行时才能获得（非常量表达式）
```
2.constexpr变量
允许将变量声明为constexpr类型以便由编译器来验证变量的值是否是一个常量表达式。
==（声明为constexpr的变量一定是一个常量，且必须用常量初始化）==
```c++
constexpr int mf = 20; //√
constexpr int s2 = size();//当size是constexpr函数时才正确
```
3.指针和constexpr
constexpr声明中定义一个指针，限定符constexpr仅对指针有效，与指针所指的对象无关。
==constexpr把它所定义的对象置为了顶层const==
```c++
const int *p = nullptr;//指向整数常量的指针
const int *q = nullptr;//指向整数的常量指针
```
与其他常量指针类似，constexpr指针既可以指向常量也可以指向一个非常量
==非常量可转化为常量（隐式）==
```c++
int j = 0;
constexpr int i = 42;
constexpr const int *p = &i;//p是常量指针，指向整型常量i
constexpr int *p1 = &j;//p1是常量指针，指向整数j
```



