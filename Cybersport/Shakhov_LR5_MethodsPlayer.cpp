#include "Shakhov_LR5_defPlayer.h"
#include "Shakhov_LR5_AbstractPlayer.h"
#include "Shakhov_LR5_ChildSniper.h"
#include "Shakhov_LR5_ChildSupport.h"
#include "Shakhov_LR5_ParentSniper.h"
#include "Shakhov_LR5_Multi_TacticalAI.h"

// Player
Player::Player() : playerId(0), nickname(""), rating(0) {}
Player::Player(int id, const string& nick, int rat) : playerId(id), nickname(nick), rating(rat) {}
Player::Player(int pid) : playerId(pid), nickname(""), rating(0) {}

void Player::validate() {
    if (getRating() >= 0 && getRating() <= 1000) {
        cout << "Рейтинг корректен." << endl;
    }
    else {
        cout << "Ошибка: рейтинг должен быть в диапазоне [0, 1000]!" << endl;
    }
}

istream& operator>>(istream& in, Player& obj) {
    return obj.input(in);  // Передача управления производному классу
}

ostream& operator<<(ostream& out, const Player& obj) {
    return obj.output(out);  // Передача управления производному классу
}

bool operator==(const Player& p1, const Player& p2) {
    return p1.getPlayerId() == p2.getPlayerId();
}

// Sniper
Sniper::Sniper() : Player(), headshotAccuracy(0), longRangeKills(0) {}
Sniper::Sniper(int id, const string& nick, int rat, int hsa, int lrk)
    : Player(id, nick, rat), headshotAccuracy(hsa), longRangeKills(lrk) {
}
Sniper::Sniper(const Sniper& other) : Player(other), headshotAccuracy(other.headshotAccuracy), longRangeKills(other.longRangeKills) {}
Sniper::Sniper(const string& nick) : Player(0, nick, 0), headshotAccuracy(0), longRangeKills(0) {}

istream& Sniper::input(istream& in) {
    int id, rat;
    string nick;
    cout << "Введите ID игрока: ";
    in >> id;
    in.ignore();
    cout << "Введите никнейм: ";
    getline(in, nick);
    cout << "Введите рейтинг (0-1000): ";
    in >> rat;
    setPlayerId(id);
    setNickname(nick);
    setRating(rat);

    cout << "Введите точность хедшотов (%): ";
    in >> headshotAccuracy;
    cout << "Введите количество дальних убийств: ";
    in >> longRangeKills;
    return in;
}

ostream& Sniper::output(ostream& out) const {
    out << "ID: " << getPlayerId() << "\nНикнейм: " << getNickname() << "\nРейтинг: " << getRating()
        << "\nТочность хедшотов: " << headshotAccuracy << "%\nДальних убийств: " << longRangeKills << endl;
    return out;
}

void Sniper::playRole() { cout << "Роль: Снайпер" << endl; }
int Sniper::calculateImpact() { return headshotAccuracy * 2 + longRangeKills; }
void Sniper::validate() {
    Player::validate();
    if (headshotAccuracy >= 70) {
        cout << "Точность хедшотов корректна (>=70%)." << endl;
    }
    else {
        cout << "Ошибка: точность хедшотов должна быть >=70%!" << endl;
    }
}

void Sniper::upgradeScope() {
    headshotAccuracy += 5;
    cout << "Точность хедшотов увеличена на 5%." << endl;
}

unique_ptr<Sniper> Sniper::operator+(const Sniper& other) const {
    auto result = make_unique<Sniper>(
        getPlayerId(), getNickname() + "&" + other.getNickname(), getRating(),
        headshotAccuracy + other.headshotAccuracy, longRangeKills + other.longRangeKills
    );
    return result;
}

// Support
Support::Support() : Player(), healsPerMatch(0), utilityUsage(0) {}
Support::Support(int id, const string& nick, int rat, int hpm, int util)
    : Player(id, nick, rat), healsPerMatch(hpm), utilityUsage(util) {
}
Support::Support(const Support& other) : Player(other), healsPerMatch(other.healsPerMatch), utilityUsage(other.utilityUsage) {}
Support::Support(const string& nick) : Player(0, nick, 0), healsPerMatch(0), utilityUsage(0) {}

istream& Support::input(istream& in) {
    int id, rat;
    string nick;
    cout << "Введите ID игрока: ";
    in >> id;
    in.ignore();
    cout << "Введите никнейм: ";
    getline(in, nick);
    cout << "Введите рейтинг (0-1000): ";
    in >> rat;
    setPlayerId(id);
    setNickname(nick);
    setRating(rat);

    cout << "Введите количество восстановлений за матч: ";
    in >> healsPerMatch;
    cout << "Введите использование утилит: ";
    in >> utilityUsage;
    return in;
}

ostream& Support::output(ostream& out) const {
    out << "ID: " << getPlayerId() << "\nНикнейм: " << getNickname() << "\nРейтинг: " << getRating()
        << "\nВосстановлений за матч: " << healsPerMatch << "\nИспользование утилит: " << utilityUsage << endl;
    return out;
}

void Support::playRole() { cout << "Роль: Поддержка" << endl; }
int Support::calculateImpact() { return healsPerMatch * 10 + utilityUsage * 5; }
void Support::validate() {
    Player::validate();
    if (healsPerMatch >= 20) {
        cout << "Количество восстановлений корректно (>=20)." << endl;
    }
    else {
        cout << "Ошибка: количество восстановлений должно быть >=20!" << endl;
    }
}

void Support::deployShield() { cout << "Защита установлена." << endl; }

unique_ptr<Support> Support::operator+(const Support& other) const {
    auto result = make_unique<Support>(
        getPlayerId(), getNickname() + "&" + other.getNickname(), getRating(),
        healsPerMatch + other.healsPerMatch, utilityUsage + other.utilityUsage
    );
    return result;
}

// TacticalAI
istream& TacticalAI::input(istream& in) {
    strategies.clear();
    cout << "Введите 3 стратегии (по одной на строке):\n";
    for (int i = 0; i < 3; ++i) {
        string strat;
        cout << "Стратегия " << i + 1 << ": ";
        in.ignore();
        getline(in, strat);
        strategies.push_back(strat);
    }
    return in;
}

ostream& TacticalAI::output(ostream& out) const {
    out << "Стратегии:\n";
    for (size_t i = 0; i < strategies.size(); ++i) {
        out << i + 1 << ". " << strategies[i] << endl;
    }
    return out;
}

string& TacticalAI::operator[](int index) {
    if (index < 0 || index >= static_cast<int>(strategies.size())) {
        throw out_of_range("Недопустимый индекс стратегии.");
    }
    return strategies[index];
}

const string& TacticalAI::operator[](int index) const {
    if (index < 0 || index >= static_cast<int>(strategies.size())) {
        throw out_of_range("Недопустимый индекс стратегии.");
    }
    return strategies[index];
}

// Strategist
Strategist::Strategist() : Player(), successRate(0), mapKnowledge(0) {}
Strategist::Strategist(int id, const string& nick, int rat, int rate, int ledge)
    : Player(id, nick, rat), successRate(rate), mapKnowledge(ledge) {
}
Strategist::Strategist(const Strategist& other)
    : Player(other), TacticalAI(other), successRate(other.successRate), mapKnowledge(other.mapKnowledge) {
}
Strategist::Strategist(const string& nick) : Player(0, nick, 0), successRate(0), mapKnowledge(0) {}

istream& Strategist::input(istream& in) {
    int id, rat;
    string nick;
    cout << "Введите ID игрока: ";
    in >> id;
    in.ignore();
    cout << "Введите никнейм: ";
    getline(in, nick);
    cout << "Введите рейтинг (0-1000): ";
    in >> rat;
    setPlayerId(id);
    setNickname(nick);
    setRating(rat);

    TacticalAI::input(in);
    cout << "Введите успешность стратегий (%): ";
    in >> successRate;
    cout << "Введите знание карт (1-5): ";
    in >> mapKnowledge;
    return in;
}

// В Methods.cpp
ostream& Strategist::output(ostream& out) const {
    // Вместо вызова Player::output(out) вручную выводим данные базового класса
    out << "ID: " << getPlayerId() << "\nНикнейм: " << getNickname() << "\nРейтинг: " << getRating() << endl;
    TacticalAI::output(out);
    out << "Успешность стратегий: " << successRate << "%\nЗнание карт: " << mapKnowledge << endl;
    return out;
}

void Strategist::playRole() { cout << "Роль: Стратег" << endl; }
int Strategist::calculateImpact() { return successRate * 2 + mapKnowledge * 3; }
void Strategist::validate() {
    Player::validate();
    if (mapKnowledge >= 3) {
        cout << "Знание карт корректно (>=3)." << endl;
    }
    else {
        cout << "Ошибка: знание карт должно быть >=3!" << endl;
    }
}

void Strategist::predictEnemyMove() {
    cout << "Прогноз действий противника:\n";
    for (size_t i = 0; i < strategies.size(); ++i) {
        cout << i + 1 << ". " << strategies[i] << endl;
    }
}