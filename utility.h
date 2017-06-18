#include <iostream>
using namespace std;
#include <windows.h>

//The four regions: A, B, C , and D
enum REGION {
	A_REG,
	B_REG,
	C_REG,
	D_REG
};

//Enemy types: Paver, Fighter, and Shielded Fighter
enum Etype {
	PVR,
	FITR,
	SHLD_FITR
};


//constants
#define CmdWidth		150
#define CmdHeight		50
#define CastleWidth		30
#define CastleLength	20
#define CastleXStrt		(CmdWidth/2-(CastleWidth/2))
#define CastleYStrt		(CmdHeight/2-(CastleLength/2))
#define TowerWidth      7
#define TowerLength     3
#define EnemyShape		219  //ASCII code of enemy char shape 



//Tower
struct Tower
{
	int TW; //Tower width
	int TL; //Tower Height
	float Health;
	int TP; //Fire power
	int N;  //Maximum number of ennemies
	float Total_Damage;  //Total damage caused by enemies in the game
	float Current_Damage; //Damage caused by enemies in one time step
	int Paved_Distance;  //paved distance by enemies
	int KillCount;  //No. of killed enemies 
	int CurrentKillCount;
	int ShieldedCount;  //No. of shielded enemies
};
struct castle
{
	//starting x,y
	int Xstrt;
	int Ystrt;
	int W;	            //width
	int L;              //Height
	Tower towers[4];	//Castle has 4 towers
};
struct enemy
{
	int ID;			//Each enemy has a unique ID (sequence number)
	REGION Region;	//Region of this enemy
	int Distance;	//Distance to the castle
	float Health;	//Enemy health
	Etype Type;		//PVR, FITR, SHLD_FITR
	int Tarrival;   //arrival time
	int Fire_power; //fire power
	int Reload_period; //Reload period
	int TKill;         //Time killed at
	int Fight_Delay;   //Fight delay
	int Kill_Delay;    //Kill delay
	int Total_fight_time;    //Total fight time
	float DamageE;  //Damage caused by tower 
	int Tfirst_shot;  //first shot by the tower
	float Priority;
	int velocity;
};

//Structures for functions
struct Node
{
	enemy e;
	Node *next;
};
struct list
{
	Node *head;
	int count;
};
struct Queue
{
	Node *rear;
	Node *front;
	int count;
};

//Prototype of functions
//Function to load input file
void LoadingFunction(castle &ct, float &c1, float &c2, float &c3, Queue *&Q);
//Functions to check Full or Empty lists
bool IsFull();
bool IsEmptyQueue(Queue *q);
bool IsEmptyList(list *L);
//Queues Functions
void CreateQueue(Queue *&q);
bool Enqueue(Queue *&q, enemy e);
bool Dequeue(Queue *&q, enemy &edeleted);
//Linked list Functions
void CreateList(list *&Lhead);
bool InsertBeg(list *&L, enemy e);
bool InsertEnd(list *&L, enemy e);
bool DeleteFirst(list*& L, enemy & edeleted);
bool DeleteMid(list *&L, int IDK, enemy &edeleted);
//Functions to change from enum <-> character
REGION CharToEnum(char RegionTemp);
//Functions Sorting
void InsertionSortLinkedList(list*&L);
void MergeSorted(Node*p1, Node* p2, list*&Merged);
void BubbleSort(enemy x[], int n);
//Simulation Functions
bool MoveInAct(Queue *&Q, list *&LA, list *&LB, list *&LC, list *&LD, Tower Towers[]);    //Function to move from inactive list to active list
bool IsReloading(enemy e, int TimeStep, int &remaining_time);
bool ShootAtTower(list *&Active_list, Tower& T, int TimeStep);
int ShootAtEnemy(Tower &tower, list*&Active, int TimeStep, int &TotalFightDelay, float c1, float c2, float c3);
bool IsPaved(int PavedDistance, int enemyDistance);  //function to check is distance paved or not
bool MoveAndPave(list*&Active_list, int TimeStep, Tower &tower);  //Function to move enemies
void ListToArrayptr(list *Activelists, enemy *Activenemies[], int &count);
int FindAdjacent(int iKilledTower, Tower Towerarr[]);
void MoveToAdjacent(Tower Towerarr[], int iKilledTower, list *ActiveLists[], castle ct);
void Kill(list*Active_list[], Tower towers[], int TimeStep, int &tTotal_Fight_Delay);
void Calculations(list*& Active_list, Tower &tower, int EnemiesShot);
void GraphicsAndModes(list*Active_list[], int mode, Tower Towers[], enemy *ActiveEnemies[], int count, castle ct, int TimeStep);
void OutputFile(Tower towers[], bool GameWin, bool GameLoss, int TotalKillDelay, int TotalFightDelay, list*Active_list[], int TimeStep);
bool GameWin(castle c, int Total_Enemies);
bool GameLoss(castle ct);
void SimulationFn();
//Functions Prototype
//A function to set the position of cursor on the screen
void gotoxy(int x, int y);
//A function to set the command window lenght and height for the game specification
void SetWindow();
//A function to color the cmd text
void color(int thecolor);
//A function to partition the castle into regions (A,B,C,D)
void DrawRegions(const castle & C);
//A function to draw the castle and the towers
void DrawCastle(const castle & C, int SimulationTime);
//A function to draw a single enemy using its distance from the castle
void DrawEnemy(const enemy& E, int Ypos = 0);
//A function to draw a list of enemies exist in all regions and ensure there is no overflow in the drawing
void DrawEnemies(enemy* enemies[], int size);
//Student use this function to print his/her message
void PrintMsg(char*msg);

