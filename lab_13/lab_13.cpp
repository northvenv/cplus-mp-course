#include <iostream>
#include <string>
#include <algorithm>

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
    
    virtual ~Personality() {
        objectCount--;
    }
    
    virtual void show() const = 0;
    virtual Personality* clone() const = 0;
    
    static int getObjectCount() {
        return objectCount;
    }

    int getYear() const { return year; }
    string getName() const { return name; }

    bool operator<(const Personality& other) const {
        return this->year < other.year;
    }

    bool operator>(const Personality& other) const {
        return this->year > other.year;
    }
};

int Personality::objectCount = 0;

class Writer : public Personality {
public:
    Writer() : Personality() {}
    Writer(const string& n, int y, const string& d) : Personality(n, y, d) {}
    Writer(const Writer& other) : Personality(other) {}
    
    void show() const override {
        cout << "[Writer] " << name << " (" << year << ") - " << description << endl;
    }
    
    Personality* clone() const override {
        return new Writer(*this);
    }
};

class Scientist : public Personality {
private:
    string field;
public:
    Scientist() : Personality(), field("Неизвестно") {}
    Scientist(const string& n, int y, const string& d, const string& f) 
        : Personality(n, y, d), field(f) {}
    Scientist(const Scientist& other) : Personality(other), field(other.field) {}

    void show() const override {
        cout << "[Scientist] " << name << " (" << year << "), область: " << field << " - " << description << endl;
    }

    Personality* clone() const override {
        return new Scientist(*this);
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
        
        personalities = new Personality*[static_cast<size_t>(count) + 1];
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
        Personality** temp = new Personality*[static_cast<size_t>(count) + 1];
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
        Writer* p = new Writer();
        *this = *this + p;
        delete p;
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

template <typename U>
struct Comparator {
    static bool less(const U& a, const U& b) { return a < b; }
    static bool greater(const U& a, const U& b) { return a > b; }
};

template <typename U>
struct Comparator<U*> {
    static bool less(const U* a, const U* b) {
        if (!a || !b) return false;
        return *a < *b;
    }
    static bool greater(const U* a, const U* b) {
        if (!a || !b) return false;
        return *a > *b;
    }
};

template <typename T>
class ArrayContainer {
private:
    T* data;
    size_t size;
    size_t capacity;

public:
    ArrayContainer(int n) : size(0), capacity(static_cast<size_t>(n)) {
        data = new T[capacity]; 
    }

    ~ArrayContainer() {
        delete[] data;
    }

    void add(T item) {
        if (size < capacity) {
            data[size++] = item;
        } else {
            cout << "Ошибка: массив переполнен!" << endl;
        }
    }

    T get(int index) const {
        if (index >= 0 && static_cast<size_t>(index) < size) {
            return data[index];
        }
        throw out_of_range("Индекс вне диапазона");
    }

    int getSize() const { return static_cast<int>(size); }

    T min() const {
        if (size == 0) throw runtime_error("Массив пуст");
        T minVal = data[0];
        for (size_t i = 1; i < size; i++) {
            if (Comparator<T>::less(data[i], minVal)) {
                minVal = data[i];
            }
        }
        return minVal;
    }

    T max() const {
        if (size == 0) throw runtime_error("Массив пуст");
        T maxVal = data[0];
        for (size_t i = 1; i < size; i++) {
            if (Comparator<T>::greater(data[i], maxVal)) {
                maxVal = data[i];
            }
        }
        return maxVal;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    Encyclopedia enc("Мировые личности", 2024);
    
    Writer w_1("Достоевский", 1821, "Русский классик");
    Writer w_2("Толстой", 1828, "Автор 'Войны и мира'");
    
    enc = enc + &w_1;
    enc = enc + &w_2;
    
    ++enc;
    
    cout << enc << endl;
    cout << "Всего создано объектов Personality: " << Personality::getObjectCount() << endl;
    
    cout << "--- Тест с int ---" << endl;
    ArrayContainer<int> intArr(5);
    intArr.add(10); intArr.add(5); intArr.add(20); intArr.add(1);
    cout << "Min int: " << intArr.min() << " | Max int: " << intArr.max() << endl;

    cout << "\n--- Тест с char ---" << endl;
    ArrayContainer<char> charArr(3);
    charArr.add('x'); charArr.add('b'); charArr.add('z');
    cout << "Min char: " << charArr.min() << " | Max char: " << charArr.max() << endl;

    cout << "\n--- Тест с Personality* ---" << endl;
    ArrayContainer<Personality*> ptrArr(3);
    Writer* p1 = new Writer("Чехов", 1860, "Драматург");
    Scientist* p2 = new Scientist("Менделеев", 1834, "Химик", "Химия");
    Writer* p3 = new Writer("Пушкин", 1799, "Поэт");
    
    ptrArr.add(p1); ptrArr.add(p2); ptrArr.add(p3);
    
    cout << "Min by year: "; ptrArr.min()->show();
    cout << "Max by year: "; ptrArr.max()->show();

    cout << "\n--- Тест с Writer* ---" << endl;
    ArrayContainer<Writer*> writerArr(2);
    writerArr.add(&w_1);
    writerArr.add(&w_2);
    cout << "Min Writer ptr: "; writerArr.min()->show();
    cout << "Max Writer ptr: "; writerArr.max()->show();

    delete p1; delete p2; delete p3;

    cout << "\nЗавершение программы. Объектов Personality осталось: " << Personality::getObjectCount() << endl;

    return 0;
}
