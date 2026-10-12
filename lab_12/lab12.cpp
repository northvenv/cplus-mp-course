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
    
    Personality(const Personality& other) : name(other.name), year(other.year), description(other.description) {
        objectCount++;
    }
    
    virtual void show() const = 0;
    
    virtual Personality* clone() const = 0;
    
    static int getObjectCount() {
        return objectCount;
    }
    
    virtual ~Personality() {
        objectCount--;
    }
};

int Personality::objectCount = 0;

class Writer : public Personality {
public:
    Writer() : Personality() {}
    
    Writer(const string& n, int y, const string& d) : Personality(n, y, d) {}
    
    Writer(const Writer& other) : Personality(other) {}
    
    void show() const override {
        cout << name << " (" << year << ") - " << description << endl;
    }
    
    Personality* clone() const override {
        return new Writer(*this);
    }
};

class Encyclopedia {
private:
    string title;
    int publishYear;
    Personality** personalities;
    int count;
    static int arrayCount;
    
    void copyFrom(const Encyclopedia& other) {
        title = other.title;
        publishYear = other.publishYear;
        count = other.count;
        
        personalities = new Personality*[count + 1];
        for (int i = 0; i < count; i++) {
            personalities[i] = other.personalities[i]->clone();
        }
    }
    
    void clear() {
        for (int i = 0; i < count; i++) {
            delete personalities[i];
        }
        delete[] personalities;
        arrayCount -= count;
    }
    
public:
    Encyclopedia(const string& t, int y) : title(t), publishYear(y), count(0) {
        personalities = new Personality*[1];
    }
    
    Encyclopedia(const Encyclopedia& other) {
        copyFrom(other);
    }
    
    Encyclopedia& operator=(const Encyclopedia& other) {
        if (this != &other) {
            clear();
            copyFrom(other);
        }
        return *this;
    }
    
    Encyclopedia& operator+(Personality* p) {
        Personality** temp = new Personality*[count + 1];
        
        for (int i = 0; i < count; i++) {
            temp[i] = personalities[i];
        }
        
        temp[count] = p->clone();
        count++;
        arrayCount++;
        
        delete[] personalities;
        personalities = temp;
        return *this;
    }
    
    Encyclopedia& operator++() {
        Personality* p = new Writer();
        
        Personality** temp = new Personality*[count + 1];
        
        for (int i = 0; i < count; i++) {
            temp[i] = personalities[i];
        }
        
        temp[count] = p;
        count++;
        arrayCount++;
        
        delete[] personalities;
        personalities = temp;
        
        return *this;
    }
    
    Encyclopedia operator++(int) {
        Encyclopedia temp(*this);
        ++(*this);
        return temp;
    }
    
    Personality* operator[](int index) {
        if (index >= 0 && index < count) {
            return personalities[index];
        }
        return nullptr;
    }
    
    string getTitle() const { return title; }
    int getPublishYear() const { return publishYear; }
    int getCount() const { return count; }
    Personality** getPersonalities() const { return personalities; }
    
    static int getArrayCount() {
        return arrayCount;
    }
    
    ~Encyclopedia() {
        clear();
    }
};

int Encyclopedia::arrayCount = 0;

ostream& operator<<(ostream& os, const Encyclopedia& enc) {
    os << "Энциклопедия: " << enc.getTitle() << " (" << enc.getPublishYear() << ")" << endl;
    os << "Содержит " << enc.getCount() << " личностей:" << endl;
    
    Personality** persons = enc.getPersonalities();
    for (int i = 0; i < enc.getCount(); i++) {
        os << i+1 << ". ";
        persons[i]->show();
    }
    
    return os;
}

int main() {
    Encyclopedia enc("Современная литература", 2024);
    
    Writer* w1 = new Writer("Стругацкий", 1925, "Фантаст");
    Writer* w2 = new Writer("Лем", 1921, "Фантаст");
    Writer* w3 = new Writer("Брэдбери", 1920, "Фантаст");
    
    enc = enc + w1;
    enc = enc + w2;
    enc = enc + w3;
    
    cout << "После добавления через +:" << endl;
    cout << enc << endl;
    
    ++enc;
    cout << "После префиксного ++:" << endl;
    cout << enc << endl;
    
    enc++;
    cout << "После постфиксного ++:" << endl;
    cout << enc << endl;
    
    cout << "Доступ через []:" << endl;
    Personality* p = enc[1];
    if (p) {
        p->show();
    }
    
    delete w1;
    delete w2;
    delete w3;
    
    return 0;
}