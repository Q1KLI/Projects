#include <iostream>
#include <string>
#include <windows.h>
#include <queue>
#include <stack>
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

            void SecondQuarterReport() {
                if (q.empty()) {
                    cout << "Список посылок пуст\n";
                    return;
                }

                // Получаем текущий год
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

                    int month = pkg.date[1];  // месяц
                    int year = pkg.date[2];   // год

                    if (year == lastYear && month >= 4 && month <= 6) {
                        found = true;
                        count++;
                        cout << "Посылка №" << pkg.number
                             << " → " << pkg.point << "\n";
                    }
                }

                if (!found) {
                    cout << "Посылок, отправленных во втором квартале прошлого года, не найдено.\n";
                } else {
                    cout << "\nВсего найдено: " << count << " посылок.\n";
                }
            }

            void TotalCostByPoint() {
                if (q.empty()) {
                    cout << "Список посылок пуст\n";
                    return;
                }

                // Структура для хранения пункта и суммарной стоимости
                struct PointCost {
                    string point;
                    int totalCost = 0;
                };

                stack<PointCost> resultStack;     // Стек для группировки
                queue<package> temp = q;

                // Обрабатываем все посылки
                while (!temp.empty()) {
                    package pkg = temp.front();
                    temp.pop();

                    bool found = false;

                    // Создаём временный стек для поиска
                    stack<PointCost> tempStack;

                    // Ищем пункт назначения в resultStack
                    while (!resultStack.empty()) {
                        PointCost pc = resultStack.top();
                        resultStack.pop();

                        if (pc.point == pkg.point) {
                            pc.totalCost += pkg.cost;
                            tempStack.push(pc);
                            found = true;
                        } else {
                            tempStack.push(pc);
                        }
                    }

                    // Если пункт не найден — создаём новую запись
                    if (!found) {
                        PointCost newPC;
                        newPC.point = pkg.point;
                        newPC.totalCost = pkg.cost;
                        tempStack.push(newPC);
                    }

                    // Возвращаем данные обратно в resultStack
                    while (!tempStack.empty()) {
                        resultStack.push(tempStack.top());
                        tempStack.pop();
                    }
                }

                // Вывод результата
                if (resultStack.empty()) {
                    cout << "Нет данных\n";
                    return;
                }

                cout << "=== Общая стоимость посылок по пунктам назначения ===\n\n";

                // Выводим из стека (в обратном порядке)
                stack<PointCost> printStack = resultStack;  // копия для вывода

                while (!printStack.empty()) {
                    PointCost pc = printStack.top();
                    printStack.pop();
                    cout << "Пункт: " << pc.point
                         << " | Общая стоимость: " << pc.totalCost << " руб.\n";
                }

                cout << "\nОтчет сформирован с использованием стека.\n";
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

    l.SecondQuarterReport();
    l.TotalCostByPoint();
    return 0;
}
