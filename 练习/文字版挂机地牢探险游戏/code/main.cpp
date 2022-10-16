#include "Event.h"

using namespace std;

int main()
{
	Event Game;
	while(Game.ExPlorer_Life() > 0){
		int opt = rand() % 100;
		if(opt < 10)
			Game.Event_Camp();
		else if(opt > 10 && opt < 65)
			Game.Event_NormalRoom();
		else if(opt >= 65 && opt < 80)
			Game.Event_TrapRoom();
		else if( opt >= 80 && opt < 90)
			Game.Event_ChiefRoom();
		else
			Game.Event_WeaponsRoom(); 
	}
} 
