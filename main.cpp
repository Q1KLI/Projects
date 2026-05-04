#include <windows.h>
#include "package_list.h"

using namespace std;

package ReadPkgFromConsole() {
    package p;
    cout << "Введите номер, вес, стоимость, дату(д м г) и пункт:\n";
    cin >> p.number >> p.weight >> p.cost >> p.date[0] >> p.date[1] >> p.date[2] >> p.point;
    return p;
}

package ExamplePackage(int num, string city) {
    package p = {num, 10, 100, {1, 5, 2025}, city}; // Пример для II квартала 2025
    return p;
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    PackageList list;
    list.addPackage(ExamplePackage(1, "Bobruysk"));
    list.addPackage(ExamplePackage(2, "Pyt-Yah"));

    list.print();
    list.SecondQuarterReport();
    list.TotalCostByPoint();

    return 0;
}
