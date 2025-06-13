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
        {1, {"������� ������ ������", [&]() { case1(players); }}},
        {2, {"�������� ���� �������", [&]() { case2(players); }}},
        {3, {"��������� �������� ��� �������", [&]() { case3(players); }}},
        {4, {"������������ �������������", case4}},
        {5, {"������������ ��������", case5}},
        {6, {"������������ ��������", case6}},
        {7, {"������������ �������", case7}},
        {8, {"������������ ����������", case8}}
    };

    while (true) {
        cout << "\n===== ���� =====\n";
        for (const auto& item : menu) {
            cout << item.first << ". " << item.second.title << "\n";
        }
        cout << "0. �����\n";

        int choice = EnterNumber<int>("�������� ����� ����: ");
        if (choice == 0) {
            cout << "���������� ���������.\n";
            break;
        }

        auto it = menu.find(choice);
        if (it != menu.end()) {
            it->second.action();
        }
        else {
            cout << "�������� �����. ���������.\n";
        }
    }

    return 0;
}
