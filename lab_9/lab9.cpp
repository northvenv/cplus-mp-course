#include <iostream>
#include <string>

using namespace std;

class Personality {
protected:
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
    
    virtual void show() const {
        cout << "Имя: " << name << ", Год: " << year << ", Описание: " << description << endl;
    }
    
    virtual ~Personality() {
        cout << "Personality: деструктор" << endl;
    }
};

class Artist : public Personality {
private:
    string style;
    
public:
    Artist() : Personality(), style("") {
        cout << "Artist: конструктор без параметров" << endl;
    }
    
    Artist(const string& n, int y, const string& d, const string& s) 
        : Personality(n, y, d), style(s) {
        cout << "Artist: конструктор с параметрами" << endl;
    }
    
    Artist(const Artist& other) : Personality(other), style(other.style) {
        cout << "Artist: конструктор копирования" << endl;
    }
    
    void show() const override {
        cout << "ХУДОЖНИК:" << endl;
        cout << "  Имя: " << name << endl;
        cout << "  Год рождения: " << year << endl;
        cout << "  Описание: " << description << endl;
        cout << "  Стиль: " << style << endl;
    }
    
    ~Artist() {
        cout << "Artist: деструктор" << endl;
    }
};

class Writer : public Personality {
private:
    string mainWork;
    
public:
    Writer() : Personality(), mainWork("") {
        cout << "Writer: конструктор без параметров" << endl;
    }
    
    Writer(const string& n, int y, const string& d, const string& work) 
        : Personality(n, y, d), mainWork(work) {
        cout << "Writer: конструктор с параметрами" << endl;
    }
    
    Writer(const Writer& other) : Personality(other), mainWork(other.mainWork) {
        cout << "Writer: конструктор копирования" << endl;
    }
    
    void show() const override {
        cout << "ПИСАТЕЛЬ:" << endl;
        cout << "  Имя: " << name << endl;
        cout << "  Год рождения: " << year << endl;
        cout << "  Описание: " << description << endl;
        cout << "  Главное произведение: " << mainWork << endl;
    }
    
    ~Writer() {
        cout << "Writer: деструктор" << endl;
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
    Personality p1("Суворов", 1730, "Полководец");
    p1.show();
    cout << endl;
    
    Artist a1("Репин", 1844, "Художник-передвижник", "Реализм");
    a1.show();
    cout << endl;
    
    Writer w1("Пушкин", 1799, "Поэт", "Евгений Онегин");
    w1.show();
    cout << endl;
    
    Personality* arr[3];
    
    arr[0] = new Personality("Ломоносов", 1711, "Ученый");
    arr[1] = new Artist("Айвазовский", 1817, "Моренист", "Романтизм");
    arr[2] = new Writer("Гоголь", 1809, "Писатель", "Мертвые души");
    
    for (int i = 0; i < 3; i++) {
        cout << i+1 << ". ";
        arr[i]->show();
        cout << endl;
    }
    
    Writer writers[2] = {
        Writer("Толстой", 1828, "Писатель", "Война и мир"),
        Writer("Достоевский", 1821, "Писатель", "Преступление и наказание")
    };
    
    for (int i = 0; i < 2; i++) {
        cout << i+1 << ". ";
        writers[i].show();
        cout << endl;
    }
    
    for (int i = 0; i < 3; i++) {
        delete arr[i];
    }
    
    return 0;
}