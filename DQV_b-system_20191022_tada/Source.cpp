#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>

//#define printf //

char playerName[][5 * 2 + 1] =
{
	" 主人公 ",
	"ビアンカ",
	"レックス",
	" タバサ ",
};

char enemyName[][5 * 2 + 1] =
{
	"エスターク"
};

enum commandFirst
{
	COMMAND_ATTACK,
	COMMAND_SPELL,
	COMMAND_TOOL,
	COMMAND_MAX
};
char commandFirst[][4 * 2 + 1] =
{
	"こうげき",		//COMMAND_ATTACK
	"じゅもん",		//COMMAND_SPELL
	"　どうぐ",		//COMMAND_TOOL
};

enum detailSpell1
{
	SPELL1_HOIMI,
	SPELL1_KIARI,
	SPELL1_BAGI,
	SPELL1_SUKARA,
	SPELL1_BEHOIMI,
	SPELL1_BAGIMA,
	SPELL1_BEHOMA,
	SPELL1_ZAORARU,
	SPELL1_MEGAZARU,
	SPELL1_BAGIKUROSU,
	SPELL1_MAX
};
char detailSpell1[][8 * 2 + 1] =
{
	"　　ホイミ(3)",		//0
	"　キアリー(2)",		//1
	"　　　バギ(2)",		//2　
	"　　スカラ(2)",		//3
	"　ベホイミ(5)",		//4
	"　　バギマ(4)",		//5
	"　  ベホマ(7)",		//6
	" ザオラル(10)",		//7
	"メガザル(all)",		//8
	"バギクロス(8)"			//9
};
//Spellの消費MP
int SpellMP1[10] = { 3,2,2,2,5,4,7,0,10,8 };
//0,1,3,4,6,7番のスペルは対象を選ぶ
bool SelectTargetSpell1[10] = { true,true,false,true,true,false,true,true,false,false };

enum detailSpell2
{
	SPELL2_MERA,
	SPELL2_GIRA,
	SPELL2_BAIKIRUTO,
	SPELL2_BEGIRAMA,
	SPELL2_MERAMI,
	SPELL2_BEGIRAGON,
	SPELL2_MERAZOMA,
	SPELL2_MAX
};
char detailSpell2[][8 * 2 + 1]
{
	"　　　 メラ(2)",		//0
	"　　　 ギラ(4)",		//1
	" バイキルト(6)",		//2
	"　 ベギラマ(6)",		//3
	"　　 メラミ(4)",		//4
	"ベギラゴン(10)",		//5
	"メラゾーマ(10)",		//6
};
//Spellの消費MP
int SpellMP2[10] = { 2,4,6,6,4,10,10 };
//すべて対象を選ばない
bool SelectTargetSpell2[10] = { false,false,true,false,false,false,false };

enum detailSpell3
{
	SPELL3_SUKURUTO,
	SPELL3_BEHOIMI,
	SPELL3_KIARIKU,
	SPELL3_BEHOMA,
	SPELL3_FUBAHA,
	SPELL3_RAIDEIN,
	SPELL3_ZAORIKU,
	SPELL3_BEHOMARA,
	SPELL3_GIGADEIN,
	SPELL3_MINADEIN,
	SPELL3_MAX
};
char detailSpell3[][8 * 2 + 1]
{
	"　 　スクルト(3)",		//0
	"　 　ベホイミ(5)",		//1
	"　 　キアリク(2)",		//2
	"　　 　ベホマ(7)",		//3
	"　 　フバーハ(3)",		//4
	" 　ライデイン(6)",		//5
	"　　ザオリク(20)",		//6
	"　ベホマラー(18)",		//7
	"　ギガデイン(15)",		//8
	"ミナデイン(ev10)"		//9
};
//Spellの消費MP
int SpellMP3[10] = { 3,5,2,7,3,6,20,18,15,10 };
//1,4,7番のスペルは対象を選ぶ
bool SelectTargetSpell3[10] = { false,true,false,true,false,false,true,false,false,false };

enum detailSpell4
{
	SPELL4_HYADO,
	SPELL4_IO,
	SPELL4_HYADARUKO,
	SPELL4_BAIKIRUTO,
	SPELL4_RUKANAN,
	SPELL4_IORA,
	SPELL4_MAHYADO,
	SPELL4_DORAGORAMU,
	SPELL4_IONAZUN,
	SPELL4_MAX
};
char detailSpell4[][8 * 2 + 1]
{
	"　　 ヒャド(3)",		//0
	"　　　 イオ(5)",		//1
	" ヒャダルコ(5)",		//2
	" バイキルト(6)",		//3
	"　 ルカナン(4)",		//4
	"　　 イオラ(8)",		//5
	"　マヒャド(12)",		//6
	"ドラゴラム(18)",		//7
	"イオナズン(15)"		//8
};
//Spellの消費MP
int SpellMP4[10] = { 3,5,5,6,4,8,12,18,15 };
//3番のスペルは対象を選ぶ
bool SelectTargetSpell4[10] = { false,false,false,true,false,false,false,false,false };

enum spell_targetName
{
	NAME_PLAYER1,
	NAME_PLAYER2,
	NAME_PLAYER3,
	NAME_PLAYER4,
	NAME_MAX
};
char spell_targetName[][5 * 2 + 1] =
{
	"　主人公",
	"ビアンカ",
	"レックス",
	"　タバサ"
};


typedef struct
{
	char(*name)[8 * 2 + 1];
	int *mp;
	bool* isSelectTarget;
	int size;
}SpellData;



enum contentTool
{
	CONTENT_DORUM,
	CONTENT_MAX
};
char contentTool[][10 * 2 + 1] =
{
	"　たたかいのドラム"
};



typedef struct
{
	int base_strength;	//力
	int agility;		//素早さ
	int base_endurance;	//身の守り
	int maxHP;			//maxHP
	int maxMP;			//maxMP

	bool poison;		//毒
	bool paralysis;		//麻痺
	bool sleep;			//眠り
	bool can_action;	//このターン行動可能かどうか
	bool dragon;		//ドラゴンフラグ

	int strength;			//現在の力
	int endurance;			//現在の身の守り
	int attack;				//攻撃力
	int defense;			//守備力
	int HP;					//現在のHP
	int MP;					//現在のMP
	int action;				//行動
	int action_spell;		//呪文詳細
	int action_spell_target;//呪文対象
	int action_tool;		//道具内容
	SpellData spells;
}CHARACTER;

CHARACTER statusTable[] =
{
	//力，素早さ，身の守り，maxHP，maxMP
	{ 149, 102,	45,	340, 170 },		//主人公・現在ステータス
{ 55, 120,	68,	291, 290 },		//ビアンカ・現在ステータス
{ 123,	95,	50,	324, 180 },		//レックス・現在ステータス
{ 50, 115,	75,	271, 190 },		//タバサ・現在ステータス
{ 450,  85,250,9000 }		//エスターク・ステータス
};

int command;		// 最初のコマンド
int detail;			// 呪文詳細コマンド
int content;		// 道具内容コマンド
int p_turn;			// プレイヤー・ターン
int e_turn;			// エネミー・ターン
int spell_target;	// 呪文対象

					//display表示（メイン）
void display()
{
	system("cls");
	printf
	(
		"＋―%s―＋\n"
		"｜ レベル　45 ｜\n"
		"｜ ＨＰ　%4d ｜\n"
		"｜ ＭＰ　%4d ｜\n"
		"＋-―――――-＋\n\n"

		"＋―%s―＋\n"
		"｜ レベル　45 ｜\n"
		"｜ ＨＰ　%4d ｜\n"
		"｜ ＭＰ　%4d ｜\n"
		"＋-―――――-＋\n\n"

		"＋―%s―＋\n"
		"｜ レベル　45 ｜\n"
		"｜ ＨＰ　%4d ｜\n"
		"｜ ＭＰ　%4d ｜\n"
		"＋-―――――-＋\n\n"

		"＋―%s―＋\n"
		"｜ レベル　45 ｜\n"
		"｜ ＨＰ　%4d ｜\n"
		"｜ ＭＰ　%4d ｜\n"
		"＋-―――――-＋\n\n"
		,
		playerName[0],
		statusTable[0].HP,
		statusTable[0].MP
		,
		playerName[1],
		statusTable[1].HP,
		statusTable[1].MP
		,
		playerName[2],
		statusTable[2].HP,
		statusTable[2].MP
		,
		playerName[3],
		statusTable[3].HP,
		statusTable[3].MP
	);
}

//display表示（MP不足）
void display_mp()
{
	printf("＋―――――――――――――――――＋\n");
	printf("｜MPがたりない　　　　　　　　　　　｜\n");
	printf("＋―――――――――――――――――＋\n");
}

// 毒フラグ
//bool statusTable[0].poison = 0;
//bool statusTable[1].poison = 0;
//bool statusTable[2].poison = 0;
//bool statusTable[3].poison = 0;

int player_num = 4;
void status_poison()
{
	for (int i = 0; i < player_num; i++)
	{
		if (statusTable[i].poison)
		{
			statusTable[i].HP -= (statusTable[i].maxHP / 6);
			printf("＋――――――――――――――――――――＋\n");
			printf("｜%sは毒によるダメージを受けた　　　　　　｜\n", playerName[i]);
			printf("＋――――――――――――――――――――＋\n");
		}
	}
}



int get_input(int limit)
{
	int ch;
	while (1) {
		ch = _getch();
		if (ch == 0x0d) {
			return -1;
		}
		if (ch - '1' < limit && ch - '1' >= 0)break;
		if (ch == '0')return 9;
	}
	return ch - '1';
}

bool status_break()
{
	return false;
}
// 休み状態（眠り or 麻痺）
/*
void player1_status_break()
{
srand((unsigned)time(NULL));	//時間によって，実行系列を変更
int r = rand();
int count = 0;					// 休んでから経過したターン
if (statusTable[0].sleep == 1)
{
if (count == 2)
{
switch (rand() % 2)
{
case 0:		break;
default:
count = 0;
statusTable[0].sleep = 0;
printf("＋――――――――――――――――――――＋\n");
printf("｜%sは目を覚ました　　　　　　　　　　　　｜\n", playerName[0]);
printf("＋――――――――――――――――――――＋\n");
break;
}
}
else if (count == 3)
{
switch (rand() % 3)
{
case 0:		break;
default:
count = 0;
statusTable[0].sleep = 0;
printf("＋――――――――――――――――――――＋\n");
printf("｜%sは目を覚ました　　　　　　　　　　　　　｜\n", playerName[0]);
printf("＋――――――――――――――――――――＋\n");
break;
}
}
else if (count == 4)
{
switch (rand() % 4)
{
case 0:		break;
default:
count = 0;
statusTable[0].sleep = 0;
printf("＋――――――――――――――――――――＋\n");
printf("｜%sは目を覚ました　　　　　　　　　　　　　｜\n", playerName[0]);
printf("＋――――――――――――――――――――＋\n");
break;
}
}
else if (count == 5)
{
count = 0;
statusTable[0].sleep = 0;
printf("＋――――――――――――――――――――＋\n");
printf("｜%sは目を覚ました　　　　　　　　　　　　　｜\n", playerName[0]);
printf("＋――――――――――――――――――――＋\n");
}
if (statusTable[0].sleep == 1)
{
printf("＋――――――――――――――――――――＋\n");
printf("｜%sは眠っている　　　　　　　　　　　　　｜\n", playerName[0]);
printf("＋――――――――――――――――――――＋\n");
count++;
}
}
if (statusTable[0].paralysis == 1)
{
if (count == 5)
{
switch (rand() % 2)
{
case 0:		break;
default:
count = 0;
statusTable[0].paralysis = 0;
printf("＋――――――――――――――――――――＋\n");
printf("｜%sの麻痺が解けた　　　　　　　　　　　　｜\n", playerName[0]);
printf("＋――――――――――――――――――――＋\n");
break;
}
}
else if (count == 6)
{
switch (rand() % 3)
{
case 0:		break;
default:
count = 0;
statusTable[0].paralysis = 0;
printf("＋――――――――――――――――――――＋\n");
printf("｜%sの麻痺が解けた　　　　　　　　　　　　　｜\n", playerName[0]);
printf("＋――――――――――――――――――――＋\n");
break;
}
}
else if (count == 7)
{
switch (rand() % 4)
{
case 0:		break;
default:
count = 0;
statusTable[0].paralysis = 0;
printf("＋――――――――――――――――――――＋\n");
printf("｜%sの麻痺が解けた　　　　　　　　　　　　　｜\n", playerName[0]);
printf("＋――――――――――――――――――――＋\n");
break;
}
}
else if (count == 8)
{
count = 0;
statusTable[0].paralysis = 0;
printf("＋――――――――――――――――――――＋\n");
printf("｜%sの麻痺が解けた　　　　　　　　　　　　　｜\n", playerName[0]);
printf("＋――――――――――――――――――――＋\n");
}
if (statusTable[0].paralysis == 1)
{
printf("＋――――――――――――――――――――＋\n");
printf("｜%sは麻痺している　　　　　　　　　　　　｜\n", playerName[0]);
printf("＋――――――――――――――――――――＋\n");
count++;
}
}
}
void player2_status_break()
{
srand((unsigned)time(NULL));	//時間によって，実行系列を変更
int r = rand();
int count = 0;					// 休んでから経過したターン
if (statusTable[1].sleep == 1)
{
if (count == 2)
{
switch (rand() % 2)
{
case 0:		break;
default:
count = 0;
statusTable[1].sleep = 0;
printf("＋――――――――――――――――――――＋\n");
printf("｜%sは目を覚ました　　　　　　　　　　　　　｜\n", playerName[1]);
printf("＋――――――――――――――――――――＋\n");
break;
}
}
else if (count == 3)
{
switch (rand() % 3)
{
case 0:		break;
default:
count = 0;
statusTable[1].sleep = 0;
printf("＋――――――――――――――――――――＋\n");
printf("｜%sは目を覚ました　　　　　　　　　　　　　｜\n", playerName[1]);
printf("＋――――――――――――――――――――＋\n");
break;
}
}
else if (count == 4)
{
switch (rand() % 4)
{
case 0:		break;
default:
count = 0;
statusTable[1].sleep = 0;
printf("＋――――――――――――――――――――＋\n");
printf("｜%sは目を覚ました　　　　　　　　　　　　　｜\n", playerName[1]);
printf("＋――――――――――――――――――――＋\n");
break;
}
}
else if (count == 5)
{
count = 0;
statusTable[1].sleep = 0;
printf("＋――――――――――――――――――――＋\n");
printf("｜%sは目を覚ました　　　　　　　　　　　　　｜\n", playerName[1]);
printf("＋――――――――――――――――――――＋\n");
}
if (statusTable[1].sleep == 1)
{
printf("＋――――――――――――――――――――＋\n");
printf("｜%sは眠っている　　　　　　　　　　　　　｜\n", playerName[1]);
printf("＋――――――――――――――――――――＋\n");
count++;
}
}
if (statusTable[1].paralysis == 1)
{
if (count == 5)
{
switch (rand() % 2)
{
case 0:		break;
default:
count = 0;
statusTable[1].paralysis = 0;
printf("＋――――――――――――――――――――＋\n");
printf("｜%sの麻痺が解けた　　　　　　　　　　　　｜\n", playerName[1]);
printf("＋――――――――――――――――――――＋\n");
break;
}
}
else if (count == 6)
{
switch (rand() % 3)
{
case 0:		break;
default:
count = 0;
statusTable[1].paralysis = 0;
printf("＋――――――――――――――――――――＋\n");
printf("｜%sの麻痺が解けた　　　　　　　　　　　　　｜\n", playerName[1]);
printf("＋――――――――――――――――――――＋\n");
break;
}
}
else if (count == 7)
{
switch (rand() % 4)
{
case 0:		break;
default:
count = 0;
statusTable[1].paralysis = 0;
printf("＋――――――――――――――――――――＋\n");
printf("｜%sの麻痺が解けた　　　　　　　　　　　　　｜\n", playerName[1]);
printf("＋――――――――――――――――――――＋\n");
break;
}
}
else if (count == 8)
{
count = 0;
statusTable[1].paralysis = 0;
printf("＋――――――――――――――――――――＋\n");
printf("｜%sの麻痺が解けた　　　　　　　　　　　　　｜\n", playerName[1]);
printf("＋――――――――――――――――――――＋\n");
}
if (statusTable[1].paralysis == 1)
{
printf("＋――――――――――――――――――――＋\n");
printf("｜%sは麻痺している　　　　　　　　　　　　｜\n", playerName[1]);
printf("＋――――――――――――――――――――＋\n");
count++;
}
}
}
void player3_status_break()
{
srand((unsigned)time(NULL));	//時間によって，実行系列を変更
int r = rand();
int count = 0;					// 休んでから経過したターン
if (statusTable[2].sleep == 1)
{
if (count == 2)
{
switch (rand() % 2)
{
case 0:		break;
default:
count = 0;
statusTable[2].sleep = 0;
printf("＋――――――――――――――――――――＋\n");
printf("｜%sは目を覚ました　　　　　　　　　　　　　｜\n", playerName[2]);
printf("＋――――――――――――――――――――＋\n");
break;
}
}
else if (count == 3)
{
switch (rand() % 3)
{
case 0:		break;
default:
count = 0;
statusTable[2].sleep = 0;
printf("＋――――――――――――――――――――＋\n");
printf("｜%sは目を覚ました　　　　　　　　　　　　　｜\n", playerName[2]);
printf("＋――――――――――――――――――――＋\n");
break;
}
}
else if (count == 4)
{
switch (rand() % 4)
{
case 0:		break;
default:
count = 0;
statusTable[2].sleep = 0;
printf("＋――――――――――――――――――――＋\n");
printf("｜%sは目を覚ました　　　　　　　　　　　　　｜\n", playerName[2]);
printf("＋――――――――――――――――――――＋\n");
break;
}
}
else if (count == 5)
{
count = 0;
statusTable[2].sleep = 0;
printf("＋――――――――――――――――――――＋\n");
printf("｜%sは目を覚ました　　　　　　　　　　　　　｜\n", playerName[2]);
printf("＋――――――――――――――――――――＋\n");
}
if (statusTable[2].sleep == 1)
{
printf("＋――――――――――――――――――――＋\n");
printf("｜%sは眠っている　　　　　　　　　　　　　｜\n", playerName[2]);
printf("＋――――――――――――――――――――＋\n");
count++;
}
}
if (statusTable[2].paralysis == 1)
{
if (count == 5)
{
switch (rand() % 2)
{
case 0:		break;
default:
count = 0;
statusTable[2].paralysis = 0;
printf("＋――――――――――――――――――――＋\n");
printf("｜%sの麻痺が解けた　　　　　　　　　　　　｜\n", playerName[2]);
printf("＋――――――――――――――――――――＋\n");
break;
}
}
else if (count == 6)
{
switch (rand() % 3)
{
case 0:		break;
default:
count = 0;
statusTable[2].paralysis = 0;
printf("＋――――――――――――――――――――＋\n");
printf("｜%sの麻痺が解けた　　　　　　　　　　　　　｜\n", playerName[2]);
printf("＋――――――――――――――――――――＋\n");
break;
}
}
else if (count == 7)
{
switch (rand() % 4)
{
case 0:		break;
default:
count = 0;
statusTable[2].paralysis = 0;
printf("＋――――――――――――――――――――＋\n");
printf("｜%sの麻痺が解けた　　　　　　　　　　　　　｜\n", playerName[2]);
printf("＋――――――――――――――――――――＋\n");
break;
}
}
else if (count == 8)
{
count = 0;
statusTable[2].paralysis = 0;
printf("＋――――――――――――――――――――＋\n");
printf("｜%sの麻痺が解けた　　　　　　　　　　　　　｜\n", playerName[2]);
printf("＋――――――――――――――――――――＋\n");
}
if (statusTable[2].paralysis == 1)
{
printf("＋――――――――――――――――――――＋\n");
printf("｜%sは麻痺している　　　　　　　　　　　　｜\n", playerName[2]);
printf("＋――――――――――――――――――――＋\n");
count++;
}
}
}
void player4_status_break()
{
srand((unsigned)time(NULL));	//時間によって，実行系列を変更
int r = rand();
int count = 0;					// 休んでから経過したターン
if (statusTable[3].sleep == 1)
{
if (count == 2)
{
switch (rand() % 2)
{
case 0:		break;
default:
count = 0;
statusTable[3].sleep = 0;
printf("＋――――――――――――――――――――＋\n");
printf("｜%sは目を覚ました　　　　　　　　　　　　　｜\n", playerName[3]);
printf("＋――――――――――――――――――――＋\n");
break;
}
}
else if (count == 3)
{
switch (rand() % 3)
{
case 0:		break;
default:
count = 0;
statusTable[3].sleep = 0;
printf("＋――――――――――――――――――――＋\n");
printf("｜%sは目を覚ました　　　　　　　　　　　　　｜\n", playerName[3]);
printf("＋――――――――――――――――――――＋\n");
break;
}
}
else if (count == 4)
{
switch (rand() % 4)
{
case 0:		break;
default:
count = 0;
statusTable[3].sleep = 0;
printf("＋――――――――――――――――――――＋\n");
printf("｜%sは目を覚ました　　　　　　　　　　　　　｜\n", playerName[3]);
printf("＋――――――――――――――――――――＋\n");
break;
}
}
else if (count == 5)
{
count = 0;
statusTable[3].sleep = 0;
printf("＋――――――――――――――――――――＋\n");
printf("｜%sは目を覚ました　　　　　　　　　　　　　｜\n", playerName[3]);
printf("＋――――――――――――――――――――＋\n");
}
if (statusTable[3].sleep == 1)
{
printf("＋――――――――――――――――――――＋\n");
printf("｜%sは眠っている　　　　　　　　　　　　　｜\n", playerName[3]);
printf("＋――――――――――――――――――――＋\n");
count++;
}
}
if (statusTable[1].paralysis == 1)
{
if (count == 5)
{
switch (rand() % 2)
{
case 0:		break;
default:
count = 0;
statusTable[3].paralysis = 0;
printf("＋――――――――――――――――――――＋\n");
printf("｜%sの麻痺が解けた　　　　　　　　　　　　｜\n", playerName[3]);
printf("＋――――――――――――――――――――＋\n");
break;
}
}
else if (count == 6)
{
switch (rand() % 3)
{
case 0:		break;
default:
count = 0;
statusTable[3].paralysis = 0;
printf("＋――――――――――――――――――――＋\n");
printf("｜%sの麻痺が解けた　　　　　　　　　　　　｜\n", playerName[3]);
printf("＋――――――――――――――――――――＋\n");
break;
}
}
else if (count == 7)
{
switch (rand() % 4)
{
case 0:		break;
default:
count = 0;
statusTable[3].paralysis = 0;
printf("＋――――――――――――――――――――＋\n");
printf("｜%sの麻痺が解けた　　　　　　　　　　　　　｜\n", playerName[3]);
printf("＋――――――――――――――――――――＋\n");
break;
}
}
else if (count == 8)
{
count = 0;
statusTable[3].paralysis = 0;
printf("＋――――――――――――――――――――＋\n");
printf("｜%sの麻痺が解けた　　　　　　　　　　　　　｜\n", playerName[3]);
printf("＋――――――――――――――――――――＋\n");
}
if (statusTable[3].paralysis == 1)
{
printf("＋――――――――――――――――――――＋\n");
printf("｜%sは麻痺している　　　　　　　　　　　　｜\n", playerName[3]);
printf("＋――――――――――――――――――――＋\n");
count++;
}
}
}
*/

int bless = 1;		// フバーハによるbless減少率

// 呪文
void spell()
{
	srand((unsigned)time(NULL));	//時間によって，実行系列を変更
	int cureMin;
	int cureMax;
	int cure;
	int m_damageMin;
	int m_damageMax;
	int m_damage;
	int keep;

	if (p_turn == 0)
	{
		if (statusTable[0].action == 1)
		{
			if (statusTable[0].action_spell == 0)
			{
				cureMin = 30;
				cureMax = 40;
				cure = cureMin + rand() % (cureMax - cureMin);
				display();
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sはホイミをとなえた　　　｜\n", playerName[0]);
				printf("＋―――――――――――――――――＋\n");
				statusTable[0].MP -= 3;
				statusTable[statusTable[0].action_spell_target].HP += cure;
				if (statusTable[statusTable[0].action_spell_target].HP > statusTable[statusTable[0].action_spell_target].maxHP)
					statusTable[statusTable[0].action_spell_target].HP = statusTable[statusTable[0].action_spell_target].maxHP;
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sはHPが%dかいふくした　｜\n", playerName[statusTable[0].action_spell_target], cure);
				printf("＋―――――――――――――――――＋\n");
				_getch();
			}
			else if (statusTable[0].action_spell == 1)
			{
				display();
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sはキアリーをとなえた　　｜\n", playerName[0]);
				printf("＋―――――――――――――――――＋\n");
				statusTable[0].MP -= 2;
				if (statusTable[0].action_spell_target == 0)
					statusTable[0].poison = 0;
				else if (statusTable[0].action_spell_target == 1)
					statusTable[1].poison = 0;
				else if (statusTable[0].action_spell_target == 2)
					statusTable[2].poison = 0;
				else if (statusTable[0].action_spell_target == 3)
					statusTable[3].poison = 0;
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sのドクをけしさった　　　｜\n", playerName[statusTable[0].action_spell_target]);
				printf("＋―――――――――――――――――＋\n");
				_getch();
			}
			else if (statusTable[0].action_spell == 2)
			{
				m_damageMin = 8;
				m_damageMax = 24;
				m_damage = m_damageMin + rand() % (m_damageMax - m_damageMin);
				display();
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sはバギをとなえた　　　　｜\n", playerName[0]);
				printf("＋―――――――――――――――――＋\n");
				statusTable[0].MP -= 2;
				statusTable[4].HP -= m_damage;
				printf("＋―――――――――――――――――――――――――＋\n");
				printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[0], enemyName[0], m_damage);
				printf("＋―――――――――――――――――――――――――＋\n");
				_getch();
			}
			else if (statusTable[0].action_spell == 3)
			{
				display();
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sはスカラをとなえた　　　｜\n", playerName[0]);
				printf("＋―――――――――――――――――＋\n");
				statusTable[0].MP -= 2;
				if (statusTable[statusTable[0].action_spell_target].endurance >= statusTable[statusTable[0].action_spell_target].base_endurance * 2)
					statusTable[statusTable[0].action_spell_target].endurance = statusTable[statusTable[0].action_spell_target].endurance;
				else
					statusTable[statusTable[0].action_spell_target].endurance += statusTable[statusTable[0].action_spell_target].base_endurance / 2;
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sのみのまもりがあがった　｜\n", playerName[statusTable[0].action_spell_target]);
				printf("＋―――――――――――――――――＋\n");
				_getch();
			}
			else if (statusTable[0].action_spell == 4)
			{
				cureMin = 75;
				cureMax = 95;
				cure = cureMin + rand() % (cureMax - cureMin);
				display();
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sはべホイミをとなえた　　｜\n", playerName[0]);
				printf("＋―――――――――――――――――＋\n");
				statusTable[0].MP -= 5;
				statusTable[statusTable[0].action_spell_target].HP += cure;
				if (statusTable[statusTable[0].action_spell_target].HP > statusTable[statusTable[0].action_spell_target].maxHP)
					statusTable[statusTable[0].action_spell_target].HP = statusTable[statusTable[0].action_spell_target].maxHP;
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sはHPが%dかいふくした　｜\n", playerName[statusTable[0].action_spell_target], cure);
				printf("＋―――――――――――――――――＋\n");
				_getch();
			}
			else if (statusTable[0].action_spell == 5)
			{
				m_damageMin = 25;
				m_damageMax = 55;
				m_damage = m_damageMin + rand() % (m_damageMax - m_damageMin);
				display();
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sはバギマをとなえた　　　｜\n", playerName[0]);
				printf("＋―――――――――――――――――＋\n");
				statusTable[0].MP -= 4;
				statusTable[4].HP -= m_damage;
				printf("＋―――――――――――――――――――――――――＋\n");
				printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[0], enemyName[0], m_damage);
				printf("＋―――――――――――――――――――――――――＋\n");
				_getch();
			}
			else if (statusTable[0].action_spell == 6)
			{
				display();
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sはベホマをとなえた　　　｜\n", playerName[0]);
				printf("＋―――――――――――――――――＋\n");
				statusTable[0].MP -= 7;
				statusTable[statusTable[0].action_spell_target].HP = statusTable[statusTable[0].action_spell_target].maxHP;
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sはHPがぜんかいふくした　｜\n", playerName[statusTable[0].action_spell_target]);
				printf("＋―――――――――――――――――＋\n");
				_getch();
			}
			else if (statusTable[0].action_spell == 7)
			{
				display();
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sはザオラルをとなえた　　｜\n", playerName[0]);
				printf("＋―――――――――――――――――＋\n");
				statusTable[0].MP -= 10;
				if (statusTable[statusTable[0].action_spell_target].HP == 0)
				{
					switch (keep = rand() % 2)
					{
					case 0: statusTable[statusTable[0].action_spell_target].HP = statusTable[statusTable[0].action_spell_target].maxHP / 2;
						break;
					case 1:
						break;
					}
				}
				else if (statusTable[statusTable[0].action_spell_target].HP != 0)
				{
					printf("＋―――――――――――――――――＋\n");
					printf("｜しかし、%sはいきている　　｜\n", playerName[statusTable[0].action_spell_target]);
					printf("＋―――――――――――――――――＋\n");
				}
				if (keep == 0)
				{
					printf("＋―――――――――――――――――＋\n");
					printf("｜%sはいきかえった　　　　　｜\n", playerName[statusTable[0].action_spell_target]);
					printf("＋―――――――――――――――――＋\n");
				}
				else if (keep == 1)
				{
					printf("＋―――――――――――――――――＋\n");
					printf("｜しかし、失敗した　　　　　　　　　｜\n");
					printf("＋―――――――――――――――――＋\n");
				}
				_getch();
			}
			else if (statusTable[0].action_spell == 8)
			{
				display();
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sはメガザルをとなえた　　｜\n", playerName[0]);
				printf("＋―――――――――――――――――＋\n");
				statusTable[0].HP = 0;
				statusTable[0].MP = 0;
				statusTable[1].HP = statusTable[1].maxHP;
				statusTable[2].HP = statusTable[2].maxHP;
				statusTable[3].HP = statusTable[3].maxHP;
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sはMPが0になり死亡した　　｜\n", playerName[0]);
				printf("｜ぜんいんが、かんぜんかいふくした　｜\n");
				printf("＋―――――――――――――――――＋\n");
				_getch();
			}
			else if (statusTable[0].action_spell == 9)
			{
				m_damageMin = 80;
				m_damageMax = 180;
				m_damage = m_damageMin + rand() % (m_damageMax - m_damageMin);
				display();
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sはバギクロスをとなえた　｜\n", playerName[0]);
				printf("＋―――――――――――――――――＋\n");
				statusTable[0].MP -= 8;
				statusTable[4].HP -= m_damage;
				printf("＋―――――――――――――――――――――――――＋\n");
				printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[0], enemyName[0], m_damage);
				printf("＋―――――――――――――――――――――――――＋\n");
				_getch();
			}
		}
	}
	else if (p_turn == 1)
	{
		if (statusTable[1].action == 1)
		{
			if (statusTable[1].action_spell == 0)
			{
				m_damageMin = 12;
				m_damageMax = 15;
				m_damage = m_damageMin + rand() % (m_damageMax - m_damageMin);
				display();
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sはメラをとなえた　　　　｜\n", playerName[1]);
				printf("＋―――――――――――――――――＋\n");
				statusTable[1].MP -= 2;
				statusTable[4].HP -= m_damage;
				printf("＋―――――――――――――――――――――――――＋\n");
				printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[1], enemyName[0], m_damage);
				printf("＋―――――――――――――――――――――――――＋\n");
				_getch();
			}
			else if (statusTable[1].action_spell == 1)
			{
				m_damageMin = 16;
				m_damageMax = 24;
				m_damage = m_damageMin + rand() % (m_damageMax - m_damageMin);
				display();
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sはギラをとなえた　　　　｜\n", playerName[1]);
				printf("＋―――――――――――――――――＋\n");
				statusTable[1].MP -= 4;
				statusTable[4].HP -= m_damage;
				printf("＋―――――――――――――――――――――――――＋\n");
				printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[1], enemyName[0], m_damage);
				printf("＋―――――――――――――――――――――――――＋\n");
				_getch();
			}
			else if (statusTable[1].action_spell == 2)
			{
				display();
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sはバイキルトをとなえた　｜\n", playerName[1]);
				printf("＋―――――――――――――――――＋\n");
				statusTable[1].MP -= 6;
				if (statusTable[statusTable[1].action_spell_target].strength >= statusTable[statusTable[1].action_spell_target].base_strength * 2)
				{
					statusTable[statusTable[1].action_spell_target].strength = statusTable[statusTable[1].action_spell_target].strength;
					printf("＋―――――――――――――――――――――――＋\n");
					printf("｜しかし、%sのちからはもうあがらない　｜\n", playerName[statusTable[1].action_spell_target]);
					printf("＋―――――――――――――――――――――――＋\n");
				}
				else
				{
					statusTable[statusTable[1].action_spell_target].strength *= 2;
					printf("＋―――――――――――――――――＋\n");
					printf("｜%sはちからがばいになった　｜\n", playerName[statusTable[1].action_spell_target]);
					printf("＋―――――――――――――――――＋\n");
				}
				_getch();
			}
			else if (statusTable[1].action_spell == 3)
			{
				m_damageMin = 30;
				m_damageMax = 42;
				m_damage = m_damageMin + rand() % (m_damageMax - m_damageMin);
				display();
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sはベギラマをとなえた　　｜\n", playerName[1]);
				printf("＋―――――――――――――――――＋\n");
				statusTable[1].MP -= 6;
				statusTable[4].HP -= m_damage;
				printf("＋―――――――――――――――――――――――――＋\n");
				printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[1], enemyName[0], m_damage);
				printf("＋―――――――――――――――――――――――――＋\n");
				_getch();
			}
			else if (statusTable[1].action_spell == 4)
			{
				m_damageMin = 70;
				m_damageMax = 90;
				m_damage = m_damageMin + rand() % (m_damageMax - m_damageMin);
				display();
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sはメラミをとなえた　　　｜\n", playerName[1]);
				printf("＋―――――――――――――――――＋\n");
				statusTable[1].MP -= 4;
				statusTable[4].HP -= m_damage;
				printf("＋―――――――――――――――――――――――――＋\n");
				printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[1], enemyName[0], m_damage);
				printf("＋―――――――――――――――――――――――――＋\n");
				_getch();
			}
			else if (statusTable[1].action_spell == 5)
			{
				m_damageMin = 88;
				m_damageMax = 112;
				m_damage = m_damageMin + rand() % (m_damageMax - m_damageMin);
				display();
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sはベギラゴンをとなえた　｜\n", playerName[1]);
				printf("＋―――――――――――――――――＋\n");
				statusTable[1].MP -= 10;
				statusTable[4].HP -= m_damage;
				printf("＋―――――――――――――――――――――――――＋\n");
				printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[1], enemyName[0], m_damage);
				printf("＋―――――――――――――――――――――――――＋\n");
				_getch();
			}
			else if (statusTable[1].action_spell == 6)
			{
				m_damageMin = 180;
				m_damageMax = 200;
				m_damage = m_damageMin + rand() % (m_damageMax - m_damageMin);
				display();
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sはメラゾーマをとなえた　｜\n", playerName[1]);
				printf("＋―――――――――――――――――＋\n");
				statusTable[1].MP -= 2;
				statusTable[4].HP -= m_damage;
				printf("＋―――――――――――――――――――――――――＋\n");
				printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[1], enemyName[0], m_damage);
				printf("＋―――――――――――――――――――――――――＋\n");
				_getch();
			}
		}
	}
	else if (p_turn == 2)
	{
		if (statusTable[2].action == 1)
		{
			if (statusTable[2].action_spell == 0)
			{
				display();
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sはスクルトをとなえた　　｜\n", playerName[2]);
				printf("＋―――――――――――――――――＋\n");
				statusTable[2].MP -= 3;
				if (statusTable[0].endurance >= statusTable[0].base_endurance * 2)
				{
					statusTable[0].endurance = statusTable[0].endurance;
					printf("＋――――――――――――――――――――――――＋\n");
					printf("｜しかし、%sのみのまもりはもうあがらない　｜\n", playerName[0]);
					printf("＋――――――――――――――――――――――――＋\n");
				}
				else
				{
					statusTable[0].endurance *= 6 / 5;
					printf("＋―――――――――――――――――＋\n");
					printf("｜%sのみのまもりがあがった　｜\n", playerName[0]);
					printf("＋―――――――――――――――――＋\n");
				}
				if (statusTable[1].endurance >= statusTable[1].base_endurance * 2)
				{
					statusTable[1].endurance = statusTable[1].endurance;
					printf("＋――――――――――――――――――――――――＋\n");
					printf("｜しかし、%sのみのまもりはもうあがらない　｜\n", playerName[1]);
					printf("＋――――――――――――――――――――――――＋\n");
				}
				else
				{
					statusTable[1].endurance *= 6 / 5;
					printf("＋―――――――――――――――――＋\n");
					printf("｜%sのみのまもりがあがった　｜\n", playerName[1]);
					printf("＋―――――――――――――――――＋\n");
				}
				if (statusTable[2].endurance >= statusTable[2].base_endurance * 2)
				{
					statusTable[2].endurance = statusTable[2].endurance;
					printf("＋――――――――――――――――――――――――＋\n");
					printf("｜しかし、%sのみのまもりはもうあがらない　｜\n", playerName[2]);
					printf("＋――――――――――――――――――――――――＋\n");
				}
				else
				{
					statusTable[0].endurance *= 6 / 5;
					printf("＋―――――――――――――――――＋\n");
					printf("｜%sのみのまもりがあがった　｜\n", playerName[2]);
					printf("＋―――――――――――――――――＋\n");
				}
				if (statusTable[3].endurance >= statusTable[3].base_endurance * 2)
				{
					statusTable[3].endurance = statusTable[3].endurance;
					printf("＋――――――――――――――――――――――――＋\n");
					printf("｜しかし、%sのみのまもりはもうあがらない　｜\n", playerName[0]);
					printf("＋――――――――――――――――――――――――＋\n");
				}
				else
				{
					statusTable[3].endurance *= 6 / 5;
					printf("＋―――――――――――――――――＋\n");
					printf("｜%sのみのまもりがあがった　｜\n", playerName[3]);
					printf("＋―――――――――――――――――＋\n");
				}
				_getch();
			}
			else if (statusTable[2].action_spell == 1)
			{
				cureMin = 75;
				cureMax = 95;
				cure = cureMin + rand() % (cureMax - cureMin);
				display();
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sはべホイミをとなえた　　｜\n", playerName[2]);
				printf("＋―――――――――――――――――＋\n");
				statusTable[2].MP -= 5;
				statusTable[statusTable[2].action_spell_target].HP += cure;
				if (statusTable[statusTable[2].action_spell_target].HP > statusTable[statusTable[2].action_spell_target].maxHP)
					statusTable[statusTable[2].action_spell_target].HP = statusTable[statusTable[2].action_spell_target].maxHP;
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sはHPが%dかいふくした　｜\n", playerName[statusTable[2].action_spell_target], cure);
				printf("＋―――――――――――――――――＋\n");
				_getch();
			}
			else if (statusTable[2].action_spell == 2)
			{
				display();
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sはキアリクをとなえた　　｜\n", playerName[2]);
				printf("＋―――――――――――――――――＋\n");
				statusTable[2].MP -= 2;
				statusTable[0].paralysis = 0;
				statusTable[1].paralysis = 0;
				statusTable[2].paralysis = 0;
				statusTable[3].paralysis = 0;
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sのマヒをけしさった　　　｜\n", playerName[statusTable[0].action_spell_target]);
				printf("＋―――――――――――――――――＋\n");
				_getch();
			}
			else if (statusTable[2].action_spell == 3)
			{
				display();
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sはベホマをとなえた　　　｜\n", playerName[2]);
				printf("＋―――――――――――――――――＋\n");
				statusTable[2].MP -= 7;
				statusTable[statusTable[2].action_spell_target].HP = statusTable[statusTable[2].action_spell_target].maxHP;
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sはHPがぜんかいふくした　｜\n", playerName[statusTable[2].action_spell_target]);
				printf("＋―――――――――――――――――＋\n");
				_getch();
			}
			else if (statusTable[2].action_spell == 4)
			{
				display();
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sはフバーハをとなえた　　｜\n", playerName[2]);
				printf("＋―――――――――――――――――＋\n");
				statusTable[0].MP -= 3;
				bless = 1 / 2;
				printf("＋―――――――――――――――――＋\n");
				printf("｜ぜんいんのブレスたいせいがあがった｜\n");
				printf("＋―――――――――――――――――＋\n");
				_getch();
			}
			else if (statusTable[2].action_spell == 5)
			{
				m_damageMin = 70;
				m_damageMax = 90;
				m_damage = m_damageMin + rand() % (m_damageMax - m_damageMin);
				display();
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sはライデインをとなえた　｜\n", playerName[2]);
				printf("＋―――――――――――――――――＋\n");
				statusTable[2].MP -= 6;
				statusTable[4].HP -= m_damage;
				printf("＋―――――――――――――――――――――――――＋\n");
				printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[1], enemyName[0], m_damage);
				printf("＋―――――――――――――――――――――――――＋\n");
				_getch();
			}
			else if (statusTable[2].action_spell == 6)
			{
				display();
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sはザオリクをとなえた　　｜\n", playerName[2]);
				printf("＋―――――――――――――――――＋\n");
				statusTable[2].MP -= 20;
				if (statusTable[statusTable[2].action_spell_target].HP == 0)
				{
					statusTable[statusTable[2].action_spell_target].HP = statusTable[statusTable[2].action_spell_target].maxHP;
					printf("＋――――――――――――――――――――――――＋\n");
					printf("｜%sはいきかえって、かんぜんかいふくした　｜\n", playerName[statusTable[2].action_spell_target]);
					printf("＋――――――――――――――――――――――――＋\n");
				}
				else if (statusTable[statusTable[2].action_spell_target].HP != 0)
				{
					printf("＋―――――――――――――――――＋\n");
					printf("｜しかし、%sはいきている　　｜\n", playerName[statusTable[2].action_spell_target]);
					printf("＋―――――――――――――――――＋\n");
				}
			}
			else if (statusTable[2].action_spell == 7)
			{
				cureMin = 100;
				cureMax = 120;
				cure = cureMin + rand() % (cureMax - cureMin);
				display();
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sはベホマラーをとなえた　｜\n", playerName[2]);
				printf("＋―――――――――――――――――＋\n");
				statusTable[2].MP -= 18;
				statusTable[0].HP += cure;
				if (statusTable[0].HP > statusTable[0].maxHP)
					statusTable[0].HP = statusTable[0].maxHP;
				statusTable[1].HP += cure;
				if (statusTable[1].HP > statusTable[0].maxHP)
					statusTable[1].HP = statusTable[0].maxHP;
				statusTable[2].HP += cure;
				if (statusTable[2].HP > statusTable[0].maxHP)
					statusTable[2].HP = statusTable[0].maxHP;
				statusTable[3].HP += cure;
				if (statusTable[3].HP > statusTable[0].maxHP)
					statusTable[3].HP = statusTable[0].maxHP;
				printf("＋―――――――――――――――――＋\n");
				printf("｜ぜんいんのHPがかいふくした　　　　｜\n");
				printf("＋―――――――――――――――――＋\n");
				_getch();
			}
			else if (statusTable[2].action_spell == 8)
			{
				m_damageMin = 175;
				m_damageMax = 225;
				m_damage = m_damageMin + rand() % (m_damageMax - m_damageMin);
				display();
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sはギガデインをとなえた　｜\n", playerName[2]);
				printf("＋―――――――――――――――――＋\n");
				statusTable[2].MP -= 15;
				statusTable[4].HP -= m_damage;
				printf("＋―――――――――――――――――――――――――＋\n");
				printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[2], enemyName[0], m_damage);
				printf("＋―――――――――――――――――――――――――＋\n");
				_getch();
			}
			else if (statusTable[2].action_spell == 9)
			{
				m_damageMin = 300;
				m_damageMax = 350;
				m_damage = m_damageMin + rand() % (m_damageMax - m_damageMin);
				display();
				printf("＋―――――――――――――――――――＋\n");
				printf("｜%sはぜんいんからちからをあつめ｜\n", playerName[2]);
				statusTable[0].MP -= 10;
				statusTable[1].MP -= 10;
				statusTable[2].MP -= 10;
				statusTable[3].MP -= 10;
				printf("｜ミナデインをとなえた　　　　　　　　　｜\n");
				printf("＋―――――――――――――――――――＋\n");
				statusTable[4].HP -= m_damage;
				printf("＋―――――――――――――――――――＋\n");
				printf("｜%sに%dのダメージをあたえた　｜\n", enemyName[0], m_damage);
				printf("＋―――――――――――――――――――＋\n");
				_getch();
			}
		}
	}
	else if (p_turn == 3)
	{
		if (statusTable[3].action == 1)
		{
			if (statusTable[3].action_spell == 0)
			{
				m_damageMin = 25;
				m_damageMax = 35;
				m_damage = m_damageMin + rand() % (m_damageMax - m_damageMin);
				display();
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sはヒャドをとなえた　　　｜\n", playerName[3]);
				printf("＋―――――――――――――――――＋\n");
				statusTable[3].MP -= 3;
				statusTable[4].HP -= m_damage;
				printf("＋―――――――――――――――――――――――――＋\n");
				printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[3], enemyName[0], m_damage);
				printf("＋―――――――――――――――――――――――――＋\n");
				_getch();
			}
			else if (statusTable[3].action_spell == 1)
			{
				m_damageMin = 20;
				m_damageMax = 30;
				m_damage = m_damageMin + rand() % (m_damageMax - m_damageMin);
				display();
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sはイオをとなえた　　　｜\n", playerName[3]);
				printf("＋―――――――――――――――――＋\n");
				statusTable[3].MP -= 5;
				statusTable[4].HP -= m_damage;
				printf("＋―――――――――――――――――――――――――＋\n");
				printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[3], enemyName[0], m_damage);
				printf("＋―――――――――――――――――――――――――＋\n");
				_getch();
			}
			else if (statusTable[3].action_spell == 2)
			{
				m_damageMin = 42;
				m_damageMax = 58;
				m_damage = m_damageMin + rand() % (m_damageMax - m_damageMin);
				display();
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sはヒャダルコをとなえた　｜\n", playerName[3]);
				printf("＋―――――――――――――――――＋\n");
				statusTable[3].MP -= 5;
				statusTable[4].HP -= m_damage;
				printf("＋―――――――――――――――――――――――――＋\n");
				printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[3], enemyName[0], m_damage);
				printf("＋―――――――――――――――――――――――――＋\n");
				_getch();
			}
			else if (statusTable[3].action_spell == 3)
			{
				display();
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sはバイキルトをとなえた　｜\n", playerName[3]);
				printf("＋―――――――――――――――――＋\n");
				statusTable[3].MP -= 6;
				if (statusTable[statusTable[3].action_spell_target].strength >= statusTable[statusTable[3].action_spell_target].base_strength * 2)
				{
					statusTable[statusTable[3].action_spell_target].strength = statusTable[statusTable[3].action_spell_target].strength;
					printf("＋―――――――――――――――――――――――＋\n");
					printf("｜しかし、%sのちからはもうあがらない　｜\n", playerName[statusTable[3].action_spell_target]);
					printf("＋―――――――――――――――――――――――＋\n");
				}
				else
				{
					statusTable[statusTable[3].action_spell_target].strength *= 2;
					printf("＋―――――――――――――――――＋\n");
					printf("｜%sはちからがばいになった　｜\n", playerName[statusTable[3].action_spell_target]);
					printf("＋―――――――――――――――――＋\n");
				}
				_getch();
			}
			else if (statusTable[3].action_spell == 4)
			{
				display();
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sはルカナンをとなえた　　｜\n", playerName[3]);
				printf("＋―――――――――――――――――＋\n");
				statusTable[3].MP -= 4;
				if (statusTable[4].base_endurance == 0)
				{
					printf("＋――――――――――――――――――――＋\n");
					printf("｜%sのみのまもりはもうさがらない｜\n", playerName[4]);
					printf("＋――――――――――――――――――――＋\n");
				}
				else
				{
					statusTable[4].base_endurance -= statusTable[4].base_endurance / 2;
					printf("＋―――――――――――――――――＋\n");
					printf("｜%sのみのまもりがさがった｜\n", playerName[4]);
					printf("＋―――――――――――――――――＋\n");
				}
				_getch();
			}
			else if (statusTable[3].action_spell == 5)
			{
				m_damageMin = 52;
				m_damageMax = 68;
				m_damage = m_damageMin + rand() % (m_damageMax - m_damageMin);
				display();
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sはイオラをとなえた　　　｜\n", playerName[3]);
				printf("＋―――――――――――――――――＋\n");
				statusTable[3].MP -= 8;
				statusTable[4].HP -= m_damage;
				printf("＋―――――――――――――――――――――――――＋\n");
				printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[3], enemyName[0], m_damage);
				printf("＋―――――――――――――――――――――――――＋\n");
				_getch();
			}
			else if (statusTable[3].action_spell == 6)
			{
				m_damageMin = 80;
				m_damageMax = 104;
				m_damage = m_damageMin + rand() % (m_damageMax - m_damageMin);
				display();
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sはマヒャドをとなえた　　｜\n", playerName[3]);
				printf("＋―――――――――――――――――＋\n");
				statusTable[3].MP -= 12;
				statusTable[4].HP -= m_damage;
				printf("＋―――――――――――――――――――――――――＋\n");
				printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[3], enemyName[0], m_damage);
				printf("＋―――――――――――――――――――――――――＋\n");
				_getch();
			}
			else if (statusTable[3].action_spell == 7)
			{
				display();
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sはドラゴラムをとなえた　｜\n", playerName[3]);
				printf("＋―――――――――――――――――＋\n");
				statusTable[3].MP -= 18;
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sはドラゴンになった　　　｜\n", playerName[3]);
				printf("＋―――――――――――――――――＋\n");

				statusTable[3].dragon = 1;

				int damageBase;
				int damageMin;
				int damageMax;
				int damage;

				switch (rand() % 3)
				{
				case 0:
					damageBase = statusTable[p_turn].attack / 2 - statusTable[4].base_endurance / 4;
					damageMin = damageBase * 7 / 8 + 60;
					damageMax = damageBase * 9 / 8 + 60;
					damage = damageMin + rand() % (damageMax - damageMin);
					printf("＋―――――――――――――――――――＋\n");
					printf("｜%sはするどいツメでこうげきした｜\n", playerName[3]);
					printf("＋―――――――――――――――――――＋\n");
					statusTable[4].HP -= damage;
					printf("＋――――――――――――――――――＋\n");
					printf("｜%sは%dのダメージをうけた｜\n", enemyName[0], damage);
					printf("＋――――――――――――――――――＋\n");
					break;
				default:
					damageMin = 65;
					damageMax = 85;
					damage = damageMin + rand() % (damageMax - damageMin);
					printf("＋――――――――――――――＋\n");
					printf("｜%sはほのおをはいた　｜\n", playerName[3]);
					printf("＋――――――――――――――＋\n");
					statusTable[4].HP -= damage;
					printf("＋――――――――――――――――――＋\n");
					printf("｜%sは%dのダメージをうけた｜\n", enemyName[0], damage);
					printf("＋――――――――――――――――――＋\n");
					break;
				}
				_getch();
			}
			else if (statusTable[3].action_spell == 8)
			{
				m_damageMin = 120;
				m_damageMax = 160;
				m_damage = m_damageMin + rand() % (m_damageMax - m_damageMin);
				display();
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sはイオナズンをとなえた　｜\n", playerName[3]);
				printf("＋―――――――――――――――――＋\n");
				statusTable[3].MP -= 15;
				statusTable[4].HP -= m_damage;
				printf("＋―――――――――――――――――――――――――＋\n");
				printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[3], enemyName[0], m_damage);
				printf("＋―――――――――――――――――――――――――＋\n");
				_getch();
			}
		}
	}
}

// 道具
void tool()
{
	if (p_turn == 0)
	{
		if (statusTable[0].action == 2 && statusTable[0].action_tool == 0)
		{
			display();
			printf("＋――――――――――――――――――＋\n");
			printf("｜%sはたたかいのドラムを使った　　　　｜\n", playerName[0]);
			printf("＋――――――――――――――――――＋\n");
			if (statusTable[0].strength >= statusTable[0].base_strength * 2)
			{
				printf("＋――――――――――――――――――――――――＋\n");
				printf("｜しかし、%sのちからはもうあがらない　　　｜\n", playerName[0]);
				printf("＋――――――――――――――――――――――――＋\n");
			}
			else
			{
				statusTable[0].strength *= 2;
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sのちからがあがった　　　｜\n", playerName[0]);
				printf("＋―――――――――――――――――＋\n");
			}
			if (statusTable[1].strength >= statusTable[1].base_strength * 2)
			{
				printf("＋――――――――――――――――――――――――＋\n");
				printf("｜しかし、%sのちからはもうあがらない　　　｜\n", playerName[1]);
				printf("＋――――――――――――――――――――――――＋\n");
			}
			else
			{
				statusTable[1].strength *= 2;
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sのちからがあがった　　　｜\n", playerName[1]);
				printf("＋―――――――――――――――――＋\n");
			}
			if (statusTable[2].strength >= statusTable[2].base_strength * 2)
			{
				printf("＋――――――――――――――――――――――――＋\n");
				printf("｜しかし、%sのちからはもうあがらない　　　｜\n", playerName[1]);
				printf("＋――――――――――――――――――――――――＋\n");
			}
			else
			{
				statusTable[2].strength *= 2;
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sのちからがあがった　　　｜\n", playerName[2]);
				printf("＋―――――――――――――――――＋\n");
			}
			if (statusTable[3].strength >= statusTable[3].base_strength * 2)
			{
				printf("＋――――――――――――――――――――――――＋\n");
				printf("｜しかし、%sのちからはもうあがらない　　　｜\n", playerName[3]);
				printf("＋――――――――――――――――――――――――＋\n");
			}
			else
			{
				statusTable[3].strength *= 2;
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sのちからがあがった　　　｜\n", playerName[3]);
				printf("＋―――――――――――――――――＋\n");
			}
			_getch();
		}
	}
	else if (p_turn == 1)
	{
		if (statusTable[1].action == 2 && statusTable[1].action_tool == 0)
		{
			display();
			printf("＋――――――――――――――――――＋\n");
			printf("｜%sはたたかいのドラムを使った　　　　｜\n", playerName[1]);
			printf("＋――――――――――――――――――＋\n");
			if (statusTable[0].strength >= statusTable[0].base_strength * 2)
			{
				printf("＋――――――――――――――――――――――――＋\n");
				printf("｜しかし、%sのちからはもうあがらない　　　｜\n", playerName[0]);
				printf("＋――――――――――――――――――――――――＋\n");
			}
			else
			{
				statusTable[0].strength *= 2;
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sのちからがあがった　　　｜\n", playerName[0]);
				printf("＋―――――――――――――――――＋\n");
			}
			if (statusTable[1].strength >= statusTable[1].base_strength * 2)
			{
				printf("＋――――――――――――――――――――――――＋\n");
				printf("｜しかし、%sのちからはもうあがらない　　　｜\n", playerName[1]);
				printf("＋――――――――――――――――――――――――＋\n");
			}
			else
			{
				statusTable[1].strength *= 2;
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sのちからがあがった　　　｜\n", playerName[1]);
				printf("＋―――――――――――――――――＋\n");
			}
			if (statusTable[2].strength >= statusTable[2].base_strength * 2)
			{
				printf("＋――――――――――――――――――――――――＋\n");
				printf("｜しかし、%sのちからはもうあがらない　　　｜\n", playerName[1]);
				printf("＋――――――――――――――――――――――――＋\n");
			}
			else
			{
				statusTable[2].strength *= 2;
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sのちからがあがった　　　｜\n", playerName[2]);
				printf("＋―――――――――――――――――＋\n");
			}
			if (statusTable[3].strength >= statusTable[3].base_strength * 2)
			{
				printf("＋――――――――――――――――――――――――＋\n");
				printf("｜しかし、%sのちからはもうあがらない　　　｜\n", playerName[3]);
				printf("＋――――――――――――――――――――――――＋\n");
			}
			else
			{
				statusTable[3].strength *= 2;
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sのちからがあがった　　　｜\n", playerName[3]);
				printf("＋―――――――――――――――――＋\n");
			}
			_getch();
		}
	}
	else if (p_turn == 2)
	{
		if (statusTable[2].action == 2 && statusTable[2].action_tool == 0)
		{
			display();
			printf("＋――――――――――――――――――＋\n");
			printf("｜%sはたたかいのドラムを使った　　　　｜\n", playerName[2]);
			printf("＋――――――――――――――――――＋\n");
			if (statusTable[0].strength >= statusTable[0].base_strength * 2)
			{
				printf("＋――――――――――――――――――――――――＋\n");
				printf("｜しかし、%sのちからはもうあがらない　　　｜\n", playerName[0]);
				printf("＋――――――――――――――――――――――――＋\n");
			}
			else
			{
				statusTable[0].strength *= 2;
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sのちからがあがった　　　｜\n", playerName[0]);
				printf("＋―――――――――――――――――＋\n");
			}
			if (statusTable[1].strength >= statusTable[1].base_strength * 2)
			{
				printf("＋――――――――――――――――――――――――＋\n");
				printf("｜しかし、%sのちからはもうあがらない　　　｜\n", playerName[1]);
				printf("＋――――――――――――――――――――――――＋\n");
			}
			else
			{
				statusTable[1].strength *= 2;
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sのちからがあがった　　　｜\n", playerName[1]);
				printf("＋―――――――――――――――――＋\n");
			}
			if (statusTable[2].strength >= statusTable[2].base_strength * 2)
			{
				printf("＋――――――――――――――――――――――――＋\n");
				printf("｜しかし、%sのちからはもうあがらない　　　｜\n", playerName[1]);
				printf("＋――――――――――――――――――――――――＋\n");
			}
			else
			{
				statusTable[2].strength *= 2;
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sのちからがあがった　　　｜\n", playerName[2]);
				printf("＋―――――――――――――――――＋\n");
			}
			if (statusTable[3].strength >= statusTable[3].base_strength * 2)
			{
				printf("＋――――――――――――――――――――――――＋\n");
				printf("｜しかし、%sのちからはもうあがらない　　　｜\n", playerName[3]);
				printf("＋――――――――――――――――――――――――＋\n");
			}
			else
			{
				statusTable[3].strength *= 2;
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sのちからがあがった　　　｜\n", playerName[3]);
				printf("＋―――――――――――――――――＋\n");
			}
			_getch();
		}
	}
	else if (p_turn == 3)
	{
		if (statusTable[3].action == 2 && statusTable[3].action_tool == 0)
		{
			display();
			printf("＋――――――――――――――――――＋\n");
			printf("｜%sはたたかいのドラムを使った　　　　｜\n", playerName[3]);
			printf("＋――――――――――――――――――＋\n");
			if (statusTable[0].strength >= statusTable[0].base_strength * 2)
			{
				printf("＋――――――――――――――――――――――――＋\n");
				printf("｜しかし、%sのちからはもうあがらない　　　｜\n", playerName[0]);
				printf("＋――――――――――――――――――――――――＋\n");
			}
			else
			{
				statusTable[0].strength *= 2;
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sのちからがあがった　　　｜\n", playerName[0]);
				printf("＋―――――――――――――――――＋\n");
			}
			if (statusTable[1].strength >= statusTable[1].base_strength * 2)
			{
				printf("＋――――――――――――――――――――――――＋\n");
				printf("｜しかし、%sのちからはもうあがらない　　　｜\n", playerName[1]);
				printf("＋――――――――――――――――――――――――＋\n");
			}
			else
			{
				statusTable[1].strength *= 2;
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sのちからがあがった　　　｜\n", playerName[1]);
				printf("＋―――――――――――――――――＋\n");
			}
			if (statusTable[2].strength >= statusTable[2].base_strength * 2)
			{
				printf("＋――――――――――――――――――――――――＋\n");
				printf("｜しかし、%sのちからはもうあがらない　　　｜\n", playerName[1]);
				printf("＋――――――――――――――――――――――――＋\n");
			}
			else
			{
				statusTable[2].strength *= 2;
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sのちからがあがった　　　｜\n", playerName[2]);
				printf("＋―――――――――――――――――＋\n");
			}
			if (statusTable[3].strength >= statusTable[3].base_strength * 2)
			{
				printf("＋――――――――――――――――――――――――＋\n");
				printf("｜しかし、%sのちからはもうあがらない　　　｜\n", playerName[3]);
				printf("＋――――――――――――――――――――――――＋\n");
			}
			else
			{
				statusTable[3].strength *= 2;
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sのちからがあがった　　　｜\n", playerName[3]);
				printf("＋―――――――――――――――――＋\n");
			}
			_getch();
		}
	}
}

int select_action(int i)
{
	int command = 0;
	// player1・死亡判定
	if (statusTable[i].HP == 0 || statusTable[i].sleep || statusTable[i].paralysis) {
		status_break();
		statusTable[i].action = 0;
		statusTable[i].can_action = false;
		return -1;
	}
	statusTable[i].can_action = true;
	// player1・休み判定

	while (1)
	{
		display();
		printf("%s\n", playerName[i]);
		printf("＋――――――＋\n");
		for (int i = 0; i < COMMAND_MAX; i++)
			printf("｜%s%s　｜\n",
			(i == command) ? "＞" : "　",
				commandFirst[i]);
		printf("＋――――――＋\n");


		int input = get_input(3);
		if (input == -1)break;
		else command = input;
	}
	return command;
}

void disp_spells(int select, int player)
{
	display();
	printf("%s\n", playerName[player]);
	printf("＋――――――――＋\n");
	for (int i = 0; i < statusTable[player].spells.size; i++)
		printf("｜%s%s ｜\n",
		(i == select) ? "＞" : "　",
			statusTable[player].spells.name[i]);
	printf("＋――――――――＋\n");
}

int main()
{
	//player1・ステータス
	{
		statusTable[0].strength = statusTable[0].base_strength;
		statusTable[0].endurance = statusTable[0].base_endurance;
		statusTable[0].attack = statusTable[0].strength + 130;
		statusTable[0].defense = statusTable[0].endurance + 235;
		statusTable[0].HP = statusTable[0].maxHP;
		statusTable[0].MP = statusTable[0].maxMP;
		SpellData spelldata = { detailSpell1,SpellMP1,SelectTargetSpell1,SPELL1_MAX };
		statusTable[0].spells = spelldata;
	}
	//player2・ステータス
	{
		statusTable[1].strength = statusTable[1].base_strength;
		statusTable[1].endurance = statusTable[1].base_endurance;
		statusTable[1].attack = statusTable[1].strength + 100;
		statusTable[1].defense = statusTable[1].endurance + 157;
		statusTable[1].HP = statusTable[1].maxHP;
		statusTable[1].MP = statusTable[1].maxMP;
		SpellData spelldata2 = { detailSpell2,SpellMP2,SelectTargetSpell2,SPELL2_MAX };
		statusTable[1].spells = spelldata2;
	}
	//player3・ステータス
	{
		statusTable[2].strength = statusTable[2].base_strength;
		statusTable[2].endurance = statusTable[2].base_endurance;
		statusTable[2].attack = statusTable[2].strength + 130;
		statusTable[2].defense = statusTable[2].endurance + 235;
		statusTable[2].HP = statusTable[2].maxHP;
		statusTable[2].MP = statusTable[2].maxMP;
		SpellData spelldata3 = { detailSpell3,SpellMP3,SelectTargetSpell3,SPELL3_MAX };
		statusTable[2].spells = spelldata3;
	}
	//player4・ステータス
	{
		statusTable[3].strength = statusTable[3].base_strength;
		statusTable[3].endurance = statusTable[3].base_endurance;
		statusTable[3].attack = statusTable[3].strength + 100;
		statusTable[3].defense = statusTable[3].endurance + 180;
		statusTable[3].HP = statusTable[3].maxHP;
		statusTable[3].MP = statusTable[3].maxMP;
		SpellData spelldata4 = { detailSpell4,SpellMP4,SelectTargetSpell4,SPELL4_MAX };
		statusTable[3].spells = spelldata4;
	}
	//enemy・HP
	{
		statusTable[4].HP = statusTable[4].maxHP;
		statusTable[4].can_action = true;
	}

	// 戦闘ループ
	while (1)
	{
		// 毒判定
		status_poison();



		for (int player = 0; player < 4; player++)
		{
			statusTable[player].action = select_action(player);
			if (statusTable[player].can_action == false)continue;

			switch (statusTable[player].action)
			{
			case 0:
				break;
			case 1:
				detail = 0;
				while (1)
				{
					int input;
					disp_spells(detail, player);
					input = get_input(10);
					if (input == -1)
					{
						// MPが足りないときの処理
						if (statusTable[player].MP - statusTable[player].spells.mp[detail] < 0)
						{
							display_mp();
							_getch();
						}
						else
						{
							break;
						}
					}
					else detail = input;
				}

				statusTable[player].action_spell = detail;

				if (statusTable[player].spells.isSelectTarget[statusTable[player].action_spell] == true)
				{
					spell_target = 0;
					while (1)
					{
						display();
						printf("使用対象\n");
						printf("＋――――――＋\n");
						for (int i = 0; i < NAME_MAX; i++)
							printf("｜%s%s  ｜\n",
							(i == spell_target) ? "＞" : "　",
								spell_targetName[i]);
						printf("＋――――――＋\n");
						
						int input;
						input = get_input(4);

						if (input == -1)break;
						else spell_target = input;
					}
					statusTable[player].action_spell_target = spell_target;
				}
				break;
			case 2:
				while (1)
				{
					display();
					printf("%s\n", playerName[player]);
					printf("＋―――――――――――＋\n");
					for (int i = 0; i < CONTENT_MAX; i++)
						printf("｜%s%s　｜\n",
						(i == content) ? "＞" : "　",
							contentTool[i]);
					printf("＋―――――――――――＋\n");

					int ch = _getch();
					if (ch == 0x0d)
						break;

					switch (ch)
					{
					case'1':	content = 0;	break;
					}
				}
				statusTable[player].action_tool = content;
				break;
			}
		}





		// すばやさの比較
		int agility[] =
		{
			statusTable[0].agility,
			statusTable[1].agility,
			statusTable[2].agility,
			statusTable[3].agility,
			statusTable[4].agility
		};



		//int agility[5];
		int action_players = 0;
		for (int i = 0; i < 5; i++)

			if (statusTable[i].can_action == true)
			{
				agility[action_players] = statusTable[i].agility;
				action_players++;
			}

		// agility[] をバブルソート
		for (int i = 0; i < action_players; i++)
		{
			for (int j = action_players - 1; j > i; j--)
			{
				if (agility[j - 1] < agility[j])
				{
					int d = agility[j - 1];
					agility[j - 1] = agility[j];
					agility[j] = d;
				}
			}
		}



		srand((unsigned)time(NULL));	//時間によって，実行系列を変更
		int damageBase;
		int damageMin;
		int damageMax;
		int damage;
		int c_damageBase;
		int c_damageMin;
		int c_damageMax;
		int c_damage;
		int em_damageMin;
		int em_damageMax;
		int em_damage;
		int keep;
		int b_turn = 0;			// バトルターン
		int agility_count = 0;	// 行動カウント

								// バトル
		while (1)
		{
		agi:
			if (agility[agility_count] == statusTable[0].agility)
				p_turn = 0;
			else if (agility[agility_count] == statusTable[1].agility)
				p_turn = 1;
			else if (agility[agility_count] == statusTable[2].agility)
				p_turn = 2;
			else if (agility[agility_count] == statusTable[3].agility)
				p_turn = 3;
			else if (agility[agility_count] == statusTable[4].agility)
				e_turn = 1;
			if (p_turn == 3 && statusTable[3].dragon == 1)
			{
				display();
				switch (rand() % 3)
				{
				case 0:
					damageBase = statusTable[p_turn].attack / 2 - statusTable[4].base_endurance / 4;
					damageMin = damageBase * 7 / 8 + 60;
					damageMax = damageBase * 9 / 8 + 60;
					damage = damageMin + rand() % (damageMax - damageMin);
					printf("＋―――――――――――――――――――＋\n");
					printf("｜%sはするどいツメでこうげきした｜\n", playerName[3]);
					printf("＋―――――――――――――――――――＋\n");
					statusTable[4].HP -= damage;
					printf("＋――――――――――――――――――＋\n");
					printf("｜%sは%dのダメージをうけた｜\n", enemyName[0], damage);
					printf("＋――――――――――――――――――＋\n");
					break;
				default:
					damageMin = 65;
					damageMax = 85;
					damage = damageMin + rand() % (damageMax - damageMin);
					printf("＋――――――――――――――＋\n");
					printf("｜%sはほのおをはいた　｜\n", playerName[3]);
					printf("＋――――――――――――――＋\n");
					statusTable[4].HP -= damage;
					printf("＋――――――――――――――――――＋\n");
					printf("｜%sは%dのダメージをうけた｜\n", enemyName[0], damage);
					printf("＋――――――――――――――――――＋\n");
					break;
				}
				_getch();
				agility_count++;
				if (agility_count == action_players)//yamato
					break;
				else
					goto agi;
			}

			if (e_turn == 1)
			{
				// 2回攻撃
				int attack_count = 0;
				while (1)
				{
					switch (rand() % 6)
					{
					case 0:
						keep = rand() % 4;
						damageBase = statusTable[4].base_strength / 2 - statusTable[keep].defense / 4;
						damageMin = damageBase * 7 / 8;
						damageMax = damageBase * 9 / 8;
						damage = damageMin + rand() % (damageMax - damageMin);
						display();
						printf("＋―――――――――――――――――＋\n");
						printf("｜%sのこうげき　　　　　　　｜\n", enemyName[0]);
						printf("＋―――――――――――――――――＋\n");
						statusTable[keep].HP -= damage;
						if (statusTable[keep].HP < 0)
							statusTable[keep].HP = 0;
						printf("＋―――――――――――――――――＋\n");
						printf("｜%sは%sに　　　　　｜\n", enemyName[0], playerName[keep]);
						printf("｜%dのダメージを与えた　　　　　　｜\n", damage);
						printf("＋―――――――――――――――――＋\n");
						_getch();
						break;
					case 1:
						em_damageMin = 72;
						em_damageMax = 88;
						display();
						printf("＋―――――――――――――――――＋\n");
						printf("｜%sはイオナズンをとなえた　｜\n", enemyName[0]);
						printf("＋―――――――――――――――――＋\n");
						for (int i = 0; i < 4; i++)
						{
							em_damage = em_damageMin + rand() % (em_damageMax - em_damageMin);
							statusTable[i].HP -= em_damage;
							if (statusTable[i].HP < 0)
								statusTable[i].HP = 0;
						}
						printf("＋―――――――――――――――――＋\n");
						printf("｜%sはプレイヤー全員に　　　｜\n", enemyName[0]);
						printf("｜%dのダメージを与えた　　　　　　      ｜\n", em_damage);//yamato
						printf("＋―――――――――――――――――＋\n");
						_getch();
						break;
					case 2:
						em_damageMin = 150;
						em_damageMax = 170;
						display();
						printf("＋―――――――――――――――――＋\n");
						printf("｜%sは灼熱の炎をとなえた　　｜\n", enemyName[0]);
						printf("＋―――――――――――――――――＋\n");
						for (int i = 0; i < 4; i++)
						{
							em_damage = em_damageMin + rand() % (em_damageMax - em_damageMin);
							statusTable[i].HP -= em_damage * bless;
							if (statusTable[i].HP < 0)
								statusTable[i].HP = 0;
						}
						printf("＋―――――――――――――――――＋\n");
						printf("｜%sはプレイヤー全員に　　　｜\n", enemyName[0]);
						printf("｜%dのダメージを与えた　　　　　　　　　｜\n", em_damage);//yamato
						printf("＋―――――――――――――――――＋\n");
						_getch();
						break;
					case 3:
						em_damageMin = 120;
						em_damageMax = 140;
						display();
						printf("＋―――――――――――――――――＋\n");
						printf("｜%sは輝く息をとなえた　　　｜\n", enemyName[0]);
						printf("＋―――――――――――――――――＋\n");
						for (int i = 0; i < 4; i++)
						{
							em_damage = em_damageMin + rand() % (em_damageMax - em_damageMin);
							statusTable[i].HP -= em_damage * bless;
							if (statusTable[i].HP < 0)
								statusTable[i].HP = 0;
						}
						printf("＋―――――――――――――――――＋\n");
						printf("｜%sはプレイヤー全員に　　　｜\n", enemyName[0]);
						printf("｜%dのダメージを与えた　　　　　　｜\n", em_damage);//yamato
						printf("＋―――――――――――――――――＋\n");
						_getch();
						break;
					case 4:
						keep = rand() % 4;
						em_damageMin = 92;
						em_damageMax = 128;
						em_damage = em_damageMin + rand() % (em_damageMax - em_damageMin);
						display();
						printf("＋―――――――――――――――――＋\n");
						printf("｜%sはメラゾーマをとなえた　｜\n", enemyName[0]);
						printf("＋―――――――――――――――――＋\n");
						statusTable[keep].HP -= em_damage;
						if (statusTable[keep].HP < 0)
							statusTable[keep].HP = 0;
						printf("＋―――――――――――――――――＋\n");
						printf("｜%sは%sに　　　　　｜\n", enemyName[0], playerName[keep]);
						printf("｜%dのダメージを与えた　　　　　　｜\n", em_damage);//yamato
						printf("＋―――――――――――――――――＋\n");
						_getch();
						break;
					case 5:
						display();
						printf("＋――――――――――――――――――＋\n");
						printf("｜%sは凍てつく波動をとなえた　｜\n", enemyName[0]);
						printf("＋――――――――――――――――――＋\n");
						statusTable[0].strength = statusTable[0].base_strength;
						statusTable[0].endurance = statusTable[0].base_endurance;
						statusTable[1].strength = statusTable[1].base_strength;
						statusTable[1].endurance = statusTable[1].base_endurance;
						statusTable[2].strength = statusTable[2].base_strength;
						statusTable[2].endurance = statusTable[2].base_endurance;
						statusTable[3].strength = statusTable[3].base_strength;
						statusTable[3].endurance = statusTable[3].base_endurance;
						bless = 1;
						printf("＋――――――――――――――――――＋\n");
						printf("｜プレイヤー全員にかかっている　　　　｜\n");
						printf("｜良い効果が消えた　　　　　　　　　　｜\n");
						printf("＋――――――――――――――――――＋\n");
						_getch();
						break;
					}
					attack_count++;
					if (attack_count == 2)
					{
						attack_count = 0;
						e_turn = 0;
						break;
					}
				}
			}

			else
			{
				if (statusTable[p_turn].action == 0)
				{
					damageBase = statusTable[p_turn].attack / 2 - statusTable[4].base_endurance / 4;
					damageMin = damageBase * 7 / 8;
					damageMax = damageBase * 9 / 8;
					damage = damageMin + rand() % (damageMax - damageMin);
					switch (keep = rand() % 32)
					{
					case 0:
						c_damageBase = statusTable[p_turn].attack;
						c_damageMin = c_damageBase;
						c_damageMax = c_damageBase * 74 / 64;
						c_damage = c_damageMin + rand() % (c_damageMax - c_damageMin);
						break;
					default:
						break;
					}
					display();
					printf("＋―――――――――――――――――＋\n");
					printf("｜%sのこうげき　　　　　　　　｜\n", playerName[p_turn]);
					printf("＋―――――――――――――――――＋");
					_getch();
					if (keep == 0)
					{
						display();
						printf("＋―――――――――――――――――＋\n");
						printf("｜会心の一撃！　　　　　　　　　　　｜\n");
						statusTable[4].HP -= c_damage;
						if (statusTable[4].HP < 0)
							statusTable[4].HP = 0;
						printf("｜%sは%sに　　　　　｜\n", playerName[p_turn], enemyName[0]);
						printf("｜%dのダメージを与えた　　　　　　　｜\n", c_damage);
						printf("＋―――――――――――――――――＋\n");
						_getch();
					}
					else
					{
						statusTable[4].HP -= damage;
						if (statusTable[4].HP < 0)
							statusTable[4].HP = 0;
						display();
						printf("＋―――――――――――――――――＋\n");
						printf("｜%sは%sに　　　　　｜\n", playerName[p_turn], enemyName[0]);
						printf("｜%dのダメージを与えた　　　　　　　｜\n", damage);
						printf("＋―――――――――――――――――＋\n");
						_getch();
					}
				}
				else if (statusTable[p_turn].action == 1)
					spell();
				if (statusTable[4].HP < 0)
					statusTable[4].HP = 0;
				else if (statusTable[p_turn].action == 2)
					tool();
			}

			b_turn++;
			agility_count++;

			if (statusTable[4].HP == 0)
				break;
			else if (statusTable[0].HP == 0 && statusTable[1].HP == 0 && statusTable[2].HP == 0 && statusTable[3].HP == 0)
				break;
			else if (statusTable[0].paralysis == 1 && statusTable[1].paralysis == 1 && statusTable[2].paralysis == 1 && statusTable[3].paralysis == 1)
				break;
			if (agility_count == action_players)//yamato
				break;
		}

		agility_count = 0;

		// 勝利時の処理
		if (statusTable[4].HP == 0)
		{
			display();
			printf("＋――――――――――――――――＋\n");
			printf("｜　　　　　%sをたおした　｜\n", enemyName[0]);
			printf("＋――――――――――――――――＋\n");
			_getch();
			break;
		}


		// 敗北時の処理
		else if (statusTable[0].HP == 0 && statusTable[1].HP == 0 && statusTable[2].HP == 0 && statusTable[3].HP == 0)
		{
			display();
			printf("＋――――――――――――――――＋\n");
			printf("｜　　プレイヤーがぜんめつした　　｜\n");
			printf("＋――――――――――――――――＋\n");
			_getch();
			break;
		}
		else if (statusTable[0].paralysis == 1 && statusTable[1].paralysis == 1 && statusTable[2].paralysis == 1 && statusTable[3].paralysis == 1)
		{
			display();
			printf("＋――――――――――――――――＋\n");
			printf("｜　プレイヤーがぜんいんまひした　｜\n");
			printf("＋――――――――――――――――＋\n");
			_getch();
			break;
		}
	}
}