#include <iostream>
#include <string>

using namespace std;

class Personality {
protected:
    string name;
    int year;
    string description;
    
public:
    Personality() : name(""), year(0), description("") {}
    
    Personality(const string& n, int y) : name(n), year(y), description("") {}
    
    Personality(const string& n, int y, const string& d) : name(n), year(y), description(d) {}
    
    virtual void show() const = 0;
    
    virtual ~Personality() {}
};

class Artist : public Personality {
private:
    string style;
    
public:
    Artist() : Personality(), style("") {}
    
    Artist(const string& n, int y, const string& d, const string& s) 
        : Personality(n, y, d), style(s) {}
    
    void show() const override {
        cout << "ХУДОЖНИК" << endl;
        cout << "  Имя: " << name << endl;
        cout << "  Год рождения: " << year << endl;
        cout << "  Описание: " << description << endl;
        cout << "  Стиль: " << style << endl;
    }
};

class Writer : public Personality {
private:
    string mainWork;
    
public:
    Writer() : Personality(), mainWork("") {}
    
    Writer(const string& n, int y, const string& d, const string& work) 
        : Personality(n, y, d), mainWork(work) {}
    
    void show() const override {
        cout << "ПИСАТЕЛЬ" << endl;
        cout << "  Имя: " << name << endl;
        cout << "  Год рождения: " << year << endl;
        cout << "  Описание: " << description << endl;
        cout << "  Главное произведение: " << mainWork << endl;
    }
};

class Encyclopedia {
private:
    string title;
    int publishYear;
    Personality** personalities;
    int count;
    
public:
    Encyclopedia() : title(""), publishYear(0), count(0) {
        personalities = new Personality*[1];
    }
    
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
        cout << "=== ЭНЦИКЛОПЕДИЯ ===" << endl;
        cout << "Название: " << title << endl;
        cout << "Год издания: " << publishYear << endl;
        cout << "Количество личностей: " << count << endl;
        
        for (int i = 0; i < count; i++) {
            cout << i+1 << ". ";
            personalities[i]->show();
        }
    }
    
    ~Encyclopedia() {
        for (int i = 0; i < count; i++) {
            delete personalities[i];
        }
        delete[] personalities;
    }
};

int main() {
    Personality* arr[4];
    
    arr[0] = new Artist("Репин", 1844, "Художник-передвижник", "Реализм");
    arr[1] = new Writer("Пушкин", 1799, "Поэт", "Евгений Онегин");
    arr[2] = new Artist("Айвазовский", 1817, "Моренист", "Романтизм");
    arr[3] = new Writer("Гоголь", 1809, "Писатель", "Мертвые души");
    
    for (int i = 0; i < 4; i++) {
        arr[i]->show();
    }
    
    Encyclopedia enc("Великие люди России", 2023);
    
    enc.addPersonality(new Artist("Шишкин", 1832, "Пейзажист", "Реализм"));
    enc.addPersonality(new Writer("Толстой", 1828, "Писатель", "Война и мир"));
    enc.addPersonality(new Artist("Ван Гог", 1853, "Художник", "Постимпрессионизм"));
    enc.addPersonality(new Writer("Достоевский", 1821, "Писатель", "Преступление и наказание"));
    
    enc.display();
    
    for (int i = 0; i < 4; i++) {
        delete arr[i];
    }
    
    return 0;
}