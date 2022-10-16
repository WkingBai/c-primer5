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
	Event() : Explorer("探险家",make_pair(100, 100),10), Room_num(5,0), EXP(make_pair(0 , 10)){ srand((unsigned)time(NULL));}
	~Event() = default;
	void Event_Camp();   //营地 
	void Event_NormalRoom(); //普通房间 
	void Event_TrapRoom(); //陷阱房间 
	void Event_ChiefRoom();  //首领房间 
	void Event_WeaponsRoom(); //武器房间 

	void BuffAndDebuff();  //增减益函数 
	void Exp_add(int num); //经验获取 
	void Dead_message(); //死亡消息 
	
	int ExPlorer_Life(){  
		return Explorer.Hp().first;
	}
private:
	Figure Explorer; //探险家 
	vector<int> Room_num; //统计各类型房间数 
	deque<int> Buff; //增益 
	deque<int> Debuff; //减益 
	pair<int,int> EXP; //经验 
};

// 死亡信息
void Event::Dead_message()
{
	int num = 0;
	for(auto a : Room_num){
		num += a;
	}
	cout << Explorer.Name() << "死亡，共走过" << num <<"个房间，营地：" << Room_num[0] 
														<< "，普通房间：" << Room_num[1] 
														<< ", 陷阱房间: " << Room_num[2]
														<< ", 首领房间: " << Room_num[3]
														<< ", 武器房间: " << Room_num[4]<< "\n\n"; 	
 } 
 
//经验获取
void Event::Exp_add(int num)
{
	EXP.first += num;
	if(EXP.first >= EXP.second){
		EXP.first %= EXP.second;
		Explorer.Hp_change(100);
		cout << "获得" << num <<"点经验,生命回复，当前生命 (" << Explorer.Hp().first << '/' << Explorer.Hp().second <<"),"
			 << "当前经验 (" << EXP.first << '/' << EXP.second <<")\n\n"; 
	}
	else{
		cout << "获得" << num <<"点经验,当前经验 （" << EXP.first << '/' << EXP.second <<")\n\n"; 
	}
 } 

// 增减益函数 
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
				cout << "持续恢复效果触发，获得5点生命，当前生命（" << Explorer.Hp().first << '/' << Explorer.Hp().second <<")" << "\n\n";
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
				cout << "持续损伤效果触发，失去2点生命，当前生命（" << Explorer.Hp().first << '/' << Explorer.Hp().second <<")" << "\n\n";
				if(Explorer.Hp().first <= 0){
					Dead_message();
					exit(0); 
				}
			}
		}
	}
}

// 营地 
void Event::Event_Camp()
{
	
	cout << "进入营地" << "\n\n";
	Room_num[0]++;
	BuffAndDebuff();
	Explorer.Hp_change(100);
	cout << "触发事件，回复" << Explorer.Name() << "全部生命值，当前生命（" <<  Explorer.Hp().first << "/" << Explorer.Hp().second <<")\n\n";
} 



//普通房间
void Event::Event_NormalRoom()
{
	cout << "进入普通房间" << "\n\n";
	Room_num[1]++;
	BuffAndDebuff();
	if( (rand()%100) < 10){
		Explorer.Hp_change(10);
		Buff.push_back(2);
		cout << "触发事件，回复10点生命值，获得持续回血，当前生命值 (" << Explorer.Hp().first << "/" << Explorer.Hp().second <<")\n\n";
	}
	const int num = rand() % 3 + 1;
	vector<Figure> monsters;
	cout << "遇到 "; 
	for(int i = 0; i < num; ++i){
		const int flag = rand() % 2;
		int hp = 6;
		int ack = 3;
		if(flag == 0){
			hp = 14;
			ack = 7;
		}
		Figure p("怪物" + to_string(i+1), make_pair(hp, hp), ack);
		monsters.push_back(p);
		cout << p.Name() << " (" << p.Hp().first << "/" << p.Hp().second << ")  "; 
	}
	cout << "\n\n战斗开始\n\n";
	sort(monsters.begin(), monsters.end());
	
	while(!monsters.empty()){
		Explorer.Attack(monsters.back());
		if(monsters.back().Hp().first <= 0){
			cout << monsters.back().Name() << "死亡" << "\n\n";
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


//陷阱房间
void Event::Event_TrapRoom()
{
	cout << "进入陷阱房间" << "\n\n";
	Room_num[2]++;
	BuffAndDebuff(); 
	int loss_hp = Explorer.Hp().first * 0.1;
	Explorer.Hp_change(-loss_hp);
	Debuff.push_back(5);
	cout << "触发事件，损失" << loss_hp <<"点生命值，造成持续损伤，当前生命值 (" << Explorer.Hp().first << "/" << Explorer.Hp().second <<")\n\n";
	if(Explorer.Hp().first <= 0){
		Dead_message();
		exit(0); 
	}
	cout << "遇到 "; 
	Figure p("怪物1", make_pair(20, 20), 10);
	cout << p.Name() << " (" << p.Hp().first << "/" << p.Hp().second << ")  "; 
	cout << "\n\n战斗开始\n\n";
	
	while(p.Hp().first > 0){
		Explorer.Attack(p);
		if(p.Hp().first <= 0){
			cout << p.Name() << "死亡" << "\n\n";
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

// 首领房间 
void Event::Event_ChiefRoom()
{
	cout << "进入首领房间" << "\n\n";
	Room_num[3]++;
	BuffAndDebuff(); 
	Explorer.Hp_change(20);
	cout << "触发事件，回复20点生命值，当前生命值 (" << Explorer.Hp().first << "/" << Explorer.Hp().second <<")\n\n";
	Debuff.clear();
	cout << "持续损伤效果被移除" << "\n\n"; 
	
	cout << "遇到 "; 
	Figure p("怪物首领", make_pair(40, 40), 15);
	cout << p.Name() << " (" << p.Hp().first << "/" << p.Hp().second << ")  "; 
	cout << "\n\n战斗开始\n\n";
	
	bool talent = 1; // 首领天赋标准位 
	while(p.Hp().first > 0){
		Explorer.Attack(p); 
		if(p.Hp().first <= 0){
			cout << p.Name() << "死亡" << "\n\n";
			break;
		}
		if(p.Hp().first <= 10 && talent == 1){
			talent = 0;
			p.Hp_change(20);
			cout << "怪物首领恢复生命20点，怪物首领 (" <<p.Hp().first << "/" << p.Hp().second <<")\n\n";
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


// 武器房间 
void Event::Event_WeaponsRoom()
{
	cout << "进入武器房间" << "\n\n";
	Room_num[4]++;
	BuffAndDebuff(); 
	int hp = Explorer.Hp().first; 
	cout << "遇到 "; 
	Figure p("怪物1", make_pair(40, 40), 4);
	int wp_type = rand() % 3 + 1;
	p.Weapon_acquire(wp_type);
	cout << p.Name() << " (" << p.Hp().first << "/" << p.Hp().second << ")  "; 
	cout << "\n\n战斗开始\n\n";
	while(p.Hp().first > 0){
		Explorer.Attack(p); 
		if(p.Hp().first <= 0){
			cout << p.Name() << "死亡" << "\n\n";
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
	cout << "生命恢复，当前生命 (" << Explorer.Hp().first << "/" << Explorer.Hp().second <<")\n\n";
	Explorer.Weapon_acquire(wp_type);
	cout << "获得武器" << Explorer.Wp_tp() << "\n\n"; 
}
#endif
