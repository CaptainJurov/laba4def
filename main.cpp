#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
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

    Automobile() {}

    Automobile(const Automobile& machine): Фамилия(machine.Фамилия),
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
    friend std::ostream& operator<<(std::ostream& os, Automobile& Машина) {
        std::cout<<Машина.Фамилия;
        os << "Фамилия: " << Машина.Фамилия << ", VIN: " << Машина.VIN << ", Марка: "<<Машина.Марка;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Automobile& Машина) {
        is >> Машина.Фамилия >> Машина.VIN >> Машина.Марка >> Машина.Марка_топлива >> Машина.Мощность >> Машина.Объем >> Машина.Остаток_Бензина >> Машина.Объем_Масла;
        return is;
    }
    
    friend bool operator<(const Automobile& left, const Automobile& right) {
        if (left.Мощность<right.Мощность) {
            return true;
        }
        else {return false;}
    }
};


class DataBase {
private:
    std::vector<Automobile> Автомобили;
public:
    void AppendMachine(const Automobile& machine) {
        Автомобили.push_back(Automobile(machine));
    }
    friend std::istream& operator<<(std::istream& is, DataBase& db) {
        Automobile machine;
        is >> machine;
        db.AppendMachine(machine);
        return is;
    }
    std::vector<Automobile> поискПоМаркеЛинейный(std::string VIN) {
    std::vector<Automobile> найденные;
    for (auto car = Автомобили.begin(); car != Автомобили.end(); car++) {
        auto i = std::find_if(car, Автомобили.end(), [VIN](Automobile& left) {return left.VIN==VIN;});
        найденные.push_back(*i);
        // next(car);
    }
    return найденные;
    }

    bool поискПоМаркеБинарный(Automobile& machine) {
        std::sort(Автомобили.begin(), Автомобили.end(), [](Automobile& a, Automobile& b) {
            return a.VIN < b.VIN;
        });
        return std::binary_search(Автомобили.begin(), Автомобили.end(), machine);
}
};

int main() {
    DataBase *db = new DataBase();
    db->AppendMachine(Automobile("Zalupenko", "Z1488OV", "Lada", "АИ-95", 100, 30, 1, 0));
    db->AppendMachine(Automobile("Shaurbekov", "Z1488OV", "Matiz", "АИ-95", 50, 30, 1, 0));
    db->AppendMachine(Automobile("Bekbekov", "Z1477OV", "Matiz", "АИ-95", 50, 30, 1, 0));
    auto machine = Automobile("Ohlobusting", "R787US", "Лада", "АИ-95", 100, 30, 1, 0);
    if (db->поискПоМаркеБинарный(machine)) {
        std::cout<<"FIND\n";
    };
    auto baze = db->поискПоМаркеЛинейный("Z1488OV");
    for (auto i:baze) {
        std::cout<<i.Фамилия<<"\n";
    }
    std::cout<<"Gotovo\n";
    return 0;
}
