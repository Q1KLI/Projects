#define PACKAGE_LIST_H

#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <ctime>

struct package {
    int number;
    int weight;
    int cost;
    int date[3];
    std::string point;
};

struct PackageList {
    std::queue<package> q;

    void addPackage(package pkg);
    void print();
    void removePackage(int number);
    void editPackage(int number, package newPkg);
    void SecondQuarterReport();
    void TotalCostByPoint();
};
