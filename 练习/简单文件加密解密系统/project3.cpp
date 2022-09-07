#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

//读取输入文件数据 
string Read_data(const string& path)
{
	ifstream fin;
	fin.open(path, ios::binary);
	if (!fin.is_open()) {
		cout << " 无法打开该文件！" << endl;
		exit(0);
	}
	char ch;
	string data;
	while (fin.get(ch)) {   //get()函数不忽略白色空格字符（空格、制表符、换行符） 
		data.push_back(ch);
	}
	fin.close();
	return data;
}

//读取并判断码本文件数据 
vector<string> JudgeAndRead_code(const string& path, bool& flag)
{
	ifstream fin;
	vector<string> code;
	fin.open(path, ios::binary);
	if (!fin.is_open()) {
		cout << " 无法打开文件！" << endl;
		exit(0);
	}

	string buff;
	while (fin >> buff) {  // fin >> 形式的读取会忽略任何白色空格字符 
		code.push_back(buff);
	}
	for(char ch : code[0]){
		if(isdigit(ch)){
			flag = 1;
			break;	
		}
	}
	fin.close();
	return code;
}

// 26 字母码本的编码解码
void encrypt(const string& data, const string& code, ofstream& out) 
{
	string res;
	for (auto ch : data) {
		if (ch >= 'a' && ch <= 'z') {
			int num = ch - 'a';
			res.push_back(code[num]);
		}
		else if (ch >= 'A' && ch <= 'Z') {
			int num = ch - 'A';
			res.push_back(toupper(code[num]));
		}
		else
			res.push_back(ch);
	}
	cout << res.size() << "):" << '\n' << res << endl; 
	out << res;
}

void decrypt(const string& data, const string& code, ofstream& out) {
	string res;
	for (auto ch : data) {
		if (ch >= 'a' && ch <= 'z') {
			int pos = code.find(ch);
			char c = 'a' + pos;
			res.push_back(c);
		}
		else if (ch >= 'A' && ch <= 'Z') {
			int pos = code.find(tolower(ch));
			char c = 'A' + pos;
			res.push_back(c);
		}
		else
			res.push_back(ch);
	}
	cout << res.size() << "):" << '\n' << res << endl; 
	out << res;
}

// 256 个数字码本的编码解码
void encrypt_num(const string& data, const vector<string>& code, ofstream& out)
{
	string res;
	for (unsigned char ch : data) { 
		int num = ch;
		char c = stoi(code[num]); //stoi将字符串转化为int型数字 
		res.push_back(c);
	}
	cout << res.size() << "):" << '\n' << res << endl;  
	out << res;
}

void decrypt_num(const string& data, vector<string>& code, ofstream& out)
{
	string res;
	for (unsigned char ch : data) {
		int num = ch;
		string str = to_string(num);
		vector<string>::iterator iter = find(code.begin(), code.end(), str); //在code中查找str位置，返回为迭代器类型 
		char c = iter - code.begin();  
		res.push_back(c);
	}
	cout << res.size() << "):" << '\n' << res << endl; 
	out << res;
}


int main(int argc, char* argv[])
{
	bool flag = 0; //码本标志符(26个字母：0， 256个数字：1） 
	vector<string> code = JudgeAndRead_code(argv[2], flag); //判断并读取码本文件数据 
	cout << argv[2] << " 内容(" << code.size() << "):" << endl;  
	for(auto c : code){	//显示码本文件内容 
		cout << c <<' ';		
	}
	cout <<"\n\n\n";
	
	string data = Read_data(argv[3]);  //读取输入文件数据 
	cout << argv[3] << " 内容(" << data.size() << "):" << endl;
	cout << data << "\n\n\n";
	
	ofstream out_data(argv[4], ios::binary); //输出文件流 
	cout << argv[4] << " 内容(";
	string opt = argv[1];
	if (opt == "encrypt"){  
		if(flag == 0){  //码本为26个字母 
			encrypt(data, code[0], out_data);  //编码
		}
		else{
			encrypt_num(data, code, out_data); //解码 
		}
	}
	else if (opt == "decrypt"){
		if(flag == 0){ //码本为256个数字 
			decrypt(data, code[0], out_data);
		}
		else{
			decrypt_num(data, code, out_data);
		}
	}
	else
		cout << argv[1] << "无法识别\n文件编码请输入:encrypt,文件解码请输入:decrypt" << endl;
	return 0;
}
