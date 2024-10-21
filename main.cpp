#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <map>
const std::map<std::string, double> ЦеныБензин = {
    {"АИ-92", 36.0},
    {"АИ-95", 39.0},
    {"ДТ-К5", 45.0},
};
const std::map<std::string, double> ЦеныМасло = {
    {"Синт", 1200.0},
    {"Полусинт", 1600.0},
    {"Минерал", 3500.0}
};


struct Automobile {
    std::string Фамилия;
    std::string VIN;
    std::string Марка;
    std::string Марка_топлива;
    int Мощность;
    double Объем;
    double Остаток_Бензина;
    double Объем_Масла;

    Automobile(Automobile& machine): Фамилия(machine.Фамилия),
    VIN(machine.VIN), Марка(machine.Марка),
    Марка_топлива(machine.Марка_топлива),
    Мощность(machine.Мощность), Объем(machine.Объем),
    Остаток_Бензина(machine.Остаток_Бензина),
    Объем_Масла(machine.Объем_Масла)
    {}

    Automobile(
        std::string фамилия,
        std::string номер,
        std::string марка,
        std::string марка_топлива,
        int мощность,
        double обьем,
        double обьем_масла,
        double остаток_бензы = 0
    ): Фамилия(фамилия), VIN(номер), Марка(марка), Марка_топлива(марка_топлива),
        Мощность(мощность), Объем(обьем), Остаток_Бензина(остаток_бензы), Объем_Масла(обьем_масла) {}

    bool operator==(Automobile& right) {
        if (this->Фамилия!=right.Фамилия or this->VIN!=right.VIN or this->Марка!=right.Марка
        or this->Марка_топлива!=right.Марка_топлива or this->Мощность!=right.Мощность
        or this->Объем!=right.Объем or this->Остаток_Бензина!=right.Остаток_Бензина
        or this->Объем_Масла!=right.Объем_Масла) {
            return false;
        }
        else {
            return true;
        }
    }
};


class DataBase {
private:
    std::vector<Automobile> Автомобили;
public:
    void AppendMachine(Automobile& machine) {
        Автомобили.push_back(Automobile(machine));
    }
    auto GetAutomobile() {
        return Автомобили.begin();
    }
};

auto operator<<(std::ostream& left, DataBase& right) {
    return right.GetAutomobile();
}
std::ostream operator>>(std::istream& left, DataBase& right) {
    std::string фамилия, номер, марка, марка_топлива;
    int мощность;
    double обьем, обьем_масла, остаток_бензы;
    left >> фамилия >> номер >> марка >> марка_топлива >> мощность >> обьем >> обьем_масла >> остаток_бензы;
    right.AppendMachine(Automobile(фамилия, номер, марка, марка_топлива, мощность, обьем, обьем_масла, остаток_бензы));
}

int main() {

    return 0;
}
