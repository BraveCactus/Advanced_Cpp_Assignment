
#include <iostream>
#include <string>
#include <vector>

//Базовый класс для контроьльных пунктов
class ControlPoint{
protected:
    std::string name;
    double latitude;
    double longitude;
public:
    ControlPoint(std::string n, double lat, double lon): name(n), latitude(lat), longitude(lon){}

    virtual ~ControlPoint() = default;

    std::string getName() const { return name; }
    double getLati() const { return latitude; }
    double getLong() const { return longitude; }
    
    virtual bool isObligatory() const = 0;
    virtual int getPenalty() const = 0;  

};

//Производный класс для обязательного КП
class ObligatoryControlPoint: public ControlPoint{
public:
    ObligatoryControlPoint(std::string n, double lat, double lon): ControlPoint(n, lat, lon){}

    bool isObligatory() const override{return true;}
    int getPenalty() const override {return 0;}  
};

//Производный класс для необязательного КП
class OptionalControlPoint: public ControlPoint{
private:
    int penalty;
public:
    OptionalControlPoint(std::string n, double lat, double lon, int p): ControlPoint(n, lat, lon), penalty(p){}
    
    bool isObligatory() const override {return false;}
    int getPenalty() const override {return penalty;}  
};

// Абстрактный строитель
class ControlPointBuilder {
public:
    virtual void processControlPoint(const ControlPoint& cp, int index) = 0;
    virtual void showResult() = 0;
    virtual ~ControlPointBuilder() = default;
};

// builder для вывода
class PrintBuilder: public ControlPointBuilder{
public:
    // Вывод сведений о КП
    void processControlPoint(const ControlPoint& cp, int index) override{
        std::cout << "Порядковый номер: " << index << std::endl;
        std::cout << "   Название: " << cp.getName() << std::endl;
        std::cout << "   Широта: " << cp.getLati() << " Долгота: " << cp.getLong() << std::endl;
        if (!cp.isObligatory())
        {
            std::cout << "   Штраф: " << cp.getPenalty() << std::endl;
        }
        std::cout<<std::endl;        
    }

    void showResult() override {
        // В этом строителе не требуется итоговый вывод
    }
};

// Класс для подсчета штрафа
class PenaltyCounter: public ControlPointBuilder{
private:
    int totalPenalty = 0;
public:
    // Подсчет итогового штрафа
    void processControlPoint(const ControlPoint& cp, int index) override{
        if (!cp.isObligatory())
        {
            totalPenalty += cp.getPenalty();
        }        
    }

    void showResult() override {
        std::cout << "Итоговый штраф: " << totalPenalty << std::endl;
    }
};

// Класс для управления процесса
class Manager{
private:
    std::vector<ControlPoint*> cp_arr;
public:
    Manager() = default;

    ~Manager(){
        for (auto cp: cp_arr)
        {
            delete cp;
        }        
    }

    void addControlPoint(ControlPoint* cp) {
        cp_arr.push_back(cp);
    }

    void process(ControlPointBuilder& builder) {
        for (size_t i = 0; i < cp_arr.size(); ++i) {
            builder.processControlPoint(*cp_arr[i], i + 1);
        }
        builder.showResult();
    }

};


int main(){

    Manager man;

    man.addControlPoint(new ObligatoryControlPoint("Старт", 12.5, 34.85));
    man.addControlPoint(new OptionalControlPoint("Ущелье", 23.45,35.23, 3));
    man.addControlPoint(new OptionalControlPoint("Гора", 1.5, 0.85, 6));
    man.addControlPoint(new ObligatoryControlPoint("Финиш", 47.6, 19.7));

    PrintBuilder print;
    man.process(print);

    PenaltyCounter pen;
    man.process(pen);
}