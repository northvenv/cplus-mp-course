#include <iostream>
#include <string>

using namespace std;

class Personality {
private:
    string name;
    int year;
    string description;
    
public:
    Personality() : name(""), year(0), description("") {}
    
    Personality(const string& n, int y) : name(n), year(y), description("") {}
    
    Personality(const string& n, int y, const string& d) : name(n), year(y), description(d) {}
    
    void show() const {
        cout << "Имя: " << name << ", Год: " << year << ", Описание: " << description << endl;
    }
    
    void setName(const string& n) { name = n; }
    void setYear(int y) { year = y; }
    void setDescription(const string& d) { description = d; }
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
    }
    
    Encyclopedia(const string& t, int y) : title(t), publishYear(y), count(0) {
        personalities = new Personality[1];
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
    }
};

int main() {
    Encyclopedia enc;
    
    enc.setData("История в лицах", 2023);
    
    Personality p1("Иван Грозный", 1547, "Первый царь всея Руси");
    Personality p2("Петр I", 1682, "Основатель империи");
    
    enc.addPersonality(p1);
    enc.addPersonality(p2);
    
    Personality p3;
    p3.setName("Екатерина II");
    p3.setYear(1762);
    p3.setDescription("Императрица России");
    
    enc.addPersonality(p3);
    
    enc.display();
    
    return 0;
}