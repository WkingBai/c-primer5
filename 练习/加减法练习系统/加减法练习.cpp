#include<iostream>
#include<cstdlib>
#include<chrono>
#include<vector>
#include<string>
#include<cmath>

int n, num = 0;  //n:题目总数 ；  num:答对题目数量
bool flag; // flag = 1 : 有乘除法； flag = 0 : 无乘除法
int n_min = 1, n_max = 100;  // 出题范围在 n_min ~ n_max 之间(默认范围为1~100）
std::vector<std::string> errlog; // 记录错题
std::vector<double> error_ans, ack; // 分别记录错误回答及对于正确答案
std::vector<double> times; //记录每题答题时间

void Input_bool( bool& m) 
{
	while (!(std::cin >> m)) //输入出错
	{
		std::cin.clear(); // 清除错误标志
		std::cin.ignore(1024, '\n');// 清除缓冲区，将回车（包括回车）之前的数据全部清除
		std::cout << "输入 0 或 1，请重新输入：";
	};
	std::cin.ignore(1024,'\n');
}

void Input_int( int& m)
{
	while (!(std::cin >> m))
	{
		std::cin.clear();
		std::cin.ignore(1024, '\n');
		std::cout << "此处输入必须为一个整数，请重新输入：";
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
			std::cout << "此处输入必须为一个整数/浮点数，请重新输入（尽量四舍五入并保留两位小数）：";
		};
		m = round(m * 100) / 100;
	}
	else {
		int temp;
		Input_int(temp);
		m = static_cast<double>(temp);
	}
}

//答题前的简单交互
void Info() 
{
	std::cout << "\t\t\t\t欢迎来到Wkingbai的加减法练习系统\n\n" << "请输入您所希望的答题数目：";
	Input_int(n);
	std::cout << "\n本系统默认运算范围为1~100是否需要重新设置（1：需要，0：不需要）：";
	bool r;
	Input_bool(r);
	if (r) {
		std::cout << "请设置最小取值：";
		Input_int(n_min);
		std::cout << "请设置最大取值：";
		Input_int(n_max);
	}
	std::cout << "\n您希望您的题目中包含乘除法吗？（yes 请输入：1， no 请输入：0 )    答：";
	Input_bool(flag);
	if (flag)
		std::cout << "\n除法运算结果最少保留两位小数（四舍五入）";
	std::cout << "\n\n\t本次答题共100分，每题答对得" << 100.0 / n << "分，答错不得分\n\n";
}

//出题及答题
void Questions_ans() 
{
	 // res: 正确答案  ，  ans : 学生回答  ， oper : 运算类型（1：加，2：减，3：乘，4：除）
	double  res, ans;
	int oper; 
	srand(time(NULL));
	for (int i = 0; i < n; ++i) {
		std::string log; // 记录出题题目
		std::cout << "第" << i + 1 << "道题：";
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
		std::cout << log << std::endl;  //输出出题题目
		const auto start = std::chrono::steady_clock::now(); //开始计时
		Input_value(ans,oper);
		const auto end = std::chrono::steady_clock::now();//结束计时
		auto endtime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0; // 计算答题时间
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

//得分与错题结果
void result() 
{
	double min_s = DBL_MAX, avg_s = 0;  //答题最短用时 和 平均用时
	for (int i = 0; i < times.size(); ++i)
	{
		if (min_s > times[i])
			min_s = times[i];
		avg_s += times[i] / times.size();
	}
	std::cout << "本次答题共答对题目" << num << "道," << "答错" << n - num << "道。";
	std::cout << "答题平均用时为：" << avg_s << "秒，" << "最短用时为：" << min_s << "秒。";
	std::cout << "您最终得分为" << (100.0 / n) * num << std::endl;

	if (num == n)
		std::cout << "\n\n\t\t恭喜你全部答对了，真是个天才呢！\n\n" << std::endl;
	else {
		std::cout << "\n答错题目及正确答案如下：\n\n";
		for (int i = 0; i < errlog.size(); ++i) {
			std::cout << errlog[i] << '\n';
			std::cout << "你的答案为：" << error_ans[i] << '\n';
			std::cout << "正确答案为：" << ack[i] << '\n';
			std::cout << std::endl;
		}
	}
}

int main()
{
	Info();  //系统交互，进行一些常规设置
	std::cout << "\n\n\t\t\t\t答题开始\n\n";
	Questions_ans(); // 出题及解答
	std::cout << "\n\n\t\t\t\t答题结束\n\n";
	result(); // 得分与错题结果
	return 0;
}
