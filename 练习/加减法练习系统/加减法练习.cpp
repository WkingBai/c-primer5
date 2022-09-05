#include<iostream>
#include<cstdlib>
#include<chrono>
#include<vector>
#include<string>
#include<cmath>

int n, num = 0;  //n:��Ŀ���� ��  num:�����Ŀ����
bool flag; // flag = 1 : �г˳����� flag = 0 : �޳˳���
int n_min = 1, n_max = 100;  // ���ⷶΧ�� n_min ~ n_max ֮��(Ĭ�Ϸ�ΧΪ1~100��
std::vector<std::string> errlog; // ��¼����
std::vector<double> error_ans, ack; // �ֱ��¼����ش𼰶�����ȷ��
std::vector<double> times; //��¼ÿ�����ʱ��

void Input_bool( bool& m) 
{
	while (!(std::cin >> m)) //�������
	{
		std::cin.clear(); // ��������־
		std::cin.ignore(1024, '\n');// ��������������س��������س���֮ǰ������ȫ�����
		std::cout << "���� 0 �� 1�����������룺";
	};
	std::cin.ignore(1024,'\n');
}

void Input_int( int& m)
{
	while (!(std::cin >> m))
	{
		std::cin.clear();
		std::cin.ignore(1024, '\n');
		std::cout << "�˴��������Ϊһ�����������������룺";
	};
	std::cin.ignore(1024,'\n');
}

void Input_value(double& m, int oper)
{
	if (oper == 4) {
		while (!(std::cin >> m))
		{
			std::cin.clear();
			std::cin.ignore(1024, '\n');
			std::cout << "�˴��������Ϊһ������/�����������������루�����������벢������λС������";
		};
		m = round(m * 100) / 100;
	}
	else {
		int temp;
		Input_int(temp);
		m = static_cast<double>(temp);
	}
}

//����ǰ�ļ򵥽���
void Info() 
{
	std::cout << "\t\t\t\t��ӭ����Wkingbai�ļӼ�����ϰϵͳ\n\n" << "����������ϣ���Ĵ�����Ŀ��";
	Input_int(n);
	std::cout << "\n��ϵͳĬ�����㷶ΧΪ1~100�Ƿ���Ҫ�������ã�1����Ҫ��0������Ҫ����";
	bool r;
	Input_bool(r);
	if (r) {
		std::cout << "��������Сȡֵ��";
		Input_int(n_min);
		std::cout << "���������ȡֵ��";
		Input_int(n_max);
	}
	std::cout << "\n��ϣ��������Ŀ�а����˳����𣿣�yes �����룺1�� no �����룺0 )    ��";
	Input_bool(flag);
	if (flag)
		std::cout << "\n�������������ٱ�����λС�����������룩";
	std::cout << "\n\n\t���δ��⹲100�֣�ÿ���Ե�" << 100.0 / n << "�֣�����÷�\n\n";
}

//���⼰����
void Questions_ans() 
{
	 // res: ��ȷ��  ��  ans : ѧ���ش�  �� oper : �������ͣ�1���ӣ�2������3���ˣ�4������
	double  res, ans;
	int oper; 
	srand(time(NULL));
	for (int i = 0; i < n; ++i) {
		std::string log; // ��¼������Ŀ
		std::cout << "��" << i + 1 << "���⣺";
		oper = flag ? rand() % 4 + 1 : rand() % 2 + 1;
		int a = rand() % (n_max - n_min + 1) + n_min;
		int b = rand() % (n_max - n_min + 1) + n_min;
		switch (oper) {
		case 1: {
			res = a + b;
			log = std::to_string(a) + "+" + std::to_string(b) + "=";
		}
			  break;
		case 2: {
			res = a - b;
			log = std::to_string(a) + "-" + std::to_string(b) + "=";
		}
			  break;
		case 3: {
			res = a * b;
			log = std::to_string(a) + "*" + std::to_string(b) + "=";
		}
			  break;
		case 4: {
			res = a / (b * 1.0);
			res = round(res * 100) / 100;
			log = std::to_string(a) + "/" + std::to_string(b) + "=";
		}
			  break;

		}
		std::cout << log << std::endl;  //���������Ŀ
		const auto start = std::chrono::steady_clock::now(); //��ʼ��ʱ
		Input_value(ans,oper);
		const auto end = std::chrono::steady_clock::now();//������ʱ
		auto endtime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0; // �������ʱ��
		times.push_back(endtime);
		if (ans == res)
			++num;
		else {
			errlog.push_back(log);
			error_ans.push_back(ans);
			ack.push_back(res);
		}
		std::cout << '\n';
	}
}

//�÷��������
void result() 
{
	double min_s = DBL_MAX, avg_s = 0;  //���������ʱ �� ƽ����ʱ
	for (int i = 0; i < times.size(); ++i)
	{
		if (min_s > times[i])
			min_s = times[i];
		avg_s += times[i] / times.size();
	}
	std::cout << "���δ��⹲�����Ŀ" << num << "��," << "���" << n - num << "����";
	std::cout << "����ƽ����ʱΪ��" << avg_s << "�룬" << "�����ʱΪ��" << min_s << "�롣";
	std::cout << "�����յ÷�Ϊ" << (100.0 / n) * num << std::endl;

	if (num == n)
		std::cout << "\n\n\t\t��ϲ��ȫ������ˣ����Ǹ�����أ�\n\n" << std::endl;
	else {
		std::cout << "\n�����Ŀ����ȷ�����£�\n\n";
		for (int i = 0; i < errlog.size(); ++i) {
			std::cout << errlog[i] << '\n';
			std::cout << "��Ĵ�Ϊ��" << error_ans[i] << '\n';
			std::cout << "��ȷ��Ϊ��" << ack[i] << '\n';
			std::cout << std::endl;
		}
	}
}

int main()
{
	Info();  //ϵͳ����������һЩ��������
	std::cout << "\n\n\t\t\t\t���⿪ʼ\n\n";
	Questions_ans(); // ���⼰���
	std::cout << "\n\n\t\t\t\t�������\n\n";
	result(); // �÷��������
	return 0;
}
