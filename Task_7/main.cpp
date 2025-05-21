//Опр: Паттерн Bridge (Мост) — это структурный паттерн проектирования, который разделяет один или несколько классов 
//     на две отдельные иерархии — абстракцию и реализацию, позволяя изменять их независимо друг от друга.

#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

class SetImpl {
public:
    virtual ~SetImpl() = default;
    virtual void add(int element) = 0;
    virtual void remove(int element) = 0;
    virtual bool contains(int element) const = 0;
    virtual std::vector<int> getElements() const = 0;
    virtual size_t size() const = 0;
};

class VectorSetImpl : public SetImpl {
private:
    std::vector<int> elements;

public:
    void add(int element) override {
        if (!contains(element)) {
            elements.push_back(element);
        }
    }

    void remove(int element) override {
        elements.erase(std::remove(elements.begin(), elements.end(), element), elements.end());
    }

    bool contains(int element) const override {
        return std::find(elements.begin(), elements.end(), element) != elements.end();
    }

    std::vector<int> getElements() const override {
        return elements;
    }

    size_t size() const override {
        return elements.size();
    }
};

class HashSetImpl : public SetImpl {
private:
    std::unordered_set<int> elements;

public:
    void add(int element) override {
        elements.insert(element);
    }

    void remove(int element) override {
        elements.erase(element);
    }

    bool contains(int element) const override {
        return elements.find(element) != elements.end();
    }

    std::vector<int> getElements() const override {
        return std::vector<int>(elements.begin(), elements.end());
    }

    size_t size() const override {
        return elements.size();
    }
};


class Set {
private:
    SetImpl* impl;
    const size_t SWITCH_THRESHOLD = 10; // Порог для переключения реализации

    void checkAndSwitchImpl() {
        if (impl->size() > SWITCH_THRESHOLD && dynamic_cast<VectorSetImpl*>(impl)) {
            // Переключаемся с вектора на хэш-таблицу
            auto newImpl = new HashSetImpl();
            for (int elem : impl->getElements()) {
                newImpl->add(elem);
            }
            delete impl;
            impl = newImpl;
        } else if (impl->size() <= SWITCH_THRESHOLD && dynamic_cast<HashSetImpl*>(impl)) {
            // Переключаемся с хэш-таблицы на вектор
            auto newImpl = new VectorSetImpl();
            for (int elem : impl->getElements()) {
                newImpl->add(elem);
            }
            delete impl;
            impl = newImpl;
        }
    }

public:
    Set() : impl(new VectorSetImpl()) {}

    ~Set() {
        delete impl;
    }

    void add(int element) {
        impl->add(element);
        checkAndSwitchImpl();
    }

    void remove(int element) {
        impl->remove(element);
        checkAndSwitchImpl();
    }

    bool contains(int element) const {
        return impl->contains(element);
    }

    size_t size() const {
        return impl->size();
    }

    // Объединение множеств
    Set unionWith(const Set& other) const {
        Set result;
        for (int elem : impl->getElements()) {
            result.add(elem);
        }
        for (int elem : other.impl->getElements()) {
            result.add(elem);
        }
        return result;
    }

    // Пересечение множеств
    Set intersectionWith(const Set& other) const {
        Set result;
        for (int elem : impl->getElements()) {
            if (other.contains(elem)) {
                result.add(elem);
            }
        }
        return result;
    }
    
    void print() const {
        std::cout << "{ ";
        for (int elem : impl->getElements()) {
            std::cout << elem << " ";
        }
        std::cout << "}" << std::endl;
    }
};

int main() {
    Set mySet;
    
    for (int i = 1; i <= 5; ++i) {
        mySet.add(i);
    }
    std::cout << "Добавили 1-5: ";
    mySet.print();
    
    for (int i = 6; i <= 15; ++i) {
        mySet.add(i);
    }
    std::cout << "Добавили 6-15: ";
    mySet.print();
    
    mySet.remove(10);
    mySet.remove(5);
    std::cout << "Убрали 5 и 10: ";
    mySet.print();
    
    for (int i = 1; i <= 14; ++i) {
        mySet.remove(i);
    }
    std::cout << "Удалили все элементы кроме одного ";
    mySet.print();
    
    Set setA;
    setA.add(1);
    setA.add(2);
    setA.add(3);

    Set setB;
    setB.add(2);
    setB.add(3);
    setB.add(4);

    Set unionSet = setA.unionWith(setB);
    std::cout << "Объединение: ";
    unionSet.print();

    Set intersectionSet = setA.intersectionWith(setB);
    std::cout << "Пересечение: ";
    intersectionSet.print();

    return 0;
}