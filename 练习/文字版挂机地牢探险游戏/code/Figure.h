#ifndef FIGURE_H_
#define FIGURE_H_
#include <iostream>
#include <utility>

using namespace std;

class Figure{
public:
	//构造函数 
	Figure() = default;
	Figure(string s, pair<int,int> hp, int atk, pair<int,int> wp = make_pair(0, -1), int wp_type = 0): NAME(s), HP(hp), ATK(atk), Weapon(wp), Wp_type(wp_type){}
	
	//拷贝构造函数 
	Figure(const Figure& fg);
	
	//析构函数 
	~Figure() = default;
	
	//运算符重载 
	bool operator<(Figure &f) const
	{
		return ATK < f.Atk();
	}
	
	//方法 
	void Attack(Figure &enemy);  //攻击 
	void Hp_change(int hp);  //血量变化 
	void HP_assignment(int hp); //血量赋值 
	void Atk_change(int atk); //攻击力变化 
	void Weapon_acquire(int wp_type); //武器获取 
	void Weapon_eff(); //武器效果发动 
	
	string Name() const{
		return NAME;
	}
	pair<int, int> Hp() const{
		return HP; 
	}
	int Atk() const{
		return ATK;
	}
	pair<int, int> Wp() const{
		return Weapon;
	}
	int Wp_tp() const{
		return Wp_type;
	}
	
private:
	string NAME; //名称 
	pair<int, int> HP;  //血量 
	int ATK;  //攻击力 
	pair<int, int> Weapon; //武器 
	int Wp_type; //武器类型 
};

Figure::Figure(const Figure &fg)
{
	NAME = fg.Name(); 
	HP = fg.Hp();
	ATK = fg.Atk();
	Weapon = fg.Wp();
	Wp_type = fg.Wp_tp();
	
}

void Figure::Weapon_acquire(int wp_type)
{
	Wp_type = wp_type;
	if(Wp_type == 1){
		Weapon = make_pair(4, 6);
	}
	else if(Wp_type == 2){
		Weapon = make_pair(0, 6);
	}
	else if(Wp_type == 3){
		Weapon = make_pair(1, 6);
	}
}

void Figure::Weapon_eff()
{
	if(Wp_type == 2){
		Weapon.first = Weapon.second;
	}
	else if(Wp_type == 3){
		if((rand()%100) < 50){
			Weapon.first *= 2;
		}
	}
}

void Figure::Attack(Figure &enemy)
{
	if(Weapon.second == 0)
	{
		Weapon = make_pair(0,-1);
		Wp_type = 0;
		cout << "武器损坏" << "\n\n"; 
	}
	else if(Weapon.second > 0){
		Weapon_eff();
		Weapon.second--;
	}
	enemy.HP.first -= ATK + Weapon.first;
	cout << NAME << "攻击" << enemy.Name() <<",造成" << ATK + Weapon.first << "点伤害," << enemy.Name() << " (" << enemy.Hp().first <<'/' <<enemy.Hp().second <<")\n\n";
}

void Figure::Hp_change(int hp)
{
	HP.first += hp;
	if(HP.first > HP.second)
		HP.first = HP.second;
}

void Figure::HP_assignment(int hp){
	HP.first = hp;
}

void Figure::Atk_change(int atk)
{
	ATK += atk;
}


#endif
