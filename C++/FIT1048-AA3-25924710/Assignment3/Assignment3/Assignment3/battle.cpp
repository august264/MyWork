#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
using namespace std;

int reward_health = 20; // global var for health bonus
int life = 1; // alive

class Character {
public:
	int health, attack, defence; // basic attributes
	string name;

	void set_health(int stat); // basic functions
	void set_attack(int stat);
	void set_defence(int stat);
	void set_name(string hero_name) {
		name = hero_name;
	}
	

};

void Character::set_health(int stat) { // set health for the character
	health = stat;
}

void Character::set_attack(int stat) {
	attack = stat;
}

void Character::set_defence(int stat) {
	defence = stat;
}



class Hero : public Character { // inherit from Character, having health, att, def and name.
public:
	int special_attack, money; // basic attributes of Hero class
	int health_limit = 50;


	void set_sp(int stat) {
		special_attack = stat;
	}
	void set_money(int stat) {
		money = stat;
	}

	void stat_viewer() { // display stat
		cout << "Look up here: \n";
		cout << name << "'s stat:" << endl;
		cout << "Attack: " << attack << endl;
		cout << "Defence: " << defence << endl;
		cout << "Health: " << health << endl;
		cout << "Money: " << money << endl;
		cout << "SP: " << special_attack << endl;
		cout << "\n";
	}

};

class Monster : public Character { // subclass of Character
public:
	
};

class Boss : public Character { // subclass of Character, having some extra attributes
public:
	int special_attack;

	void set_sp(int stat) {
		special_attack = stat;
	}
};


int rand1_6() { // generate a random number from 1 ~ 6
	int result;
	//srand(time(NULL));
	result = rand() % (6 - 1 + 1) + 1;
	return result;
}

int rand0_2() {// generate a random number from 0 ~ 2
	int result;
	//srand(time(NULL));
	result = rand() % (2 - 0 + 1) + 0;
	return result;
}

void reward_system(Hero* hero) {
	/* rewards system*/
	int reward_attack = rand0_2(); // sort out the random stuff
	int reward_defence = rand0_2();
	int reward_SP = rand0_2();
	int reward_money = hero->health; // it is fixed 

	int new_attack = hero->attack + reward_attack; // declare some new values for comparsion later
	int new_defence = hero->defence + reward_defence;
	int new_health = hero->health + reward_health;
	int new_sp = hero->special_attack + reward_SP;
	int new_money = hero->money + reward_money;


	hero->set_money(new_money); // it's fixed

	if (new_attack <= 10) { // check boundary so it can be set to the correct value
		hero->set_attack(new_attack);
		
	}
	else
	{
		hero->set_attack(10); // maximum reached
	}


	if (new_defence <= 10) {// check boundary so it can be set to the correct value
		hero->set_defence(new_defence);
	}
	else
	{
		hero->set_defence(10);// maximum reached
	}


	if (new_sp <= 10) {// check boundary so it can be set to the correct value
		hero->set_sp(new_sp);
	}
	else {
		hero->set_sp(10);// maximum reached
	}

	if (new_health <= hero->health_limit) {// check boundary so it can be set to the correct value
		hero->set_health(new_health);
	}
	else {
		hero->set_health(hero->health_limit); // maximum
	}
	
	hero->stat_viewer(); // this works
}

void battle(Hero* hero, Monster monster) {
	int ult_cd = 1; // in each round, hero can use one special attack
	int flag = 1; // hero's turn first
	int hero_curr_attack, hero_curr_defence, hero_random, mon_curr_attack, mon_curr_defence, mon_random;

	
	while (hero->health > 0 && monster.health > 0) {
		if (flag == 1) { // hero's turn
			cout << "Hero's turn now!" << endl;
			Sleep(1000);
			hero_random = rand1_6(); // get 1 ~ 6
			hero_curr_attack = hero->attack + hero_random; // the original attack + the random one

			mon_random = rand1_6(); // get 1 ~ 6
			mon_curr_defence = monster.defence + mon_random; // the original defense + the random one

			if (ult_cd > 0) { // when still can use special attack
				char choice[20];
				cout << "Using special attack?(y/n)";
				cin >> choice;				

				if (strcmp(choice, "y") == 0) { // if hero wants to use it
					hero_curr_attack = hero_curr_attack + hero->special_attack;
					ult_cd = ult_cd - 1;
				}

			}


			int ultimate_damage; // calculating the special attac dmg
			if (hero_curr_attack > mon_curr_defence) {
				
				int damage = hero_curr_attack - mon_curr_defence; // damage dealt
				cout << "Hero " << hero->name << " has dealt " << damage << " to " << monster.name << endl;
				Sleep(1000);
				monster.set_health(monster.health - damage);
				cout << monster.name << " Health Left: " << monster.health << endl;
				cout << "\n";
				Sleep(1000);
			}// battle information

			else
			{
				cout << monster.name << " has defended!" << endl;// battle information
				Sleep(1000);
				cout << monster.name << " Health Left: " << monster.health << endl;// battle information
				cout << "\n";
				Sleep(1000);
			}			
		}

		if (flag == -1) {
			cout << "Opponent's turn now!" << endl;// battle information
			Sleep(1000);
			mon_random = rand1_6(); // get 1 ~ 6
			mon_curr_attack = monster.attack + mon_random; // the original attack + the random one

			hero_random = rand1_6(); // get 1 ~ 6
			hero_curr_defence = hero->defence + hero_random; // the original defense + the random one

			if (mon_curr_attack > hero_curr_defence) {

				int damage = mon_curr_attack - hero_curr_defence; // damage dealt
				cout << monster.name << " has dealt " << damage << " to " << "Hero " << hero->name << endl;
				Sleep(1000);
				hero->set_health(hero->health - damage);// battle information
				cout << hero->name << " Health Left: " << hero->health << endl;// battle information
				cout << "\n";// battle information
				Sleep(1000);
			}

			else
			{
				cout << hero->name << " has defended!" << endl;// battle information
				Sleep(1000);
				cout << hero->name << " Health Left: " << hero->health << endl;// battle information
				cout << "\n";
				Sleep(1000);
			}
		}
		flag = flag * (-1); // switch turn
	}

	if (hero->health > 0 && monster.health <= 0) {
		cout << "\nHooray!\n";

		
	}
	else
	{
		cout << "\nYou died!\n";
		life = 0; //dead
	}



	
}



void final_battle(Hero* hero, Boss boss) {
	int ult_cd = 1; // in each round, hero can use one special attack
	int flag = 1; // hero's turn first
	int hero_curr_attack, hero_curr_defence, hero_random, mon_curr_attack, mon_curr_defence, mon_random;


	while (hero->health > 0 && boss.health > 0) {
		if (flag == 1) { // hero's turn
			cout << "Hero's turn now!" << endl;// battle information
			Sleep(1000);
			hero_random = rand1_6(); // get 1 ~ 6
			hero_curr_attack = hero->attack + hero_random; // the original attack + the random one

			mon_random = rand1_6(); // get 1 ~ 6
			mon_curr_defence = boss.defence + mon_random; // the original defense + the random one
			if (ult_cd > 0) {
				char choice[20];
				cout << "Using special attack?(y/n)";
				cin >> choice;

				if (strcmp(choice, "y") == 0) {
					hero_curr_attack = hero_curr_attack + hero->special_attack;
					ult_cd = ult_cd - 1;
				}
			}

			int ultimate_damage;
			if (hero_curr_attack > mon_curr_defence) {

				int damage = hero_curr_attack - mon_curr_defence; // damage dealt
				cout << "Hero " << hero->name << " has dealt " << damage << " to " << boss.name << endl;
				Sleep(1000);// battle information
				boss.set_health(boss.health - damage);
				cout << boss.name << " Health Left: " << boss.health << endl;// battle information
				cout << "\n";// battle information
				Sleep(1000);
			}

			else
			{
				cout << boss.name << " has defended!" << endl;// battle information
				Sleep(1000);// battle information
				cout << boss.name << " Health Left: " << boss.health << endl;
				cout << "\n";// battle information
				Sleep(1000);
			}
		}

		if (flag == -1) {
			cout << "Opponent's turn now!" << endl;
			Sleep(1000);
			mon_random = rand1_6(); // get 1 ~ 6
			mon_curr_attack = boss.attack + mon_random; // the original attack + the random one

			hero_random = rand1_6(); // get 1 ~ 6
			hero_curr_defence = hero->defence + hero_random; // the original defense + the random one

			if (mon_curr_attack > hero_curr_defence) {

				int damage = mon_curr_attack - hero_curr_defence; // damage dealt
				cout << boss.name << " has dealt " << damage << " to " << "Hero " << hero->name << endl;
				Sleep(1000);
				hero->set_health(hero->health - damage);
				cout << hero->name << " Health Left: " << hero->health << endl;// battle information
				cout << "\n";
				Sleep(1000);
			}

			else
			{
				cout << hero->name << " has defended!" << endl;// battle information
				Sleep(1000);
				cout << hero->name << " Health Left: " << hero->health << endl;// battle information
				cout << "\n";
				Sleep(1000);
			}
		}
		flag = flag * (-1); // switch turn
	}

	if (hero->health > 0 && boss.health <= 0) {
		cout << "\nHooray!\n";

	}
	else
	{
		cout << "\nYou died!\n";
		life = 0; //dead
	}
	

}

void shopping(Hero* me) {
	int more_health = 60; // price of an item
	char answer[20];
	cout << "Do you want to be stronger(y/n)?\n";
	cin >> answer;

	if (strcmp(answer, "y") == 0) {
		if (me->money >= more_health) {
			me->set_money(me->money - more_health);
			me->health_limit = 80; // change the upper limit of health so hero can have more health than 50
			cout << "purchased successfully, now your max health is 80.\n";
		}
		else
		{
			cout << "No enough money!\n";
		}

	}
	else
	{
		cout << "See ya!\n";
	}

}

void main() {

	srand(time(NULL));

	cout << "Test begins!\n";

	Hero* me = &Hero(); // basic settings
	me->set_name("Vincent");
	me->set_attack(3);// basic settings
	me->set_defence(3);// basic settings
	me->set_health(20);// basic settings
	me->set_money(0);// basic settings
	me->set_sp(10);// cheating value
	

	Boss boss;// basic settings
	boss.set_name("Shanshan");// basic settings
	boss.set_attack(8);// basic settings
	boss.set_defence(8);// basic settings
	boss.set_health(50);// basic settings
	boss.set_sp(5);// basic settings
	

	Monster mon1, mon2, mon3, mon4;
	mon1.set_name("Mon1");// basic settings// basic settings
	mon1.set_attack(1);// basic settings
	mon1.set_defence(1);// basic settings
	mon1.set_health(10);// basic settings
	


	mon2.set_name("Mon2");// basic settings
	mon2.set_attack(3);// basic settings
	mon2.set_defence(2);// basic settings
	mon2.set_health(20);// basic settings
	

	mon3.set_name("Mon3");// basic settings
	mon3.set_attack(5);// basic settings
	mon3.set_defence(4);// basic settings
	mon3.set_health(30);// basic settings
	

	mon4.set_name("Mon4");// basic settings// basic settings
	mon4.set_attack(6);// basic settings
	mon4.set_defence(7);// basic settings
	mon4.set_health(40);	// basic settings

	cout << "==============================================================================\n";
	vector<Monster> mon_list = { mon1, mon2, mon3, mon4 };
	vector<Boss> boss_list = { boss };

	//int mon_remained;
	//mon_remained = mon_list.size();

	//for (int i = 0; i < mon_remained; i++) {
	//	cout << mon_list[i].name << "'s stat:" << endl;
	//}
	

	
	if (life == 1) { // battle in order
		battle(me, mon1);
		reward_system(me);
		shopping(me);
	}


	if (life == 1) {		// battle in order
		battle(me, mon2);
		reward_system(me);
		shopping(me);
	}

	

	if (life == 1) {// battle in order
		battle(me, mon3);
		reward_system(me);
		shopping(me);
	}

	if (life == 1) {// battle in order
		battle(me, mon4);
		reward_system(me);
		shopping(me);
	}
	
	
	if (life == 1) {// battle in order
		final_battle(me, boss);
		reward_system(me);
		cout << "\n\nYou Win!\n\n";
	}



	



	system("pause");

}