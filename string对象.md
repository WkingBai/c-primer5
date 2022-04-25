# string对象

### 1.定义和初始化string对象

1.string s1;    $\qquad $//默认初始化，s1是一个空串

2.string s2(s1);$\qquad $//s2是s1的副本

3.string s3("value");$\qquad $//s3是字面值"value"的副本，除了字面值最后的那个空字符外

4.string s3 = "value"; $\qquad $ //等价于3

5.string s4(n,'c');   $\qquad $  //把s4初始化为由连续n个字符c组成的串

  
tip:如果使用符号（=）初始化一个变量，实际上执行是==拷贝初始化==，反正如果不使用则是==直接初始化==。

### 2.string对象上的操作

1. os << s;$\qquad $//将s写到输出流os当中，返回os
2. is >> s;$\qquad $//从is中读取字符串赋值给s，字符串以空白分隔，返回is
3. getline(is,s);$\qquad $//从is中读取一行赋给s，返回is
4. s.empty();$\qquad $//s为空返回true，否则返回false
5. s[N];$\qquad $//返回s中字符的个数
6. s1 + s2;$\qquad $//返回s1 和 s2 连接后的结果
7. s1 = s2;$\qquad $//用s2的副本代替s1中原来的字符
8. s1 == s2;$\qquad $//如果s1 和 s2 中所含的字符完全一致，则它们相等。（对大小写敏感）
9. s1 ！= s2；
10. <, <=, >, >= $\qquad $//利用字符在字典中的顺序进行比较，且对字母的大小写敏感

### 3.处理string对象中的字符
|函数 | 作用 |
| :----: | ---- |
| <div style="width: 150pt">isalnum(c);|当c是字母或数字时为真|
|isalpha(c);|当c是字母时为真|
|iscntrl(c);|当c是控制字符时为真|
|isdigit(c);|当c是数字时为真|
|isgraph(c);|当c不是空格但是可以打印时为真|
|islower(c);|当c是小写字母时为真|
|isprint(c);|当c是可打印字符时为真|
|ispunct(c);|当c是标点符号时为真|
|isspace(c);|当c是空白时为真|
|isupper(c);|当c是大写字母时为真|
|isxdigit(c);|当c是十六进制数字时为真|
|tolower(c);|如果c是大写字母，输出对应的小写字母|
|toupper(c);|如果c是小写字母，输出对应的大写字母|

### 4.构造string的其他方法
|函数 | 作用 |
| :----: | ---- |
|stirng s(cp,n);|s是cp指向的数组中前n个字符的拷贝，此数组至少应该包含n个字符|
|string s(s2,pos2);|s是stirng s2从下标pos2开始的字符的拷贝。若pos2 > s2.size(),构造函数的行为未定义。|
| <div style="width: 150pt">string s(s2,pos2,len2);|s是string s2从下标pos2开始len2个字符的拷贝，pos2 > s2.size()，构造函数的行为未定义。至多拷贝s2.size() - pos2个字符|

### 5.修改string的操作
|函数 | 作用 |
| :----: |---- |
| <div style="width: 150pt">s.insert(pos,args);|在pos之前插入args指定的字符。pos可以是一个下表或一个迭代器。下标：返回一个指向s的引用。 迭代器：返回指向第一个插入字符的迭代器|
|s.erase(pos,len);|删除从pos开始的len个字符。如果len被省略，则删除pos到末尾的所有字符，返回一个指向s的引用|
|s.assign(args);|将s中的字符替换为args指定的字符。返回一个指向s的引用|
|s.append(args);|将args追加到s。返回一个指向s的引用|
|s.replace(range,args);|删除s中范围range内的字符，替换为args指定的字符。range：下标+长度/一对迭代器。返回一个指向s的引用|

### 6.string搜索操作
|函数|作用|
| :----:|----|
|<div style="width: 150pt">s.find(args);|查找s中args第一次出现的位置|
|s.rfind(args);|查找s中args最后一次出现的位置|
|s.find_first_of(args);|在s中查找args中任何一个字符第一次出现的位置|
|s.find_last_of(args);|在s中查找args中任何一个字符最后一次出现的位置|
|s.find_first_not_of(args);|在s中查找第一个不在args中的字符|
|s.find_last_not_of(args);|在s中查找最后一个不在args中的字符|

### 7.string和数值之间的转换
|函数|作用|
| :----:|----|
|<div style="width:150pt">to_string(val);|返回数值val的string表示。val可以是任何算术类型|
|stoi(s,p,b);<td rowspan="5">返回s的起始子串（表示整数内容）的数值，返回类型分别是int、long、unsigned long、long long、unsig long long。b表示转换所用的基数，默认值为10.p是size_t指针，用来保存s中第一个非数值字符的下标，p默认为0，即，函数不保存下标。</td>
|stol(s,p,b);
|stoul(s,p,b);
|stoll(s,p,b);
|stoull(s,p,b);
|stof(s,p);<td rowspan="3">返回s的起始子串（表示浮点数内容）的数值，返回值类型分别是float，double或long long double。参数p的作用与整数转换函数中一样.</td>
|stod(s,p);
|stold(s,p);

### 8.compare函数的几种参数形式
|参数|作用|
| :----:|----|
|<div style="width:150pt">s2|比较s和s2|
|pos1，n1，s2|将s中从pos1开始的n1个字符与s2进行比较|
|pos1，n1，s2，pos2，n2|将s中从pos1开始的n1个字符与s2中从pos2开始的n2个字符进行比较|
|cp|比较s与cp指向的以空字符结尾的字符数组|
|pos1，n1，cp|将s中从pos1开始的n1个字符与cp指向的以空字符结尾的字符数组进行比较|
|pos1,n1,cp,n2|将s中从pos1开始的n1个字符与指针cp指向的地址开始的n2个字符进行比较|
