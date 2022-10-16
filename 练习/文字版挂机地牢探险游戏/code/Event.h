#ifndef EVENT_H_
#define EVENT_H_

#include <ctime>
#include <cstdlib>
#include <stdlib.h>
#include <deque>
#include <vector>
#include <algorithm>
#include "Figure.h" 
using namespace std;

class Event {
public: 
	Event() : Explorer("̽�ռ�",make_pair(100, 100),10), Room_num(5,0), EXP(make_pair(0 , 10)){ srand((unsigned)time(NULL));}
	~Event() = default;
	void Event_Camp();   //Ӫ�� 
	void Event_NormalRoom(); //��ͨ���� 
	void Event_TrapRoom(); //���巿�� 
	void Event_ChiefRoom();  //���췿�� 
	void Event_WeaponsRoom(); //�������� 

	void BuffAndDebuff();  //�����溯�� 
	void Exp_add(int num); //�����ȡ 
	void Dead_message(); //������Ϣ 
	
	int ExPlorer_Life(){  
		return Explorer.Hp().first;
	}
private:
	Figure Explorer; //̽�ռ� 
	vector<int> Room_num; //ͳ�Ƹ����ͷ����� 
	deque<int> Buff; //���� 
	deque<int> Debuff; //���� 
	pair<int,int> EXP; //���� 
};

// ������Ϣ
void Event::Dead_message()
{
	int num = 0;
	for(auto a : Room_num){
		num += a;
	}
	cout << Explorer.Name() << "���������߹�" << num <<"�����䣬Ӫ�أ�" << Room_num[0] 
														<< "����ͨ���䣺" << Room_num[1] 
														<< ", ���巿��: " << Room_num[2]
														<< ", ���췿��: " << Room_num[3]
														<< ", ��������: " << Room_num[4]<< "\n\n"; 	
 } 
 
//�����ȡ
void Event::Exp_add(int num)
{
	EXP.first += num;
	if(EXP.first >= EXP.second){
		EXP.first %= EXP.second;
		Explorer.Hp_change(100);
		cout << "���" << num <<"�㾭��,�����ظ�����ǰ���� (" << Explorer.Hp().first << '/' << Explorer.Hp().second <<"),"
			 << "��ǰ���� (" << EXP.first << '/' << EXP.second <<")\n\n"; 
	}
	else{
		cout << "���" << num <<"�㾭��,��ǰ���� ��" << EXP.first << '/' << EXP.second <<")\n\n"; 
	}
 } 

// �����溯�� 
void Event::BuffAndDebuff()
{
	if(!Buff.empty()){
		while(!Buff.empty() && Buff.front() == 0){
			Buff.pop_front();
		}
		if(!Buff.empty()){
			for(auto &a : Buff){
				a--;
				Explorer.Hp_change(5) ;
				cout << "�����ָ�Ч�����������5����������ǰ������" << Explorer.Hp().first << '/' << Explorer.Hp().second <<")" << "\n\n";
			}
		}
	}
	
	if(!Debuff.empty()){
		while(!Debuff.empty() && Debuff.front() == 0){
			Debuff.pop_front();
		}
		if(!Debuff.empty()){
			for(auto &a : Debuff){
				a--;
				Explorer.Hp_change(-2);
				cout << "��������Ч��������ʧȥ2����������ǰ������" << Explorer.Hp().first << '/' << Explorer.Hp().second <<")" << "\n\n";
				if(Explorer.Hp().first <= 0){
					Dead_message();
					exit(0); 
				}
			}
		}
	}
}

// Ӫ�� 
void Event::Event_Camp()
{
	
	cout << "����Ӫ��" << "\n\n";
	Room_num[0]++;
	BuffAndDebuff();
	Explorer.Hp_change(100);
	cout << "�����¼����ظ�" << Explorer.Name() << "ȫ������ֵ����ǰ������" <<  Explorer.Hp().first << "/" << Explorer.Hp().second <<")\n\n";
} 



//��ͨ����
void Event::Event_NormalRoom()
{
	cout << "������ͨ����" << "\n\n";
	Room_num[1]++;
	BuffAndDebuff();
	if( (rand()%100) < 10){
		Explorer.Hp_change(10);
		Buff.push_back(2);
		cout << "�����¼����ظ�10������ֵ����ó�����Ѫ����ǰ����ֵ (" << Explorer.Hp().first << "/" << Explorer.Hp().second <<")\n\n";
	}
	const int num = rand() % 3 + 1;
	vector<Figure> monsters;
	cout << "���� "; 
	for(int i = 0; i < num; ++i){
		const int flag = rand() % 2;
		int hp = 6;
		int ack = 3;
		if(flag == 0){
			hp = 14;
			ack = 7;
		}
		Figure p("����" + to_string(i+1), make_pair(hp, hp), ack);
		monsters.push_back(p);
		cout << p.Name() << " (" << p.Hp().first << "/" << p.Hp().second << ")  "; 
	}
	cout << "\n\nս����ʼ\n\n";
	sort(monsters.begin(), monsters.end());
	
	while(!monsters.empty()){
		Explorer.Attack(monsters.back());
		if(monsters.back().Hp().first <= 0){
			cout << monsters.back().Name() << "����" << "\n\n";
			monsters.pop_back();
		}
		for(auto &a : monsters){
			a.Attack(Explorer);
			if(Explorer.Hp().first <= 0){
				Dead_message();
				exit(0); 
			}
		}
	}
	Exp_add(num);
 } 


//���巿��
void Event::Event_TrapRoom()
{
	cout << "�������巿��" << "\n\n";
	Room_num[2]++;
	BuffAndDebuff(); 
	int loss_hp = Explorer.Hp().first * 0.1;
	Explorer.Hp_change(-loss_hp);
	Debuff.push_back(5);
	cout << "�����¼�����ʧ" << loss_hp <<"������ֵ����ɳ������ˣ���ǰ����ֵ (" << Explorer.Hp().first << "/" << Explorer.Hp().second <<")\n\n";
	if(Explorer.Hp().first <= 0){
		Dead_message();
		exit(0); 
	}
	cout << "���� "; 
	Figure p("����1", make_pair(20, 20), 10);
	cout << p.Name() << " (" << p.Hp().first << "/" << p.Hp().second << ")  "; 
	cout << "\n\nս����ʼ\n\n";
	
	while(p.Hp().first > 0){
		Explorer.Attack(p);
		if(p.Hp().first <= 0){
			cout << p.Name() << "����" << "\n\n";
			break;
		}
		p.Attack(Explorer);
		if(Explorer.Hp().first <= 0){
			Dead_message();
			exit(0); 
		}
	}
	Exp_add(1);
 } 

// ���췿�� 
void Event::Event_ChiefRoom()
{
	cout << "�������췿��" << "\n\n";
	Room_num[3]++;
	BuffAndDebuff(); 
	Explorer.Hp_change(20);
	cout << "�����¼����ظ�20������ֵ����ǰ����ֵ (" << Explorer.Hp().first << "/" << Explorer.Hp().second <<")\n\n";
	Debuff.clear();
	cout << "��������Ч�����Ƴ�" << "\n\n"; 
	
	cout << "���� "; 
	Figure p("��������", make_pair(40, 40), 15);
	cout << p.Name() << " (" << p.Hp().first << "/" << p.Hp().second << ")  "; 
	cout << "\n\nս����ʼ\n\n";
	
	bool talent = 1; // �����츳��׼λ 
	while(p.Hp().first > 0){
		Explorer.Attack(p); 
		if(p.Hp().first <= 0){
			cout << p.Name() << "����" << "\n\n";
			break;
		}
		if(p.Hp().first <= 10 && talent == 1){
			talent = 0;
			p.Hp_change(20);
			cout << "��������ָ�����20�㣬�������� (" <<p.Hp().first << "/" << p.Hp().second <<")\n\n";
		}
		else
			p.Attack(Explorer);
		p.Atk_change(1);
		if(Explorer.Hp().first <= 0){
			Dead_message();
			exit(0); 
		}
	}
	Exp_add(5);
}


// �������� 
void Event::Event_WeaponsRoom()
{
	cout << "������������" << "\n\n";
	Room_num[4]++;
	BuffAndDebuff(); 
	int hp = Explorer.Hp().first; 
	cout << "���� "; 
	Figure p("����1", make_pair(40, 40), 4);
	int wp_type = rand() % 3 + 1;
	p.Weapon_acquire(wp_type);
	cout << p.Name() << " (" << p.Hp().first << "/" << p.Hp().second << ")  "; 
	cout << "\n\nս����ʼ\n\n";
	while(p.Hp().first > 0){
		Explorer.Attack(p); 
		if(p.Hp().first <= 0){
			cout << p.Name() << "����" << "\n\n";
			break;
		}
		p.Attack(Explorer);
		if(Explorer.Hp().first <= 0){
			Dead_message();
			exit(0); 
		}
	}
	Exp_add(2);
	Explorer.HP_assignment(hp);
	cout << "�����ָ�����ǰ���� (" << Explorer.Hp().first << "/" << Explorer.Hp().second <<")\n\n";
	Explorer.Weapon_acquire(wp_type);
	cout << "�������" << Explorer.Wp_tp() << "\n\n"; 
}
#endif
