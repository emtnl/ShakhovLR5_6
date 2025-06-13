#include <iostream>
#include <map>
#include <memory>
#include <functional>
#include <locale>
#include "Shakhovlr5_menue_functions.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    map<string, unique_ptr<Player>> players;

    using MenuItem = struct {
        string title;
        function<void()> action;
    };

    map<int, MenuItem> menu = {
        {1, {"Создать нового игрока", [&]() { case1(players); }}},
        {2, {"Показать всех игроков", [&]() { case2(players); }}},
        {3, {"Выполнить действие над игроком", [&]() { case3(players); }}},
        {4, {"Демонстрация конструкторов", case4}},
        {5, {"Демонстрация геттеров", case5}},
        {6, {"Демонстрация сеттеров", case6}},
        {7, {"Демонстрация методов", case7}},
        {8, {"Демонстрация перегрузок", case8}}
    };

    while (true) {
        cout << "\n===== МЕНЮ =====\n";
        for (const auto& item : menu) {
            cout << item.first << ". " << item.second.title << "\n";
        }
        cout << "0. Выход\n";

        int choice = EnterNumber<int>("Выберите пункт меню: ");
        if (choice == 0) {
            cout << "Завершение программы.\n";
            break;
        }

        auto it = menu.find(choice);
        if (it != menu.end()) {
            it->second.action();
        }
        else {
            cout << "Неверный выбор. Повторите.\n";
        }
    }

    return 0;
}
