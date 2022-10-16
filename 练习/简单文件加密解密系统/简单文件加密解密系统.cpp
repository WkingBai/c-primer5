#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

//��ȡ�����ļ����� 
string Read_data(const string& path)
{
	ifstream fin;
	fin.open(path, ios::binary);
	if (!fin.is_open()) {
		cout << " �޷��򿪸��ļ���" << endl;
		exit(0);
	}
	char ch;
	string data;
	while (fin.get(ch)) {   //get()���������԰�ɫ�ո��ַ����ո��Ʊ��������з��� 
		data.push_back(ch);
	}
	fin.close();
	return data;
}

//��ȡ���ж��뱾�ļ����� 
vector<string> JudgeAndRead_code(const string& path, bool& flag)
{
	ifstream fin;
	vector<string> code;
	fin.open(path, ios::binary);
	if (!fin.is_open()) {
		cout << " �޷����ļ���" << endl;
		exit(0);
	}

	string buff;
	while (fin >> buff) {  // fin >> ��ʽ�Ķ�ȡ������κΰ�ɫ�ո��ַ� 
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

// 26 ��ĸ�뱾�ı������
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

// 256 �������뱾�ı������
void encrypt_num(const string& data, const vector<string>& code, ofstream& out)
{
	string res;
	for (unsigned char ch : data) { 
		int num = ch;
		char c = stoi(code[num]); //stoi���ַ���ת��Ϊint������ 
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
		vector<string>::iterator iter = find(code.begin(), code.end(), str); //��code�в���strλ�ã�����Ϊ���������� 
		char c = iter - code.begin();  
		res.push_back(c);
	}
	cout << res.size() << "):" << '\n' << res << endl; 
	out << res;
}


int main(int argc, char* argv[])
{
	bool flag = 0; //�뱾��־��(26����ĸ��0�� 256�����֣�1�� 
	vector<string> code = JudgeAndRead_code(argv[2], flag); //�жϲ���ȡ�뱾�ļ����� 
	cout << argv[2] << " ����(" << code.size() << "):" << endl;  
	for(auto c : code){	//��ʾ�뱾�ļ����� 
		cout << c <<' ';		
	}
	cout <<"\n\n\n";
	
	string data = Read_data(argv[3]);  //��ȡ�����ļ����� 
	cout << argv[3] << " ����(" << data.size() << "):" << endl;
	cout << data << "\n\n\n";
	
	ofstream out_data(argv[4], ios::binary); //����ļ��� 
	cout << argv[4] << " ����(";
	string opt = argv[1];
	if (opt == "encrypt"){  
		if(flag == 0){  //�뱾Ϊ26����ĸ 
			encrypt(data, code[0], out_data);  //����
		}
		else{
			encrypt_num(data, code, out_data); //���� 
		}
	}
	else if (opt == "decrypt"){
		if(flag == 0){ //�뱾Ϊ256������ 
			decrypt(data, code[0], out_data);
		}
		else{
			decrypt_num(data, code, out_data);
		}
	}
	else
		cout << argv[1] << "�޷�ʶ��\n�ļ�����������:encrypt,�ļ�����������:decrypt" << endl;
	return 0;
}
