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
	string author = "��е����";
	string author1 = "���ƴ�ʦ";
	multimap<string, string> Library;
	Library.insert(make_pair(author1,"�����ߵ�ñ��"));
	Library.insert(make_pair(author,"������"));
	Library.insert(make_pair(author1,"����Ь"));
	Library.insert(make_pair(author,"����"));
	Library.insert(make_pair(author,"����֮��"));
	Library.insert(make_pair(author,"����˹�Ƽ�����"));
 
	auto it1 = Library.find(author); //���ص�һ���ؼ���Ϊauthor�ĵ�����
	auto it2 = Library.count(author);//���عؼ���Ϊauthor��Ԫ������
 
	while (it2)
	{
		if (it1->second == "����˹�Ƽ�����")
		{
			Library.erase(it1);//ֱ��ɾ���˹ؼ���ֵ�ԣ��������Ϊָ�����ĵ�����
			break;//��Ҫ,��Ȼ������õ��Ѿ�ɾ���ĵ������������
		}
		++it1;
		--it2;
	}
	
	map<string,set<string>> Library2;//��������map,set���Զ�����
	multimap<string,string>::iterator it3 = Library.begin();
	for (it3; it3 != Library.end(); ++it3)
	{
		/*Library2.insert(make_pair(it3->first,it3->second));*/
		Library2[it3->first].insert(it3->second);
		cout<<it3->first<<"�ı�������"<<it3->second<<endl;
	}
	
	for(auto a : Library2){
		cout << a.first <<":" ;
		for(auto b : a.second)
			cout << b << ' ';
		cout << endl;
}
	return 0;
}
