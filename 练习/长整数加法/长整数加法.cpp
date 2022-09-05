#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<stdlib.h>
#include<algorithm>

using namespace std;

// ��ȡ�ļ�input.txt������
vector<string> Read_txt(const string& path)
{
	ifstream fin;
	vector<string> data;
	fin.open(path, ios::in);
	if (!fin.is_open()) {
		cout << " �޷��򿪸��ļ���" << endl;
		exit(0);
	}

	string buff;
	while (getline(fin, buff)) {
		data.push_back(buff);
	}
	fin.close();
	return data;
}

//ɾ������������ǰ�ķ��ź���Ч�㣬���������������е�������
string JudgeAndDel_sym(string& str1, string& str2) {
	string dsym;
	if ((str1[0] == '-') && (str2[0] == '-')) {
		dsym = "--";
		str1.erase(0, 1); //ɾ���ַ���1ǰ�� '-' ��
		str2.erase(0, 1); //ɾ���ַ���1ǰ�� '-' ��
		while (str1[0] == '0') //ɾ����Ч����ǰ��0
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



//���������з�����ͬ�ļӷ�����
string add_same_sym(const string& str1, const string& str2) {
	if (str1.empty() && str2.empty())
		return "0";
	if (str1.empty())
		return str2;
	if (str2.empty())
		return str1;
	int n1 = str1.size() - 1;
	int n2 = str2.size() - 1;
	int cf = 0;  //��λ��־λ
	string ret;  //������
	while (n1 >= 0 || n2 >= 0) {
		int num1 = 0; //�����ַ���1�еĵ�������
		int num2 = 0; //�����ַ���2�еĵ�������
		if (n1 >= 0)
			num1 = str1[n1--] - '0';
		if (n2 >= 0)
			num2 = str2[n2--] - '0';
		int sum = num1 + num2 + cf;
		cf = sum / 10;
		sum %= 10;
		ret.push_back(sum + '0');
	}
	if (cf > 0)  // ���һ���Ƿ��н�λ
		ret.push_back('1');
	reverse(ret.begin(), ret.end());  //��ת�ַ���
	return ret;
}

//���������з�������ļӷ����㣨ʵ�����ü����� 
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
		int num1 = 0; //�����ַ���1�еĵ�������
		int num2 = 0; //�����ַ���2�еĵ�������
		if (n1 >= 0)
			num1 = str1[n1--] - '0';
		if (n2 >= 0)
			num2 = str2[n2--] - '0';
		int sum = num1 - num2 - cf;
		if (sum < 0) {  // ��Ҫ��λ����λ��
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



//char ת int 
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
		num = 37;  // radix���Ϊ36������36���ϵ����ֶ�Ϊ���Ϸ����� 
	return num;
}


//int ת char
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

//�����������argv[2]��argv[3])����Ч�Լ�� 
int check_base(const string& base) {
	if (base.size() > 1) {
		cout << "���������" << base << " ���Ϸ��� { ������2~9 �� a~z����ʾ 10~35 ���ƣ� �� 0 (��ʾ 36 ����) }" << endl;
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
		cout << "��������� " << base << " ���Ϸ���{ ������2~9 �� a~z����ʾ 10~35 ���ƣ� �� 0 (��ʾ 36 ����) }" << endl;
		exit(0);
	}
	return radix;
}

//��������������еĺϷ���
void check_data(const string& str1, const string& str2, int radix) {
	for (auto c : str1) {
		int num = Atoi(c);
		if (num >= radix) {
			cout << "��һ�����������к��е��ַ� " << c << " �� " << radix << " �����в���һ����Ч���֡�" << endl;
			exit(0);
		}
	}
	for (auto c : str2) {
		int num = Atoi(c);
		if (num >= radix) {
			cout << "�ڶ������������к��е��ַ� " << c << " �� " << radix << " �����в���һ����Ч���֡�" << endl;
			exit(0);
		}
	}
	return;
}



// ʵ���ַ������������еĳ˷�����
string multiply(string ret, int radix) {
	int cf = 0; //�����λ
	for (int i = ret.size() - 1; i >= 0; i--) {
		int current = radix * (ret[i] - '0') + cf;
		ret[i] = current % 10 + '0';
		cf = current / 10;
	}
	if (cf != 0)
		ret = to_string(cf) + ret;
	return ret;
}

// ʵ���ַ������������еļӷ�����
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

// ��������תʮ����
string BasetoTen_conversion(const string& str, int radix) {
	string ret = "0";
	for (int i = 0; i < str.size(); ++i) {
		ret = Addt(multiply(ret, radix), Atoi(str[i]));
	}
	return ret;
}



//ʵ���ַ������������еĳ�������
string Divide(string str, int obj_radix, string& ret)//����
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

//ʮ����ת��������
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
	vector<string> data = Read_txt(argv[1]); //��ȡ�ļ����� 
	int radix = argc >= 3 ? check_base(argv[2]) : 10; //��������ļ����������кϷ��Լ��
	int obj_radix = argc == 4 ? check_base(argv[3]) : radix;  //������Ľ��������кϷ��Լ��
	cout << "�ļ����ݣ�" << endl;
	for (auto a : data)
		cout << a << endl;
	cout << "ʮ������ӽ����" << endl;
	string ret = Str_add(data[0], data[1], radix); // ʵ���ı�����������������ӣ�ʮ���ƣ�
	cout << ret << endl;
	cout << "\nԤ��" << obj_radix << "���ƽ����" << endl;
	string obj_ret = TentoBase_conversion(ret, obj_radix);  //��ʮ���ƽ��ת��Ϊ��Ҫ��Ľ��ƶ�Ӧ�Ľ��
	cout << obj_ret << endl;
	return 0;

}