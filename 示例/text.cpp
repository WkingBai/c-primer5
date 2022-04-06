#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<forward_list>
#include<list> 
#include<deque>
#include<set>
#include<map>
#include<utility>
#include<algorithm>
#include<numeric>
#include<functional>
#include<iterator> 
using namespace std::placeholders;
using namespace std;

int main(int argc, char**argv)
{
	string author = "机械先驱";
	string author1 = "卡牌大师";
	multimap<string, string> Library;
	Library.insert(make_pair(author1,"灭世者的帽子"));
	Library.insert(make_pair(author,"法穿杖"));
	Library.insert(make_pair(author1,"法穿鞋"));
	Library.insert(make_pair(author,"冰杖"));
	Library.insert(make_pair(author,"巫妖之祸"));
	Library.insert(make_pair(author,"海克斯科技核心"));
 
	auto it1 = Library.find(author); //返回第一个关键字为author的迭代器
	auto it2 = Library.count(author);//返回关键词为author的元素数量
 
	while (it2)
	{
		if (it1->second == "海克斯科技核心")
		{
			Library.erase(it1);//直接删除此关键字值对，传入参数为指向它的迭代器
			break;//需要,不然下面调用到已经删除的迭代器，会出粗
		}
		++it1;
		--it2;
	}
	
	map<string,set<string>> Library2;//排序所用map,set可自动排序
	multimap<string,string>::iterator it3 = Library.begin();
	for (it3; it3 != Library.end(); ++it3)
	{
		/*Library2.insert(make_pair(it3->first,it3->second));*/
		Library2[it3->first].insert(it3->second);
		cout<<it3->first<<"的宝贝儿："<<it3->second<<endl;
	}
	
	for(auto a : Library2){
		cout << a.first <<":" ;
		for(auto b : a.second)
			cout << b << ' ';
		cout << endl;
}
	return 0;
}
