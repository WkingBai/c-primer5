#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<stdlib.h>
#include<algorithm>

using namespace std;

// 读取文件input.txt中数据
vector<string> Read_txt(const string& path)
{
	ifstream fin;
	vector<string> data;
	fin.open(path, ios::in);
	if (!fin.is_open()) {
		cout << " 无法打开该文件！" << endl;
		exit(0);
	}

	string buff;
	while (getline(fin, buff)) {
		data.push_back(buff);
	}
	fin.close();
	return data;
}

//删除其数字序列前的符号和无效零，返回两行数字序列的正负。
string JudgeAndDel_sym(string& str1, string& str2) {
	string dsym;
	if ((str1[0] == '-') && (str2[0] == '-')) {
		dsym = "--";
		str1.erase(0, 1); //删除字符串1前的 '-' 号
		str2.erase(0, 1); //删除字符串1前的 '-' 号
		while (str1[0] == '0') //删除有效数字前的0
			str1.erase(0, 1);
		while (str2[0] == '0')
			str2.erase(0, 1);

	}
	else if ((str1[0] == '-') && (str2[0] != '-')) {
		dsym = "-+";
		str1.erase(0, 1);
		if (str2[0] == '+')
			str2.erase(0, 1);
		while (str1[0] == '0')
			str1.erase(0, 1);
		while (str2[0] == '0')
			str2.erase(0, 1);
	}
	else if ((str1[0] != '-') && (str2[0] == '-')) {
		dsym = "+-";
		str2.erase(0, 1);
		if (str1[0] == '+')
			str1.erase(0, 1);
		while (str1[0] == '0')
			str1.erase(0, 1);
		while (str2[0] == '0')
			str2.erase(0, 1);
	}
	else {
		dsym = "++";
		if (str1[0] == '+')
			str1.erase(0, 1);
		if (str2[0] == '+')
			str2.erase(0, 1);
		while (str1[0] == '0')
			str1.erase(0, 1);
		while (str2[0] == '0')
			str2.erase(0, 1);
	}
	return dsym;
}



//两数字序列符号相同的加法运算
string add_same_sym(const string& str1, const string& str2) {
	if (str1.empty() && str2.empty())
		return "0";
	if (str1.empty())
		return str2;
	if (str2.empty())
		return str1;
	int n1 = str1.size() - 1;
	int n2 = str2.size() - 1;
	int cf = 0;  //进位标志位
	string ret;  //运算结果
	while (n1 >= 0 || n2 >= 0) {
		int num1 = 0; //保存字符串1中的单个数字
		int num2 = 0; //保存字符串2中的单个数字
		if (n1 >= 0)
			num1 = str1[n1--] - '0';
		if (n2 >= 0)
			num2 = str2[n2--] - '0';
		int sum = num1 + num2 + cf;
		cf = sum / 10;
		sum %= 10;
		ret.push_back(sum + '0');
	}
	if (cf > 0)  // 最后一次是否有进位
		ret.push_back('1');
	reverse(ret.begin(), ret.end());  //翻转字符串
	return ret;
}

//两数字序列符号相异的加法运算（实则运用减法） 
string add_diff_sym(const string& str1, const string& str2) {
	if (str1.empty() && str2.empty())
		return "0";
	if (str1.empty())
		return str2;
	if (str2.empty())
		return str1;
	int n1 = str1.size() - 1;
	int n2 = str2.size() - 1;
	int cf = 0;
	string ret;
	while (n1 >= 0 || n2 >= 0) {
		int num1 = 0; //保存字符串1中的单个数字
		int num2 = 0; //保存字符串2中的单个数字
		if (n1 >= 0)
			num1 = str1[n1--] - '0';
		if (n2 >= 0)
			num2 = str2[n2--] - '0';
		int sum = num1 - num2 - cf;
		if (sum < 0) {  // 需要进位（借位）
			cf = 1;
			sum += 10;
		}
		else
			cf = 0;
		ret.push_back(sum + '0');
	}
	reverse(ret.begin(), ret.end());
	return ret;
}



//char 转 int 
int Atoi(char c)
{
	int num = 0;
	if (c >= '0' && c <= '9') {
		num = c - '0';
	}
	else if (c >= 'a' && c <= 'z') {
		num = 10 + (c - 'a');
	}
	else if (c >= 'A' && c <= 'Z') {
		num = 10 + (c - 'A');
	}
	else
		num = 37;  // radix最大为36，所以36以上的数字都为不合法数字 
	return num;
}


//int 转 char
char Itoa(int num)
{
	char c = 0;
	if (num >= 0 && num <= 9) {
		c = num + '0';
	}
	if (num >= 10 && num <= 35) {
		c = (num - 10) + 'a';
	}
	return c;
}

//输入进制数（argv[2]、argv[3])的有效性检查 
int check_base(const string& base) {
	if (base.size() > 1) {
		cout << "输入进制数" << base << " 不合法。 { 请输入2~9 或 a~z（表示 10~35 进制） 或 0 (表示 36 进制) }" << endl;
		exit(0);
	}
	int radix = 0;
	if (base[0] == '0')
		radix = 36;
	else if (base[0] >= '2' && base[0] <= '9') {
		radix = base[0] - '0';
	}
	else if (base[0] >= 'a' && base[0] <= 'z') {
		radix = 10 + (base[0] - 'a');
	}
	else if (base[0] >= 'A' && base[0] <= 'Z') {
		radix = 10 + (base[0] - 'A');
	}
	else {
		cout << "输入进制数 " << base << " 不合法。{ 请输入2~9 或 a~z（表示 10~35 进制） 或 0 (表示 36 进制) }" << endl;
		exit(0);
	}
	return radix;
}

//检查两个数字序列的合法性
void check_data(const string& str1, const string& str2, int radix) {
	for (auto c : str1) {
		int num = Atoi(c);
		if (num >= radix) {
			cout << "第一行数字序列中含有的字符 " << c << " 在 " << radix << " 进制中不是一个有效数字。" << endl;
			exit(0);
		}
	}
	for (auto c : str2) {
		int num = Atoi(c);
		if (num >= radix) {
			cout << "第二行数字序列中含有的字符 " << c << " 在 " << radix << " 进制中不是一个有效数字。" << endl;
			exit(0);
		}
	}
	return;
}



// 实现字符串中数字序列的乘法运算
string multiply(string ret, int radix) {
	int cf = 0; //保存进位
	for (int i = ret.size() - 1; i >= 0; i--) {
		int current = radix * (ret[i] - '0') + cf;
		ret[i] = current % 10 + '0';
		cf = current / 10;
	}
	if (cf != 0)
		ret = to_string(cf) + ret;
	return ret;
}

// 实现字符串中数字序列的加法运算
string Addt(string str, int x)
{
	int cf = x;
	for (int i = str.size() - 1; i >= 0; i--)
	{
		int current = (str[i] - '0') + cf;
		str[i] = current % 10 + '0';
		cf = current / 10;
	}
	if (cf != 0)
	{
		str = to_string(cf) + str;
	}
	return str;
}

// 其他进制转十进制
string BasetoTen_conversion(const string& str, int radix) {
	string ret = "0";
	for (int i = 0; i < str.size(); ++i) {
		ret = Addt(multiply(ret, radix), Atoi(str[i]));
	}
	return ret;
}



//实现字符串中数字序列的除法运算
string Divide(string str, int obj_radix, string& ret)//除法
{
	int remain = 0;
	for (int i = 0; i < str.size(); i++)
	{
		int current = remain * 10 + str[i] - '0';
		str[i] = current / obj_radix + '0';
		remain = current % obj_radix;
	}
	int pos = 0;
	ret.push_back(Itoa(remain));
	while (str[pos] == '0')
	{
		pos++;
	}
	return str.substr(pos);
}

//十进制转其他进制
string TentoBase_conversion(string str, int obj_radix) {
	if (obj_radix == 10)
		return str;
	string ret = "";
	string flag = "";
	if (str[0] == '-') {
		str.erase(0, 1);
		flag = "-";
	}
	while (str.size() != 0) {
		str = Divide(str, obj_radix, ret);
	}
	reverse(ret.begin(), ret.end());
	return flag + ret;
}

string Str_add(string& str1, string& str2, int radix) {
	string dsym = JudgeAndDel_sym(str1, str2);
	check_data(str1, str2, radix);
	if (radix != 10) {
		str1 = BasetoTen_conversion(str1, radix);
		str2 = BasetoTen_conversion(str2, radix);
	}
	if (dsym == "--") {
		string ret = add_same_sym(str1, str2);
		return '-' + ret;
	}
	else if (dsym == "-+") {
		if (str1.size() > str2.size()) {
			string ret = add_diff_sym(str1, str2);
			while (ret[0] == '0' && ret.size() > 1)
				ret.erase(0, 1);
			return '-' + ret;
		}
		else if (str1.size() < str2.size()) {
			string ret = add_diff_sym(str2, str1);
			while (ret[0] == '0' && ret.size() > 1)
				ret.erase(0, 1);
			return ret;
		}
		else {
			if (str1 > str2) {
				string ret = add_diff_sym(str1, str2);
				while (ret[0] == '0' && ret.size() > 1)
					ret.erase(0, 1);
				return '-' + ret;
			}
			else {
				string ret = add_diff_sym(str2, str1);
				while (ret[0] == '0' && ret.size() > 1)
					ret.erase(0, 1);
				return ret;
			}
		}

	}

	else if (dsym == "+-") {
		if (str2.size() > str1.size()) {
			string ret = add_diff_sym(str2, str1);
			while (ret[0] == '0' && ret.size() > 1)
				ret.erase(0, 1);
			return '-' + ret;
		}
		else if (str2.size() < str1.size()) {
			string ret = add_diff_sym(str1, str2);
			while (ret[0] == '0' && ret.size() > 1)
				ret.erase(0, 1);
			return ret;
		}
		else {
			if (str2 > str1) {
				string ret = add_diff_sym(str2, str1);
				while (ret[0] == '0' && ret.size() > 1)
					ret.erase(0, 1);
				return '-' + ret;
			}
			else {
				string ret = add_diff_sym(str1, str2);
				while (ret[0] == '0' && ret.size() > 1)
					ret.erase(0, 1);
				return ret;
			}
		}

	}
	else {
		string ret = add_same_sym(str1, str2);
		return ret;
	}
}
int main(int argc, char* argv[])
{
	vector<string> data = Read_txt(argv[1]); //读取文件数据 
	int radix = argc >= 3 ? check_base(argv[2]) : 10; //对输入的文件进制数进行合法性检测
	int obj_radix = argc == 4 ? check_base(argv[3]) : radix;  //对输出的进制数进行合法性检测
	cout << "文件内容：" << endl;
	for (auto a : data)
		cout << a << endl;
	cout << "十进制相加结果：" << endl;
	string ret = Str_add(data[0], data[1], radix); // 实现文本的两个数字序列相加（十进制）
	cout << ret << endl;
	cout << "\n预期" << obj_radix << "进制结果：" << endl;
	string obj_ret = TentoBase_conversion(ret, obj_radix);  //将十进制结果转换为所要求的进制对应的结果
	cout << obj_ret << endl;
	return 0;

}