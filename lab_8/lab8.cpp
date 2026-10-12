#include <iostream>
#include <string>

using namespace std;

class Personality {
private:
    string name;
    int year;
    string description;
    
public:
    Personality() : name(""), year(0), description("") {
        cout << "Personality: конструктор без параметров" << endl;
    }
    
    Personality(const string& n, int y) : name(n), year(y), description("") {
        cout << "Personality: конструктор с 2 параметрами" << endl;
    }
    
    Personality(const string& n, int y, const string& d) : name(n), year(y), description(d) {
        cout << "Personality: конструктор с 3 параметрами" << endl;
    }
    
    Personality(const Personality& other) : name(other.name), year(other.year), description(other.description) {
        cout << "Personality: конструктор копирования" << endl;
    }
    
    void show() const {
        cout << "Имя: " << name << ", Год: " << year << ", Описание: " << description << endl;
    }
    
    void setName(const string& n) { name = n; }
    void setYear(int y) { year = y; }
    void setDescription(const string& d) { description = d; }
    
    ~Personality() {
        cout << "Personality: деструктор для " << name << endl;
    }
};

class Encyclopedia {
private:
    string title;
    int publishYear;
    Personality* personalities;
    int count;
    
public:
    Encyclopedia() : title(""), publishYear(0), count(0) {
        personalities = new Personality[1];
        cout << "Encyclopedia: конструктор без параметров" << endl;
    }
    
    Encyclopedia(const string& t, int y) : title(t), publishYear(y), count(0) {
        personalities = new Personality[1];
        cout << "Encyclopedia: конструктор с параметрами" << endl;
    }
    
    Encyclopedia(const Encyclopedia& other) : title(other.title), publishYear(other.publishYear), count(other.count) {
        personalities = new Personality[count + 1];
        for (int i = 0; i < count; i++) {
            personalities[i] = other.personalities[i];
        }
        cout << "Encyclopedia: конструктор копирования" << endl;
    }
    
    void addPersonality(const Personality& p) {
        Personality* temp = new Personality[count + 1];
        
        for (int i = 0; i < count; i++) {
            temp[i] = personalities[i];
        }
        
        temp[count] = p;
        count++;
        
        delete[] personalities;
        personalities = temp;
    }
    
    void addPersonalityWithParams(const string& n, int y, const string& d) {
        Personality p(n, y, d);
        addPersonality(p);
    }
    
    void addCopies(const Personality& p, int num) {
        for (int i = 0; i < num; i++) {
            Personality copy(p);
            addPersonality(copy);
        }
    }
    
    void setData(const string& t) {
        title = t;
    }
    
    void setData(const string& t, int y) {
        title = t;
        publishYear = y;
    }
    
    void display() const {
        cout << "Энциклопедия: " << title << ", Год издания: " << publishYear << endl;
        cout << "Содержит " << count << " личностей:" << endl;
        
        for (int i = 0; i < count; i++) {
            cout << i+1 << ". ";
            personalities[i].show();
        }
    }
    
    ~Encyclopedia() {
        delete[] personalities;
        cout << "Encyclopedia: деструктор для " << title << endl;
    }
};

int main() {
    Encyclopedia enc1;
    enc1.setData("История России", 2023);
    
    Personality p1("Иван Грозный", 1547, "Первый царь");
    Personality p2("Петр I", 1682, "Основатель империи");
    
    enc1.addPersonality(p1);
    enc1.addPersonality(p2);
    
    enc1.addPersonalityWithParams("Екатерина II", 1762, "Императрица");
    
    Personality p3("Александр I", 1801, "Император");
    enc1.addCopies(p3, 2);
    
    Encyclopedia enc2 = enc1;
    enc2.setData("Копия энциклопедии", 2024);
    
    enc1.display();
    cout << endl;
    enc2.display();
    
    return 0;
}