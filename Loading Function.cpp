#include<fstream>
#include "utility.h"
using namespace std;

void LoadingFunction(castle &ct, float &c1, float &c2, float &c3, Queue *&Q)
{
	ifstream inp("input1.txt");
	//Load castle info
	float health;
	int N;
	int TP;
	inp >> health;
	inp >> N;
	inp >> TP;
	for (int i = 0; i < 4; i++)
	{
		ct.towers[i].Health = health;
		ct.towers[i].N = N;
		ct.towers[i].TP = TP;
		ct.towers[i].Paved_Distance = 30;
		ct.towers[i].Total_Damage = 0;
		ct.towers[i].ShieldedCount = 0;
		ct.towers[i].KillCount = 0;
		ct.towers[i].CurrentKillCount = 0;
	}

	//load constants
	inp >> c1;
	inp >> c2;
	inp >> c3;

	//load enemies info
	enemy e;
	e.Distance = 60;
	e.DamageE = 0;
	char regiontemp;
	int Typetemp;
	CreateQueue(Q);
	inp >> e.ID;
	while (e.ID != -1)
	{
		inp >> Typetemp;
		e.Type = (Etype)Typetemp;
		inp >> e.Tarrival;
		inp >> e.Health;
		inp >> e.Fire_power;
		inp >> e.Reload_period;
		//Load Region
		inp >> regiontemp;
		e.Region = CharToEnum(regiontemp);
		inp >> e.velocity;
		Enqueue(Q, e);
		inp >> e.ID;
	}
	inp.close();
}