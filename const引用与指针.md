# const的引用与指针

## 知识点：
1.不允许一个非常量引用指向一个常量对象。
```c++
const int ci = 1024;
int &r = ci;//错误
```
2.允许const int& 绑定到一个普通int对象上。
```c++
int i = 42;
const int &r = i; //√
r = 52; //× 不能用常量引用改变值
i = 52; //√
```
3.指向常量的指针：不能改变其所指对象的值(同时满足1，2点)。
Tip:所谓指向常量的指针/引用，不过是指针/引用“自以为是”，他们觉得自己指向了常量，所以自觉的不去改变所指向对象的值，但可以通过其他方法改变哪个对象的值。（如2中所示）

4.const指针（常量指针）————必须初始化：不变的是指针本身的值，而非指向的值
```c++
int i = 0;
int *const p = &i;//p将一直指向i
i = 5; //√
p = &t;//×

const double *const pip = &p; //指向常量对象的常量指针
```
## 顶层const 和 底层const：

1.顶层const：指针本身是个常量

2.地层const：指针所指的对象是一个常量。
```c++
int i = 0;
int *const p1 = &i;//p1值不能改变（顶层const）
const int ci = 42; //ci值不能改变（顶层const)
const int *p2 = &ci;//p2可变，其所指对象的值不可改变(底层const)
const int *const p3 = p2;//第一个const为底层const，第二个为顶层const
const int &r = ci;//用于声明引用的const都是底层const
```
Tip:拷贝时，顶层const不受影响，但拷入、拷出的对象必须具有相同的底层const资格，或者两个对象的数据类型能够转换（非常量可转换成常量，反之不行）。
```c++
p2 = &i;// √（i:int & , p2:const int *）
t = ci;// ×（t:int &, ci: const int)
```