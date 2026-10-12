#include <iostream>
#include <string>

using namespace std;

class Personality {
protected:
    string name;
    int year;
    string description;
    static int objectCount;
    
public:
    Personality() : name("Неизвестно"), year(0), description("Нет описания") {
        objectCount++;
    }
    
    Personality(const string& n, int y, const string& d) : name(n), year(y), description(d) {
        objectCount++;
    }
    
    virtual void show() const = 0;
    
    static int getObjectCount() {
        return objectCount;
    }
    
    virtual ~Personality() {
        objectCount--;
    }
};

int Personality::objectCount = 0;

class Artist : public Personality {
private:
    string style;
    
public:
    Artist() : Personality(), style("Неизвестно") {}
    
    Artist(const string& n, int y, const string& d, const string& s) 
        : Personality(n, y, d), style(s) {}
    
    void show() const override {
        cout << "Художник: " << name << " - " << style << endl;
    }
};

class Writer : public Personality {
private:
    string mainWork;
    
public:
    Writer() : Personality(), mainWork("Неизвестно") {}
    
    Writer(const string& n, int y, const string& d, const string& work) 
        : Personality(n, y, d), mainWork(work) {}
    
    void show() const override {
        cout << "Писатель: " << name << " - " << mainWork << endl;
    }
};

class Encyclopedia {
private:
    string title;
    int publishYear;
    Personality** personalities;
    int count;
    static int arrayCount;
    
public:
    Encyclopedia(const string& t, int y) : title(t), publishYear(y), count(0) {
        personalities = new Personality*[1];
    }
    
    void addPersonality(Personality* p) {
        Personality** temp = new Personality*[count + 1];
        
        for (int i = 0; i < count; i++) {
            temp[i] = personalities[i];
        }
        
        temp[count] = p;
        count++;
        arrayCount++;
        
        delete[] personalities;
        personalities = temp;
    }
    
    void setData(const string& t) {
        title = t;
    }
    
    void setData(const string& t, int y) {
        title = t;
        publishYear = y;
    }
    
    void display() const {
        cout << title << " (" << publishYear << "):" << endl;
        for (int i = 0; i < count; i++) {
            personalities[i]->show();
        }
    }
    
    static int getArrayCount() {
        return arrayCount;
    }
    
    ~Encyclopedia() {
        for (int i = 0; i < count; i++) {
            delete personalities[i];
        }
        delete[] personalities;
        arrayCount -= count;
    }
};

int Encyclopedia::arrayCount = 0;

int main() {
    cout << "Всего объектов Personality до создания: " << Personality::getObjectCount() << endl;
    cout << "Объектов в массивах: " << Encyclopedia::getArrayCount() << endl;
    cout << endl;
    
    Artist* a1 = new Artist("Репин", 1844, "Художник", "Реализм");
    Artist* a2 = new Artist("Айвазовский", 1817, "Моренист", "Романтизм");
    Writer* w1 = new Writer("Пушкин", 1799, "Поэт", "Евгений Онегин");
    Writer* w2 = new Writer("Гоголь", 1809, "Писатель", "Мертвые души");
    
    cout << "После создания 4 объектов: " << Personality::getObjectCount() << endl;
    cout << endl;
    
    Encyclopedia enc1("Русское искусство", 2023);
    
    enc1.addPersonality(a1);
    enc1.addPersonality(a2);
    enc1.addPersonality(w1);
    enc1.addPersonality(w2);
    
    cout << "После добавления в массив: " << Personality::getObjectCount() << endl;
    cout << "Объектов в массивах: " << Encyclopedia::getArrayCount() << endl;
    cout << endl;
    
    enc1.display();
    cout << endl;
    
    Encyclopedia enc2("Зарубежное искусство", 2023);
    
    Artist* a3 = new Artist("Ван Гог", 1853, "Художник", "Постимпрессионизм");
    Writer* w3 = new Writer("Шекспир", 1564, "Драматург", "Гамлет");
    
    enc2.addPersonality(a3);
    enc2.addPersonality(w3);
    
    cout << "Всего объектов Personality: " << Personality::getObjectCount() << endl;
    cout << "Объектов в массивах: " << Encyclopedia::getArrayCount() << endl;
    cout << endl;
    
    enc2.display();
    cout << endl;
    
    cout << "Итоговые значения:" << endl;
    cout << "Всего объектов Personality: " << Personality::getObjectCount() << endl;
    cout << "Объектов в массивах Encyclopedia: " << Encyclopedia::getArrayCount() << endl;
    
    return 0;
}