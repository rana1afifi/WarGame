#include <iostream>
#include<fstream>
#include <iomanip>
#include "utility.h"
using namespace std;

ofstream out("output.txt");
//Functions to check Full or Empty lists
bool IsFull()
{
	Node *newNode = new Node;
	if (newNode == NULL)
		return true;
	else return false;
}
bool IsEmptyQueue(Queue *q)
{
	if (q->count == 0)
		return true;
	else
		return false;
}
bool IsEmptyList(list *L)
{
	if (L->count == 0)
		return true;
	return false;
}

//Functions of linked list
//function to create a list
void CreateList(list *&Lhead)
{
	Lhead = new list;
	Lhead->head = NULL;
	Lhead->count = 0;
}
//function to insert at the beginning
bool InsertBeg(list *&L, enemy e)
{
	Node *Node1 = new Node;
	if (Node1 == NULL)
		return false;
	Node1->e = e;
	Node1->next = L->head;
	L->head = Node1;
	L->count++;
	return true;
}
//function to insert at the end of a list
bool InsertEnd(list *&L, enemy e)
{
	Node *addedNode = new Node;
	if (addedNode == NULL)
		return false;
	addedNode->e = e;
	addedNode->next = NULL;
	if (L->head == NULL)
	{
		InsertBeg(L, e);
		return true;
	}
	Node *temp = L->head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = addedNode;
	L->count++;
	return true;
}
//Delete From Begenning
bool DeleteFirst(list*& L, enemy & edeleted)
{
	if (L->count == 0)
		return false;
	Node *temp = L->head;
	edeleted = temp->e;
	L->head = temp->next;
	L->count--;
	delete temp;
	return true;
}
//Delete From Middle
bool DeleteMid(list *&L, int IDK, enemy &edeleted)
{
	Node *ptr = L->head;
	Node *ptr_prev = ptr;
	while (ptr->e.ID != IDK)
	{
		ptr_prev = ptr;
		ptr = ptr->next;
		if (ptr == NULL)
		{
			return false;
		}
	}
	if (ptr == L->head)
	{
		L->head = ptr->next;
		edeleted = ptr->e;
		L->count--;
		delete ptr;
		return true;
	}
	else
	{
		edeleted = ptr->e;
		ptr_prev->next = ptr->next;
		delete ptr;
		L->count--;
		return true;
	}
}


//Functions of Queues
//Create Queue
void CreateQueue(Queue *&q)
{
	q = new Queue;
	if (q == NULL)
		return;
	q->front = q->rear = NULL;
	q->count = 0;
}
//function EnQueue
bool Enqueue(Queue *&q, enemy e)
{
	if (IsFull())
		return false;
	Node *AddedNode = new Node;
	AddedNode->e = e;
	AddedNode->next = NULL;
	if (IsEmptyQueue(q))
	{
		q->front = q->rear = AddedNode;
		q->rear->next = NULL;
	}
	else
	{
		q->rear->next = AddedNode;
		q->rear = AddedNode;
	}
	q->count++;
	return true;
}
//function Dequeue
bool Dequeue(Queue*&q, enemy &edeleted)
{
	Node *deletedNode;
	if (IsEmptyQueue(q))
		return false;
	deletedNode = q->front;
	if (q->count == 1)
	{
		q->front = q->rear = NULL;
	}
	else
	{
		q->front = q->front->next;
	}
	edeleted = deletedNode->e;
	delete deletedNode;
	q->count--;
	return true;
}

REGION CharToEnum(char RegionTemp)
{
	if (RegionTemp == 'A')
		return A_REG;
	else if (RegionTemp == 'B')
		return B_REG;
	else  if (RegionTemp == 'C')
		return C_REG;
	else return D_REG;
}

//Functions sorting
// Insertion sort for linked list (descendingly) 
void InsertionSortLinkedList(list*&L)
{
	Node*ptr = L->head->next;
	Node*ptr_prev = L->head;
	Node*walker;

	while (ptr != NULL) // ptr->enemy==2
	{
		if (ptr->e.Type != 2)
			return;
		walker = L->head;
		float element = ptr->e.Priority;
		if (L->head->e.Priority <= element)
		{
			ptr_prev->next = ptr->next;
			ptr->next = L->head;
			L->head = ptr;
			// Incrementation
			ptr = ptr_prev->next;
		}
		else
		{
			while (walker->next != NULL && walker->next->e.Priority > element)
			{
				walker = walker->next;
			}
			if (walker == ptr_prev)
			{
				ptr_prev = ptr_prev->next;
				ptr = ptr->next;
			}
			else
			{
				ptr_prev->next = ptr->next;
				ptr->next = walker->next;
				walker->next = ptr;
				ptr = ptr_prev->next;
			}
		}
	}
}
void MergeSorted(Node *p1, Node *p2, list *&Merged) // Pass to it the first non-shielded enemy
{
	enemy x;
	while (p1 != NULL && p2 != NULL)
	{
		if (p1->e.Tarrival < p2->e.Tarrival)
		{
			x = p1->e;
			p1 = p1->next;
			InsertEnd(Merged, x);

			//delete head1;
		}
		else if (p1->e.Tarrival > p2->e.Tarrival)
		{
			x = p2->e;
			p2 = p2->next;
			InsertEnd(Merged, x);

			//delete head2;
		}
		else // If two enemies have the same arrival time , we sort them by health 
		{
			if (p1->e.Health > p2->e.Health)
			{
				x = p1->e;
				p1 = p1->next;
				InsertEnd(Merged, x);
				x = p2->e;
				p2 = p2->next;
				InsertEnd(Merged, x);

			}
			else
			{
				x = p2->e;
				p2 = p2->next;
				InsertEnd(Merged, x);
				x = p1->e;
				p1 = p1->next;
				InsertEnd(Merged, x);
			}
		}
	}

	while (p1 != NULL)
	{
		x = p1->e;
		p1 = p1->next;
		InsertEnd(Merged, x);
		//delete head1;
	}
	while (p2 != NULL)
	{
		x = p2->e;
		p2 = p2->next;
		InsertEnd(Merged, x);
	}
	//delete head2;
}
void BubbleSort(enemy x[], int n)
{
	bool exchanges;
	do {
		exchanges = false;  // assume no exchanges
		for (int i = 0; i<n - 1; i++)
		{
			if (x[i].Fight_Delay>x[i + 1].Fight_Delay)
			{
				enemy temp = x[i];
				x[i] = x[i + 1];
				x[i + 1] = temp;
				exchanges = true;  // after exchange, must look again
			}
		}
	} while (exchanges);
}

//Simulation Functions
//Function to move from inactive list to active list
bool MoveInAct(Queue *&Q, list *&LA, list *&LB, list *&LC, list *&LD, Tower Towers[])
{
	enemy x;
	if (IsEmptyQueue(Q))
		return false;
	Dequeue(Q, x);
	int eRegion = x.Region;
	int adjRegion;
	if (Towers[eRegion].Health == 0)
	{
		adjRegion = FindAdjacent(eRegion, Towers);
		x.Region = (REGION)adjRegion;
	}

	if (x.Region == 0)
	{
		if (x.Type == 2)
		{
			InsertBeg(LA, x);
			Towers[0].ShieldedCount++;
		}

		else
			InsertEnd(LA, x);
	}
	else if (x.Region == 1)
	{
		if (x.Type == 2)
		{
			InsertBeg(LB, x);
			Towers[1].ShieldedCount++;
		}
		else
			InsertEnd(LB, x);
	}
	else if (x.Region == 2)
	{
		if (x.Type == 2)
		{
			InsertBeg(LC, x);
			Towers[2].ShieldedCount++;
		}
		else
			InsertEnd(LC, x);
	}
	else
	{
		if (x.Type == 2)
		{
			InsertBeg(LD, x);
			Towers[3].ShieldedCount++;
		}
		else
			InsertEnd(LD, x);
	}
	return true;
}
//Function to check if the enemy in its reload period
bool IsReloading(enemy e, int TimeStep, int &remaining_time)
{
	int rem = (TimeStep - e.Tarrival) % e.Reload_period;
	if (rem == 0)
	{
		remaining_time = 0;
		return false;
	}
	else
	{
		remaining_time = e.Reload_period - rem;
		return true;
	}
}
//Function shoot enemy -> tower
bool ShootAtTower(list *&Active_list, Tower &T, int TimeStep)
{
	T.Current_Damage = 0.0;
	if (Active_list->head == NULL)
		return false;
	int remaining_time;
	Node *ptr = Active_list->head;

	while (ptr != NULL)
	{
		if (ptr->e.Type != PVR && !IsReloading(ptr->e, TimeStep, remaining_time))
		{
			T.Current_Damage += ((1 / (float)ptr->e.Distance)*(float)ptr->e.Fire_power);
		}
		ptr = ptr->next;
	}
	T.Total_Damage += T.Current_Damage;
	return true;
}
// Function to shoot at enemy
int ShootAtEnemy(Tower &tower, list *&Active, int TimeStep, int &TotalFightDelay, float c1, float c2, float c3)
{
	if (Active->count == 0)
		return 0;
	Node *ptr = Active->head;
	// Priority Condition
	if (tower.ShieldedCount > tower.N)
	{
		// First Calculate Enemies Priorities
		int remaining_time;
		for (int i = 0; i<tower.ShieldedCount; i++)
		{
			if (ptr == NULL)
				break;
			bool Reload = IsReloading(ptr->e, TimeStep, remaining_time);
			ptr->e.Priority = c1*(float)ptr->e.Fire_power / (float)ptr->e.Distance + c2 / (float)(remaining_time + 1) + c3*(float)ptr->e.Health;
			ptr = ptr->next;
		}
		InsertionSortLinkedList(Active);  //Sort shielded enemies according to priority
	}
	ptr = Active->head;
	int EnemiesShot;  // Determine the end of the iteration 

	//Fighting
	if (tower.N <= Active->count)
		EnemiesShot = tower.N;
	else
		EnemiesShot = Active->count;
	for (int m = 0; m < EnemiesShot; m++)
	{
		if (ptr == NULL)
			break;
		if (ptr->e.DamageE == 0)
		{
			ptr->e.Tfirst_shot = TimeStep;
			ptr->e.Fight_Delay = ptr->e.Tfirst_shot - ptr->e.Tarrival;
			TotalFightDelay += ptr->e.Fight_Delay;
		}
		if (ptr->e.Type == 0 || ptr->e.Type == 1) // Calculate Damage
		{
			ptr->e.DamageE = (float)tower.TP / (float)ptr->e.Distance;
		}
		else if (ptr->e.Type == 2)
		{
			ptr->e.DamageE = (float)tower.TP / (float)(2 * ptr->e.Distance);
		}
		ptr = ptr->next;
	}
	return EnemiesShot;
}
//Function to check for the paved distance
bool IsPaved(int PavedDistance, int enemyDistance)
{
	if (enemyDistance - (60 - PavedDistance)>0)
		return true;
	else return false;
}
//Function to move enemies
bool MoveAndPave(list*&Active_list, int TimeStep, Tower &tower)
{
	if (Active_list->head == NULL)
		return false;
	int remainingTime;
	Node *temp = Active_list->head;
	//Move enemies
	while (temp != NULL)
	{
		if (temp->e.Type != 0)
		{
			for (int i = 0; i<temp->e.velocity; i++)
			{
				if (IsPaved(tower.Paved_Distance, temp->e.Distance))
					temp->e.Distance--;
			}
			if (temp->e.Distance<2)
				temp->e.Distance = 2;
		}
		else if (temp->e.Type == 0)
		{
			if (temp->e.Fire_power == 0 || IsReloading(temp->e, TimeStep, remainingTime))
			{
				for (int i = 0; i < temp->e.velocity; i++)
				{
					if (IsPaved(tower.Paved_Distance, temp->e.Distance))
						temp->e.Distance--;
				}
				if (temp->e.Distance < 2)
					temp->e.Distance = 2;
			}
		}
		temp = temp->next;
	}
	temp = Active_list->head;
	while (temp != NULL)
	{
		if (temp->e.Type == 0)
		{
			if (temp->e.Fire_power != 0 || !IsReloading(temp->e, TimeStep, remainingTime))
			{
				for (int i = 0; i<temp->e.Fire_power; i++)
				{
					if (IsPaved(tower.Paved_Distance, temp->e.Distance))
					{
						temp->e.Distance--;
						if (temp->e.Distance<2)
						{
							temp->e.Distance = 2;
							break;
						}
					}
					else
					{
						tower.Paved_Distance++;
						if (tower.Paved_Distance>58)
							tower.Paved_Distance = 58;
						temp->e.Distance--;
						if (temp->e.Distance < 2)
							temp->e.Distance = 2;
					}
				}
			}
		}
		temp = temp->next;
	}
}
//Function to find the next region to move enemies
int FindAdjacent(int iKilledTower, Tower Towerarr[])
{
	int temp = iKilledTower + 1;
	if (temp > 3)
		temp = 0;
	bool isfound = false;
	int iRegion;
	while (!isfound)
	{
		if (Towerarr[temp].Health > 0)
		{
			iRegion = temp;
			isfound = true;
		}
		else
		{
			temp++;
			if (temp > 3)
				temp = 0;
		}
	}
	return iRegion;
}
//Function to move to the adjacent region 
void MoveToAdjacent(Tower Towerarr[], int iKilledTower, list *ActiveLists[], castle ct)
{
	if (GameLoss(ct))
		return;
	if (ActiveLists[iKilledTower]->count == 0)
		return;
	int iRegion = FindAdjacent(iKilledTower, Towerarr);

	list*Merged;
	CreateList(Merged);
	Node*p1 = ActiveLists[iKilledTower]->head;
	Node*p2 = ActiveLists[iRegion]->head;

	// Adjust distance of enemies to fit paved distance of tower 
	while (p1 != NULL)
	{
		p1->e.Region = REGION(iRegion);
		if (!IsPaved(Towerarr[iRegion].Paved_Distance, p1->e.Distance))
		{
			p1->e.Distance = 60 - Towerarr[iRegion].Paved_Distance;
		}
		p1 = p1->next;
	}

	p1 = ActiveLists[iKilledTower]->head;
	// Move Shielded to Merged 
	while (p1 != NULL && p1->e.Type == 2)
	{
		InsertBeg(Merged, p1->e);
		p1 = p1->next;
	}

	while (p2 != NULL && p2->e.Type == 2)
	{
		InsertBeg(Merged, p2->e);
		p2 = p2->next;
	}

	// Insert Sorted of enemies of other types
	MergeSorted(p1, p2, Merged);
	// Destroy list of ikilled and list of iRegion
	p1 = ActiveLists[iKilledTower]->head;
	p2 = ActiveLists[iRegion]->head;
	enemy deleted;
	while (!IsEmptyList(ActiveLists[iRegion]))
	{
		DeleteFirst(ActiveLists[iRegion], deleted);
	}
	while (!IsEmptyList(ActiveLists[iKilledTower]))
	{
		DeleteFirst(ActiveLists[iKilledTower], deleted);
	}
	// Make List of adjacent point to Merged 
	ActiveLists[iRegion]->head = Merged->head;
	ActiveLists[iRegion]->count = Merged->count;

	//Deallocate list merged
	Merged = NULL;
	delete Merged;
}
//Function Kill 
void Kill(list* Active_list[], Tower towers[], int TimeStep, int &TotalKillDelay)
{
	int n;
	int TotalCurrentKillCount = 0;
	for (int x = 0; x<4; x++)
	{
		towers[x].CurrentKillCount = 0;
		Node* temp = Active_list[x]->head;
		while (temp != NULL)
		{
			if (temp->e.Health <= 0)
			{
				towers[x].CurrentKillCount++;
				towers[x].KillCount++;
			}
			temp = temp->next;
		}
		TotalCurrentKillCount += towers[x].CurrentKillCount;
	}
	n = TotalCurrentKillCount;
	enemy *killed = new enemy[n];
	int i = 0;

	for (int y = 0; y<4; y++)
	{
		Node* temp = Active_list[y]->head;
		enemy x;
		while (temp != NULL)
		{
			if (temp->e.Health <= 0)
			{
				if (temp->e.Type == 2)
					towers[y].ShieldedCount--;
				temp->e.TKill = TimeStep;
				temp->e.Kill_Delay = temp->e.TKill - temp->e.Tfirst_shot;
				TotalKillDelay += temp->e.Kill_Delay;
				temp->e.Total_fight_time = temp->e.Kill_Delay + temp->e.Fight_Delay;
				x = temp->e;
				temp = temp->next;
				DeleteMid(Active_list[y], x.ID, x);
				killed[i] = x;
				i++;
			}
			else
				temp = temp->next;
		}
	}

	if (n >= 1)
	{
		BubbleSort(killed, n);
		for (int j = 0; j<n; j++)
		{
			out << TimeStep << setw(6) << killed[j].ID << setw(6) << killed[j].Fight_Delay << setw(6) << killed[j].Kill_Delay << setw(6);
			out << killed[j].Total_fight_time << endl;
		}
	}
	delete[] killed;
}
//Health Calculations 
void Calculations(list*& Active_list, Tower &tower, int EnemiesShot)
{
	// Health of enemy , Health of Tower ; 
	tower.Health -= tower.Current_Damage;
	if (tower.Health < 0)
		tower.Health = 0;
	Node*p1 = Active_list->head;
	for (int m = 0; m < EnemiesShot; m++)
	{
		float k = p1->e.DamageE;
		p1->e.Health -= k;
		p1 = p1->next;
	}
}
//Function to form an array of enemy pointers
void ListToArrayptr(list *Activelists, enemy *Activenemies[], int &count)
{
	Node *temp;
	temp = Activelists->head;
	if (Activelists->head == NULL)
		return;
	while (temp != NULL)
	{
		Activenemies[count] = &temp->e;
		temp = temp->next;
		count++;
	}
}
//Function Output
void OutputFile(Tower towers[], bool GameWin, bool GameLoss, int TotalKillDelay, int TotalFightDelay, list*Active_list[], int TimeStep)
{
	out << "T1_Total_Damage" << setw(20) << "T2_Total_Damage" << setw(20) << "T3_Total_Damage" << setw(20) << "T4_Total_Damage" << endl;
	out << ceil(towers[0].Total_Damage * 100) / 100 << setw(20) << ceil(towers[1].Total_Damage * 100) / 100 << setw(20) << ceil(towers[2].Total_Damage * 100) / 100 << setw(20) << ceil(towers[3].Total_Damage * 100) / 100 << endl;

	out << "R1_Distance" << setw(20) << "R2_Distance" << setw(20) << "R3_Distance" << setw(20) << "R4_Distance" << endl;
	out << 60 - towers[0].Paved_Distance << setw(20) << 60 - towers[1].Paved_Distance << setw(20) << 60 - towers[2].Paved_Distance << setw(20) << 60 - towers[0].Paved_Distance << endl;
	int KilledEnemies = towers[0].KillCount + towers[1].KillCount + towers[2].KillCount + towers[3].KillCount;
	if (GameWin)
	{
		out << "Game is WIN" << endl;
		out << "Total Enemies= " << KilledEnemies << endl;
	}
	else if (GameLoss)
	{
		out << "Game is LOSS" << endl;
		out << "Number of killed enemies= " << KilledEnemies << endl;
		out << "Number of alive enemies= " << Active_list[0]->count + Active_list[1]->count + Active_list[2]->count + Active_list[3]->count << endl;
	}
	if (KilledEnemies != 0)
	{
		out << "Fight Delay Average= " << ceil((TotalFightDelay /(float) KilledEnemies)*100)/100 << endl;
		out << "Kill Delay Average= " << ceil((TotalKillDelay /(float) KilledEnemies)*100)/100 << endl;
	}
}
//Function modes
void GraphicsAndModes(list*Active_list[], int mode, Tower Towers[], enemy *ActiveEnemies[], int count, castle ct, int TimeStep)
{
	if (mode == 1 || mode == 2)
	{
		SetWindow();
		DrawCastle(ct, TimeStep);
		DrawEnemies(ActiveEnemies, count);
		cout << "Total current enemies A = " << Active_list[0]->count << " B = " << Active_list[1]->count << " C = " << Active_list[2]->count << " D = " << Active_list[3]->count << " \n";
		cout << "Last time step kill A = " << Towers[0].CurrentKillCount << " B = " << Towers[1].CurrentKillCount << " C = " << Towers[2].CurrentKillCount << " D = " << Towers[3].CurrentKillCount << endl;
		cout << "Total killed by A = " << Towers[0].KillCount << " B = " << Towers[1].KillCount << " C = " << Towers[2].KillCount << " D = " << Towers[3].KillCount << "\n";
		cout << "Unpaved distance A = " << 60 - Towers[0].Paved_Distance << " B = " << 60 - Towers[1].Paved_Distance << " C = " << 60 - Towers[2].Paved_Distance << " D = " << 60 - Towers[3].Paved_Distance << "\n";
	}
	if (mode == 1)
		cin.get();
	else if (mode == 2)
		Sleep(1000);
}
//Function to check if Game WIN or LOSS
bool GameWin(castle c, int Total_Enemies)
{
	int SumKill = c.towers[0].KillCount + c.towers[1].KillCount + c.towers[2].KillCount + c.towers[3].KillCount;
	if (SumKill == Total_Enemies)
		return true;
	else
		return false;
}
//Check if game LOSS
bool GameLoss(castle ct)
{
	bool Loss = true;
	for (int i = 0; i < 4; i++)
	{
		if (ct.towers[i].Health > 0)
		{
			Loss = false;
			break;
		}
	}
	if (!Loss)
		return false;
	else return true;
}

//Graphics Functions
//A function to set the position of cursor on the screen
void gotoxy(int x, int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	_COORD pos;
	pos.X = x;
	pos.Y = y;

	SetConsoleCursorPosition(hConsole, pos);
}
//A function to set the command window lenght and height for the game specification
void SetWindow()
{
	system("mode 150,50");   //Set mode to ensure window does not exceed buffer size
	SMALL_RECT WinRect = { 0, 0, CmdWidth, CmdHeight };   //New dimensions for window in 8x12 pixel chars
	SMALL_RECT* WinSize = &WinRect;
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, WinSize);   //Set new size for window
}
//A function to color the cmd text
void color(int thecolor)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout,
		thecolor | FOREGROUND_INTENSITY);
}
//A function to partition the castle into regions (A,B,C,D)
void DrawRegions(const castle & C)
{
	color(FOREGROUND_RED | FOREGROUND_BLUE);
	gotoxy(0, C.Ystrt + C.L / 2);
	for (int i = 0; i<C.W + 2 * C.Xstrt; i++)
		cout << "-";
	for (int j = 0; j<C.L + 2 * C.Ystrt; j++)
	{
		gotoxy(C.Xstrt + C.W / 2, j);
		cout << "|";
	}
	color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
//A function to draw the castle and the towers
void DrawCastle(const castle & C, int SimulationTime)
{
	system("CLS");

	//Draw the castle
	cout << endl;
	gotoxy(C.Xstrt, C.Ystrt);
	for (int i = 0; i<C.W; i++)
		cout << "=";
	for (int j = 1; j<C.L; j++)
	{
		gotoxy(C.Xstrt, C.Ystrt + j);
		cout << "|";
		gotoxy(C.Xstrt + C.W - 1, C.Ystrt + j);
		cout << "|";
	}
	gotoxy(C.Xstrt, C.Ystrt + C.L - 1);
	for (int i = 0; i<C.W; i++)
		cout << "=";

	//Draw towers
	int T1X, T2X, T3X, T4X, T1Y, T2Y, T3Y, T4Y;
	for (int i = 0; i<4; i++)
	{

		if (i == 0)
		{
			T1X = C.Xstrt + 1;
			T1Y = C.Ystrt + TowerLength;
			gotoxy(T1X, T1Y);
			for (int i = 0; i<TowerWidth; i++)
				cout << "=";
			gotoxy(T1X + 1, T1Y - 1);
			cout << "T1" << "(" << ceil(C.towers[0].Health * 100) / 100 << ")";

			gotoxy(C.Xstrt + C.W / 4, C.Ystrt + C.L / 4);
			cout << "(A)";
		}
		else if (i == 1)
		{
			T2X = C.Xstrt + C.W - 2 - TowerWidth;
			T2Y = T1Y;
			gotoxy(T2X, T2Y);
			for (int i = 0; i<TowerWidth + 1; i++)
				cout << "=";
			gotoxy(T2X + 1, T2Y - 1);
			cout << "T2" << "(" << ceil(C.towers[1].Health * 100) / 100 << ")";
			gotoxy(C.Xstrt + (3 * C.W / 4), C.Ystrt + C.L / 4);
			cout << "(B)";
		}
		else if (i == 2)
		{
			T3X = T2X;
			T3Y = C.Ystrt + C.L - TowerLength - 1;;
			gotoxy(T3X, T3Y);
			for (int i = 0; i<TowerWidth + 1; i++)
				cout << "=";
			gotoxy(T3X + 1, T3Y + 1);
			cout << "T3" << "(" << ceil(C.towers[2].Health * 100) / 100 << ")";
			gotoxy(C.Xstrt + (3 * C.W / 4), C.Ystrt + (3 * C.L / 4) - 1);
			cout << "(C)";

		}
		else
		{
			T4X = T1X;
			T4Y = C.Ystrt + C.L - TowerLength - 1;
			gotoxy(T4X, T4Y);
			for (int i = 0; i<TowerWidth; i++)
				cout << "=";
			gotoxy(T4X + 1, T4Y + 1);
			cout << "T4" << "(" << ceil(C.towers[3].Health * 100) / 100 << ")";
			gotoxy(C.Xstrt + (C.W / 4), C.Ystrt + (3 * C.L / 4) - 1);
			cout << "(D)";

		}
	}


	DrawRegions(C);

	//****************************
	gotoxy(CmdWidth / 2 - 10, CmdHeight - 1);
	cout << "Simulation Time : " << SimulationTime << endl;
}
//A function to draw a single enemy using its distance from the castle
void DrawEnemy(const enemy& E, int Ypos)
{
	int x, y;
	//First calcuale x,y position of the enemy on the output screen
	//It depends on the region and the enemy distance
	REGION EnemyRegion = E.Region;
	switch (EnemyRegion)
	{
	case A_REG:
		x = CastleXStrt - E.Distance + 1;
		y = (CmdHeight / 2) - (CastleLength / 4) - Ypos;
		break;
	case B_REG:
		x = CastleXStrt + CastleWidth + E.Distance - 1;
		y = (CmdHeight / 2) - (CastleLength / 4) - Ypos;
		break;
	case C_REG:
		x = CastleXStrt + CastleWidth + E.Distance - 1;
		y = (CmdHeight / 2) + (CastleLength / 4) + Ypos;
		break;
	default:
		x = CastleXStrt - E.Distance + 1;
		y = (CmdHeight / 2) + (CastleLength / 4) + Ypos;

	}

	gotoxy(x, y);

	//set enemy color according to it type
	Etype EnemyType = E.Type;
	switch (EnemyType)
	{
	case PVR:
		color(FOREGROUND_GREEN);
		break;
	case FITR:
		color(FOREGROUND_RED | FOREGROUND_GREEN);//Yellow
		break;
	default:
		color(FOREGROUND_RED);
	}


	cout << (char)EnemyShape; //Draw the enemy

	color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
//A function to draw a list of enemies and ensure there is no overflow in the drawing
void DrawEnemies(enemy* enemies[], int size)
{
	//draw enemies at each region 
	for (int region = A_REG; region <= D_REG; region++)
	{
		int CountEnemies = 0;	//count Enemies at the same distance to draw them vertically if they are <= 15 enemy else print number of enemy in the region
		bool draw = true;
		for (int distance = ((CmdWidth / 2) - (CastleWidth / 2)); distance>1; distance--)
		{
			CountEnemies = 0;

			for (int i = 0; i<size; i++)
			{
				if (enemies[i]->Distance == distance && enemies[i]->Region == region)
				{
					CountEnemies++;
				}
			}
			if (CountEnemies>15)
			{
				draw = false;
				break;
			}
		}
		if (draw)
		{
			for (int distance = ((CmdWidth / 2) - (CastleWidth / 2)); distance>1; distance--)
			{
				CountEnemies = 0;

				for (int i = 0; i<size; i++)
				{
					if (enemies[i]->Distance == distance && enemies[i]->Region == region)
					{
						DrawEnemy(*(enemies[i]), CountEnemies);
						CountEnemies++;
					}
				}

			}


		}
		else // print message maximum reached in this region
		{
			int x; int y;
			if (region == A_REG)
			{
				x = CastleXStrt - 30;
				y = (CmdHeight / 2) - (CastleLength / 4);
			}
			else if (region == B_REG)
			{
				x = CastleXStrt + CastleWidth + 30;
				y = (CmdHeight / 2) - (CastleLength / 4);


			}
			else if (region == C_REG)
			{
				x = CastleXStrt + CastleWidth + 30;
				y = (CmdHeight / 2) + (CastleLength / 4);

			}
			else
			{
				x = CastleXStrt - 30;
				y = (CmdHeight / 2) + (CastleLength / 4);

			}
			gotoxy(x, y);
			cout << "Maximum limit";
		}

	}
	gotoxy(0, CmdHeight - 1);
}
//Use this function to print a message, statistics to the user
void PrintMsg(char*msg)
{
	cout << msg;
}

//Simulation
void SimulationFn()
{
	castle ct; // define a castle 
	int mode;
	cout << "Choose a mode: " << endl;
	cin >> mode; //Choose the mode
	ct.Xstrt = CastleXStrt;
	ct.Ystrt = CastleYStrt;
	ct.W = CastleWidth;
	ct.L = CastleLength;
	float c1, c2, c3;
	Queue *Inactive_list;
	list *Act_LA, *Act_LB, *Act_LC, *Act_LD;
	CreateList(Act_LA);
	CreateList(Act_LB);
	CreateList(Act_LC);
	CreateList(Act_LD);
	list* Active_lists[] = { Act_LA, Act_LB, Act_LC, Act_LD };
	CreateQueue(Inactive_list);
	int Total_Fight_Delay = 0;
	int Total_Kill_Delay = 0;
	int EnemiesShot[4];
	LoadingFunction(ct, c1, c2, c3, Inactive_list);
	int Total_enemies = Inactive_list->count;
	enemy **ActiveEnemies = new enemy *[Total_enemies];
	int TimeStep = 1;
	int count = 0;
	GraphicsAndModes(Active_lists, mode, ct.towers, ActiveEnemies, count, ct, TimeStep);
	out << "T    S    FD   KD   FT" << endl;

	// Simulation
	while (TimeStep != -1)
	{
		count = 0; //counter for array of pointers
		//Move enemies from inactive to active list
		Node *temp = Inactive_list->front;
		while (temp != NULL)
		{
			if (temp->e.Tarrival == TimeStep)
			{
				temp = temp->next;
				MoveInAct(Inactive_list, Act_LA, Act_LB, Act_LC, Act_LD, ct.towers);
			}
			else temp = NULL;
		}

		for (int i = 0; i < 4; i++)
			ListToArrayptr(Active_lists[i], ActiveEnemies, count);

		//Fighting
		for (int i = 0; i < 4; i++)
		{
			ShootAtTower(Active_lists[i], ct.towers[i], TimeStep);
			EnemiesShot[i] = ShootAtEnemy(ct.towers[i], Active_lists[i], TimeStep, Total_Fight_Delay, c1, c2, c3);
			MoveAndPave(Active_lists[i], TimeStep, ct.towers[i]);
			Calculations(Active_lists[i], ct.towers[i], EnemiesShot[i]);
		}

		//Check if enemy is killed
		Kill(Active_lists, ct.towers, TimeStep, Total_Kill_Delay);

		//Drawing
		GraphicsAndModes(Active_lists, mode, ct.towers, ActiveEnemies, count, ct, TimeStep);

		//Check if tower is destroyed and move enemies to adjacent region
		for (int i = 0; i < 4; i++)
		if (ct.towers[i].Health <= 0)
			MoveToAdjacent(ct.towers, i, Active_lists, ct);

		//Check if game win or loss
		bool Win = GameWin(ct, Total_enemies);
		bool Loss = GameLoss(ct);
		if (GameWin(ct, Total_enemies) || GameLoss(ct))
		{
			OutputFile(ct.towers, Win, Loss, Total_Kill_Delay, Total_Fight_Delay, Active_lists, TimeStep);
			TimeStep = -1;
		}
		else TimeStep++;
	}

	//Deallocate array of pointers and active lists
	delete[] ActiveEnemies;
	delete Act_LA;
	delete Act_LB;
	delete Act_LC;
	delete Act_LD;
	out.close();
}

