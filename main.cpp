#include <iostream>
#include <string>
#include <windows.h>
#include <queue>
using namespace std;

struct package {
    int number;
    int weight;
    int cost;
    int date[3];
    string point;
};

struct list {
    queue<package> q;

    void addPackage(package pkg) {
        q.push(pkg);
    }

    void print() {
        if (q.empty()) {
            cout << "Список посылок пуст\n";
            return;
        }
        queue<package> temp = q;
        int i = 1;
        while (!temp.empty()) {
            package pkg = temp.front();
            temp.pop();
            cout << "=== Посылка №" << i++ << " ===\n";
            cout << "Номер:            " << pkg.number << "\n";
            cout << "Вес:              " << pkg.weight << " кг\n";
            cout << "Стоимость:        " << pkg.cost << " руб.\n";
            cout << "Дата отправки:    "
                 << pkg.date[0] << "."
                 << pkg.date[1] << "."
                 << pkg.date[2] << "\n";
            cout << "Пункт назначения: " << pkg.point << "\n\n";
        }
    }

    void removePackage(int number) {
            queue<package> temp;
            bool found = false;
            while (!q.empty()) {
                package pkg = q.front();
                q.pop();
                if (pkg.number == number && !found) {
                    found = true;
                } else {
                    temp.push(pkg);
                }
            }
            q = temp;
            if (found)
                cout << "Посылка №" << number << " удалена\n";
            else
                cout << "Посылка №" << number << " не найдена\n";
        }

        void editPackage(int number, package newPkg) {
                queue<package> temp;
                bool found = false;
                while (!q.empty()) {
                    package pkg = q.front();
                    q.pop();
                    if (pkg.number == number && !found) {
                        temp.push(newPkg);
                        found = true;
                    } else {
                        temp.push(pkg);
                    }
                }
                q = temp;
                if (found)
                    cout << "Посылка #" << number << " изменена\n";
                else
                    cout << "Посылка #" << number << " не найдена\n";
            }
};

package ReadPkgFromConsole() {
    package p;
    cout << "Введите номер посылки \n";
    cin >> p.number;
    cout << "Введите вес посылки \n";
    cin >> p.weight;
    cout << "Введите стоимость посылки \n";
    cin >> p.cost;
    cout << "Введите дату отправки (день месяц год) посылки \n";
    for (int i = 0; i < 3; i++) {
        cin >> p.date[i];
    }
    cout << "Введите пункт назначения посылки \n";
    cin >> p.point;
    return p;
}

package ExamplePackage() {
    package p;
    p.number = 1;
    p.weight = 10;
    p.cost = 20;
    p.date[0] = 1;
    p.date[1] = 1;
    p.date[2] = 2001;
    p.point = "Bobruysk";
    return p;
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    package p = ExamplePackage();
    package p2 = ExamplePackage();
    p2.number = 2;
    list l;
    l.addPackage(p);
    l.addPackage(p2);
    l.print();

    l.removePackage(1);
    l.print();

    p2.point = "pyt-yah";
    l.editPackage(2, p2);
    l.print();
    return 0;
}
