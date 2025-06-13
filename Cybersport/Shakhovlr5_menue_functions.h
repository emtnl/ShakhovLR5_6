#pragma once
#pragma once
#include <iostream>
#include <map>
#include <memory>
#include <limits>
#include "Shakhov_LR5_defPlayer.h"
#include "Shakhov_LR5_AbstractPlayer.h"
#include "Shakhov_LR5_ChildSniper.h"
#include "Shakhov_LR5_ChildSupport.h"
#include "Shakhov_LR5_ParentSniper.h"
#include "Shakhov_LR5_Multi_TacticalAI.h"

using namespace std;

template<typename T>
T EnterNumber(const string& prompt) {
    T value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка. Повторите ввод.\n";
    }
}

string EnterString(const string& prompt) {
    string value;
    cout << prompt;
    getline(cin, value);
    while (value.empty()) {
        cout << "Строка не может быть пустой. Повторите ввод: ";
        getline(cin, value);
    }
    return value;
}

void case1(map<string, unique_ptr<Player>>& players) {
    int choice = EnterNumber<int>("Выберите тип игрока:\n1. Снайпер\n2. Поддержка\n3. Стратег\nВыбор: ");
    string id = EnterString("Введите ID игрока: ");

    if (players.find(id) != players.end()) {
        cout << "Игрок с таким ID уже существует.\n";
        return;
    }

    try {
        switch (choice) {
        case 1: {
            int hsa = EnterNumber<int>("Введите точность хедшотов (%): ");
            int lrk = EnterNumber<int>("Введите количество дальних убийств: ");
            //проверка  на валидность
            players[id] = make_unique<Sniper>(stoi(id), "Sniper_" + id, 0, hsa, lrk);
            break;
        }
        case 2: {
            int hpm = EnterNumber<int>("Введите количество лечений за матч: ");
            int util = EnterNumber<int>("Введите использование утилит: ");
            players[id] = make_unique<Support>(stoi(id), "Support_" + id, 0, hpm, util);
            break;
        }
        case 3: {
            int success = EnterNumber<int>("Введите успешность (%): ");
            int knowledge = EnterNumber<int>("Введите знание карты (1-5): ");
            players[id] = make_unique<Strategist>(stoi(id), "Strategist_" + id, 0, success, knowledge);
            break;
        }
        default:
            cout << "Неверный выбор.\n";
        }
    }
    catch (const exception& e) {
        cout << "Ошибка создания игрока: " << e.what() << endl;
    }
}

void case2(const map<string, unique_ptr<Player>>& players) {
    if (players.empty()) {
        cout << "Список игроков пуст.\n";
        return;
    }

    cout << "Количество уникальных игроков: " << players.size() << endl;
    for (const auto& pair : players) {
        const string& id = pair.first;
        const auto& player = pair.second;
        cout << "ID: " << id << "\n" << *player;
        player->playRole();
        player->validate();
        cout << endl;
    }
}


void case3(map<string, unique_ptr<Player>>& players) {
    string id = EnterString("Введите ID игрока: ");
    auto it = players.find(id);
    if (it == players.end()) {
        cout << "Игрок не найден.\n";
        return;
    }

    int action = EnterNumber<int>("Выберите действие:\n1. PlayRole()\n2. validate()\n3. predictEnemyMove()\n4. input()\n5. output()\nВыбор: ");

    try {
        switch (action) {
        case 1: it->second->playRole(); break;
        case 2: it->second->validate(); break;
        case 3:
            if (auto* strat = dynamic_cast<Strategist*>(it->second.get()))
                strat->predictEnemyMove();
            else cout << "Только для Стратега.\n";
            break;
        case 4: cin >> *(it->second); break;
        case 5: cout << *(it->second); break;
        default: cout << "Неверное действие.\n";
        }
    }
    catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void case4() {
    cout << "=== Демонстрация конструкторов ===\n";
    Sniper s1; cout << "Sniper(): " << s1 << endl;
    Sniper s2(1, "S", 500, 80, 10); cout << "Sniper(...): " << s2 << endl;
    Sniper s3(s2); cout << "Sniper(copy): " << s3 << endl;
    Sniper s4("QuickNick"); cout << "Sniper(string): " << s4 << endl;

    Support sup(2, "Support", 600, 20, 10); cout << "Support: " << sup << endl;
    Strategist strat(3, "Strat", 700, 85, 3); cout << "Strategist: " << strat << endl;
}

void case5() {
    cout << "=== Демонстрация геттеров ===\n";
    Sniper s(1, "S", 500, 85, 15);
    cout << "ID: " << s.getPlayerId() << ", Nick: " << s.getNickname() << ", Rating: " << s.getRating()
        << ", Headshot: " << s.getHeadshotAccuracy() << ", LRK: " << s.getLongRangeKills() << endl;

    Support su(2, "SU", 600, 30, 12);
    cout << "Heals: " << su.getHealsPerMatch() << ", Util: " << su.getUtility10() << endl;

    Strategist st(3, "ST", 700, 90, 5);
    cout << "Success: " << st.getSuccessRate() << ", Map: " << st.getMapKnowledge() << endl;
    for (const auto& str : st.getStrategies()) cout << str << ", ";
    cout << endl;
}

void case6() {
    cout << "=== Демонстрация сеттеров ===\n";
    Sniper s(1, "Old", 500, 85, 15);
    s.setPlayerId(10); s.setNickname("New"); s.setRating(800);
    s.setHeadshotAccuracy(90); s.setLongRangeKills(25);
    cout << "Sniper изменён: " << s << endl;

    Support su(2, "OldS", 600, 30, 12);
    su.setHealsPerMatch(40); su.setUtilityUsage(20);
    cout << "Support изменён: " << su << endl;

    Strategist st(3, "OldSt", 700, 90, 4);
    st.setSuccessRate(100); st.setMapKnowledge(5);
    st.setStrategies({ "Тактика 1", "Тактика 2" });
    cout << "Strategist изменён: " << st << endl;
}

void case7() {
    cout << "=== Демонстрация методов ===\n";
    Sniper s(1, "S", 500, 85, 15);
    s.playRole(); cout << "Impact: " << s.calculateImpact() << endl;
    s.validate(); s.upgradeScope(); cout << s << endl;

    Support su(2, "SU", 600, 30, 12);
    su.playRole(); cout << "Impact: " << su.calculateImpact() << endl;
    su.validate(); su.deployShield();

    Strategist st(3, "ST", 700, 90, 4);
    st.playRole(); cout << "Impact: " << st.calculateImpact() << endl;
    st.validate(); st.predictEnemyMove();
}

void case8() {
    cout << "=== Демонстрация перегрузок ===\n";
    Sniper s1(1, "A", 500, 80, 10), s2(2, "B", 600, 85, 12);
    auto sum = s1 + s2; cout << "Сумма снайперов: " << *sum << endl;

    Support su1(3, "X", 700, 30, 15), su2(4, "Y", 800, 35, 18);
    auto sum2 = su1 + su2; cout << "Сумма поддержки: " << *sum2 << endl;

    Strategist st(5, "T", 900, 95, 4);
    cout << "Тактика[0]: " << st[0] << endl;
}
