#include <iostream>
#include <iterator>
#include <ostream>
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

    bool operator==(const int& right) {return right==Мощность;}
    bool operator==(const std::string& right) {return right==Фамилия or right==VIN or right==Марка or right==Марка_топлива;}
    bool operator==(const double& right) {return right==Объем or right==Остаток_Бензина or right==Объем_Масла;}
    
    friend std::ostream& operator<<(std::ostream& os, const Automobile& Машина) {
        os << "Фамилия: " << Машина.Фамилия << ", VIN: " << Машина.VIN << ", Марка: "<<Машина.Марка<<" , Бензин: "<<Машина.Марка_топлива;
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
public:
    std::vector<Automobile> Автомобили;
    void AppendMachine(const Automobile& machine) {
        Автомобили.push_back(Automobile(machine));
    }
    friend std::istream& operator<<(std::istream& is, DataBase& db) {
        Automobile machine;
        is >> machine;
        db.AppendMachine(machine);
        return is;
    }

    template<typename T>
    std::vector<Automobile> поискЛинейный(const T& param) {
        std::vector<Automobile> найденные;
        auto it_first = Автомобили.begin();
        auto it_second = Автомобили.end();
        
        while (true) {
            auto it_buf = std::find_if(it_first, it_second, [param](Automobile& left){return left==param;});
            if (it_buf != it_second) {найденные.push_back(Automobile(*it_buf));}
            else break;
            it_first = it_buf+1;
        }
    return найденные;
    }

    bool поискБинарный(Automobile& machine) {
        std::sort(Автомобили.begin(), Автомобили.end(), [](Automobile& a, Automobile& b) {
            return a.VIN < b.VIN;
        });
        return std::binary_search(Автомобили.begin(), Автомобили.end(), machine);
    }
};

void Вывод(const std::vector<Automobile>& век) {
    std::copy(
        век.begin(),
        век.end(),
        std::ostream_iterator<Automobile>(std::cout, "\n")
    );
}

int main() {
    DataBase *db = new DataBase();
    db->AppendMachine(Automobile("Zalupenko", "ВO04КО", "Lada", "АИ-92", 100, 30, 1, 0));
    db->AppendMachine(Automobile("Shaurbekov", "В777ОР", "Matiz", "АИ-95", 50, 30, 1, 0));
    db->AppendMachine(Automobile("Bekbekov", "Х069ЕР", "Matiz", "АИ-95", 50, 30, 1, 0));
    std::cout<<"Фам|Ном|Мар|Топ|Двиг|Обьем|Ост|Масл"<<"\n";
    
    auto machine = Automobile("Ohlobusting", "R787US", "Лада", "АИ-92", 99, 29, 0, 0);
    if (db->поискБинарный(machine)) {
        std::cout<<"FIND\n";
    };
    
    std::copy(
        std::istream_iterator<Automobile>(std::cin),
        std::istream_iterator<Automobile> (),
        std::back_inserter(db->Автомобили)
    );
    
    Вывод(db->Автомобили);
    
    std::cout<<"Gotovo\n";

    auto baze = db->поискЛинейный("АИ-95");
    Вывод(baze);
    return 0;
}
