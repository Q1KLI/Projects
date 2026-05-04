#include "package_list.h"

using namespace std;

void PackageList::addPackage(package pkg) {
    q.push(pkg);
}

void PackageList::print() {
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
        cout << "Дата отправки:    " << pkg.date[0] << "." << pkg.date[1] << "." << pkg.date[2] << "\n";
        cout << "Пункт назначения: " << pkg.point << "\n\n";
    }
}

void PackageList::removePackage(int number) {
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
    if (found) cout << "Посылка №" << number << " удалена\n";
    else cout << "Посылка №" << number << " не найдена\n";
}

void PackageList::editPackage(int number, package newPkg) {
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
    if (found) cout << "Посылка #" << number << " изменена\n";
    else cout << "Посылка #" << number << " не найдена\n";
}

void PackageList::SecondQuarterReport() {
    if (q.empty()) {
        cout << "Список посылок пуст\n";
        return;
    }
    time_t now = time(nullptr);
    tm* ltm = localtime(&now);
    int currentYear = 1900 + ltm->tm_year;
    int lastYear = currentYear - 1;

    queue<package> temp = q;
    bool found = false;
    int count = 0;

    cout << "=== Отчет по посылкам за II квартал " << lastYear << " года ===\n\n";
    while (!temp.empty()) {
        package pkg = temp.front();
        temp.pop();
        if (pkg.date[2] == lastYear && pkg.date[1] >= 4 && pkg.date[1] <= 6) {
            found = true;
            count++;
            cout << "Посылка №" << pkg.number << " → " << pkg.point << "\n";
        }
    }
    if (!found) cout << "Посылок за прошлый год не найдено.\n";
    else cout << "\nВсего найдено: " << count << " посылок.\n";
}

void PackageList::TotalCostByPoint() {
    if (q.empty()) {
        cout << "Список посылок пуст\n";
        return;
    }
    struct PointCost { string point; int totalCost = 0; };
    stack<PointCost> resultStack;
    queue<package> temp = q;

    while (!temp.empty()) {
        package pkg = temp.front();
        temp.pop();
        bool found = false;
        stack<PointCost> tempStack;

        while (!resultStack.empty()) {
            PointCost pc = resultStack.top();
            resultStack.pop();
            if (pc.point == pkg.point) {
                pc.totalCost += pkg.cost;
                found = true;
            }
            tempStack.push(pc);
        }
        if (!found) {
            PointCost newPC; newPC.point = pkg.point; newPC.totalCost = pkg.cost;
            tempStack.push(newPC);
        }
        while (!tempStack.empty()) {
            resultStack.push(tempStack.top());
            tempStack.pop();
        }
    }

    cout << "=== Общая стоимость по пунктам ===\n\n";
    stack<PointCost> printStack = resultStack;
    while (!printStack.empty()) {
        PointCost pc = printStack.top();
        printStack.pop();
        cout << "Пункт: " << pc.point << " | Стоимость: " << pc.totalCost << " руб.\n";
    }
}
