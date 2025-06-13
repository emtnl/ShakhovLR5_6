#ifndef Cyber_H
#define Cyber_H

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;
class Player {
private:
	int playerid;
	string nickname;
	int rating;


protected:
	virtual void input() {
		cout << "Введите данные для Player";
		cin >> playerid >> nickname >> rating;

	}

	

	virtual void output() {
		cout << "Вы ввели: " << playerid << nickname << rating << endl;


	}

public:

	
	void setPlayerID(int id) { playerid = id; }
	void setNickname(const string& nick) { nickname = nick; }
	void setRating(int rat) { rating = rat; }

	int getID() const {
		return playerid;
	}
	string getname() const {
		return nickname;
	}
	int getrating() const {
		return rating;
	}

	Player() : Player(0, "Unknown", 0) {};

	Player(int a, const string& b, int c) : playerid(a), nickname(b), rating(c) {}

	explicit Player(int pid) : playerid(pid), nickname("Unknown"), rating(0) {}


	virtual void PlayRole() = 0;
	virtual int calculateimpact() = 0;
	virtual void validate() {
		if (rating > 0 && rating < 100) {
			cout << "Рейтинг корректен." << endl;
		}
		else {
			cout << "Ошибка: рейтинг должен быть положительным!" << endl;
		}
	}
	friend bool operator==(const Player& p1, const Player& p2);

	friend istream& operator>>(istream& in, Player& obj) {
		obj.input();
		return in;
	}


	friend ostream& operator << (ostream & out, Player & obj) {
		obj.output();
		return out;

	}
	virtual ~Player() {}




	void train() {


	}


	void playMatch() {

	}

	void getRole() {


	}

};



class Sniper : public Player {
private:
	int headshotAccuracy;
	int longRangeKills;

protected:
	int calculateimpact() override {
		return headshotAccuracy * 2 + longRangeKills;
	}

	void validate() override{
		if (headshotAccuracy > 70) {
			cout << "точность больше 70%" << endl;
		}
		else {
			cout << "точность меньше 70%" << endl;
		}
	}

public:



	Sniper() : Player(), headshotAccuracy(0), longRangeKills(0) {}


	Sniper(const Sniper& other) : Player(other), headshotAccuracy(other.headshotAccuracy), longRangeKills(other.longRangeKills) {}

	explicit Sniper(int hsa, int lrk) : headshotAccuracy(hsa), longRangeKills(lrk) {}
	


	void PlayRole() override {

		cout << "Роль - Sniper" << endl;
	}

	void input() override {
		cout << "Введите данные для Sniper";
		cin >> headshotAccuracy >> longRangeKills;

	}


	void output() override {
		cout << "Вы ввели: " << headshotAccuracy << longRangeKills << endl;
	}

	void upgradeScope() {
		headshotAccuracy = headshotAccuracy + 5;
		cout << "точность увеличена на 5%" << endl;
	}


	Sniper operator+(const Sniper& other) const;

	Sniper& operator+=(const Sniper& other) {
		headshotAccuracy += other.headshotAccuracy;
		longRangeKills += other.longRangeKills;
		return *this;
	}



};





class Support : public Player, protected Sniper {
private:
	int healsPerMatch;
	int utilityUsage;



protected:
	int calculateimpact() override {
		return healsPerMatch * 10 + utilityUsage * 5;
	}


	void validate() override {
		if (healsPerMatch >= 20) {
			cout << "Количество восстановлений за матч >= 20" << endl;
		}
		else {
			cout << "Количество меньше нормы" << endl;
		}
	}

public:
	void input() override {
		cout << "Введите данные для Support" << endl;
		cin >> healsPerMatch >> utilityUsage;

	}

	void output() override {
		cout << "Вы ввели: " << healsPerMatch << utilityUsage << endl;

	}


	void PlayRole() override {
		cout << "Ваша роль - поддержка" << endl;

	}




	virtual void deployShield() {
		cout << "Защита установлена" << endl;
	}

	Support& operator+=(int extraUtility) {
		if (extraUtility > 0) {
			utilityUsage += extraUtility;
			cout << "utilityUsage увеличен на " << extraUtility << endl;
		}
		else {
			cout << "Ошибка: можно добавлять только положительное значение!" << endl;
		}
		return *this;
	}




};

class TacticalAI : public Player, public Sniper, public Support {
protected:
	vector<string> strategies;

public:

	void input() override {
		cout << "Введите стратегии" << endl;
		string s;

		for (int x = 0; x < 3; ++x) {
			cin >> s;
			strategies.push_back(s);
			
		}
	}
	void output() override {
		for (const string& s : strategies) {
			cout << s << " ";
		}
		cout << endl;

	}

	string& operator[](int index);
	const string& operator[](int index) const;

};

class Strategist : public Player, public TacticalAI {
private:
	int successRate;
	int mapKnowledge;

protected:
	void PlayRole() override {
		cout << "Ваша роль - стратег" << endl;

	}

	void validate() override {
		if (mapKnowledge >= 3) {
			cout << "допустимое знание карт" << endl;
		}
		else {
			cout << "не дрпустимое знание карт" << endl;
		}
		

	}


public:
	Strategist(int rate = 0, int ledge = 0) : successRate(rate), mapKnowledge(ledge) {}

	Strategist() : Strategist(0, 0) {}



	virtual void predictEnemyMove() {
		cout << "Введите стратегии противника:" << endl;
		TacticalAI::input();

		cout << "Прогноз действий:" << endl;
		for (size_t i = 0; i < strategies.size(); ++i) {
			cout << i + 1 << ". " << (*this)[i] << endl;
		}
	}


	


};




bool operator==(const Player& p1, const Player& p2) {
	return p1.playerid == p2.playerid;
}


#endif