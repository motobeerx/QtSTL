#include <QCoreApplication>
#include <QObject>
/// Разбираемся в эффективности операций добавления и поиска.
/// Пишем абстрактный класс IndexedCollection с двумя методами
/// add - добавляет элемент в коллекцию
/// find - возвращает элемент для указанного индекса
/// Хотим понимать, сколько времени(а потом ещё и памяти) занимает каждая эта операция для N элементов.
/// Хотим использовать TDD и разработку "через компиляцию".
/// Хотим переиспользование кода.

/// Конкретные задачи
/// 1. Переписать на QTest тесты
/// 2. ++Понять https://en.cppreference.com/w/cpp/utility/optional
/// 3. опционально - понять https://habr.com/ru/post/268013/
/// 4. Узнать синтаксис и семантику for +
/// 5. Узнать про деструкторы, операторы new и delete. Как их использовать, чтобы не было утечек памяти.
/// 6. опционально - узнать про тьюринг полноту
/// 7. ++Реализовать классы List и Hash +
/// 8. ++Поменять семантику find - на отрицательных индексах ищет элемент с конца. Сначала поменять тесты, потом код. +
/// 9. ++Написать бенчмарк для операции find +

#include <iostream>
#include <optional>
#include <QTest>
#include <QElapsedTimer>
#include <QVector>
#include <QHash>


/// Макрос для тестовых проверок.
#define ASSERT_EQUALS(caseName, actual, expected, onFailureText) \
    if(actual == expected)                                       \
    {                                                            \
        std::cout << "\033[1;32m OK    \033[0m: ";               \
        std::cout << caseName << std::endl;                      \
    }                                                            \
    else                                                         \
    {                                                            \
        std::cout << "\033[1;31m FAIL \033[0m: ";               \
        std::cout << caseName << std::endl;                      \
        std::cout << onFailureText << std::endl;                 \
        std::cout << "	actual: " << actual << std::endl;        \
        std::cout << "	expected: " << expected << std::endl;    \
        std::cout << std::endl;                                  \
    }


class IndexedCollection
{
public:
    virtual ~IndexedCollection(){}

    virtual void add(const int element) = 0;

    virtual std::optional<int> find(const int index) const = 0;

};


class Vector : public IndexedCollection
{
public:
    void add(const int element)
    {
        _elements << element;
    }

    std::optional<int> find(const int index) const
    {
        if(_elements.isEmpty()){
            return std::nullopt;
        }

        int reduced_index = index < 0 ? ((index % _elements.size()) + _elements.size()) : index;

        if(reduced_index >= _elements.size()){
            return std::nullopt;
        }
        return _elements.value(reduced_index);

    }

private:
    QVector<int> _elements;
};


class List : public IndexedCollection
{
    void add(const int element)
    {
        _elements << element;
    }

    std::optional<int> find(const int index) const
    {
        if(_elements.isEmpty()){
            return std::nullopt;
        }

        int reduced_index = index < 0 ? ((index % _elements.size()) + _elements.size()) : index;

        if(reduced_index >= _elements.size()){
            return std::nullopt;
        }
        return _elements.value(reduced_index);
    }

private:
    QList<int> _elements;
};


class Hash : public IndexedCollection
{
    void add(const int element)
    {
        _elements.insert(_elements.size(), element);
    }

    std::optional<int> find(const int index) const
    {
        if(_elements.isEmpty()){
            return std::nullopt;
        }

        int reduced_index = index < 0 ? ((index % _elements.size()) + _elements.size()) : index;

        if(reduced_index >= _elements.size()){
            return std::nullopt;
        }
        return _elements.value(reduced_index);
    }

private:
    QHash<int, int> _elements;
};


class TestIndexedCollection: public QObject{


    int const _numberOfElements = 1000000;

public:
    void smokeTest(IndexedCollection *collection){
        ASSERT_EQUALS("1)  collection->find(0) from empty collection", (collection->find(0) == std::nullopt), true, "");
        ASSERT_EQUALS("2)  collection->find(87) from empty collection", (collection->find(87) == std::nullopt), true, "");
        ASSERT_EQUALS("3)  collection->find(9999999) from empty collection", (collection->find(9999999) == std::nullopt), true, "");
        ASSERT_EQUALS("4)  collection->find(-50) from empty collection", (collection->find(-50) == std::nullopt), true, "");

        collection->add(42);
        ASSERT_EQUALS("5)  collection->find(0)  after adding 0 element", (collection->find(0) == 42), true, "");


        ASSERT_EQUALS("6)  collection->find(1) when 1 element not added", (collection->find(1) == std::nullopt), true, "");
        ASSERT_EQUALS("7)  collection->find(0) when 1 element not added", (collection->find(0) == 42), true, "");
        collection->add(99);
        ASSERT_EQUALS("8)  collection->find(1) after adding 1 element", (collection->find(1) == 99), true, "");
        ASSERT_EQUALS("9)  collection->find(0) after adding 1 element", (collection->find(0) == 42), true, "");
        ASSERT_EQUALS("10) collection->find(-1) after adding 1 element", (collection->find(-1) == 99), true, "");
    }

    qint64 benchmarkAdd(IndexedCollection *collection){
        qint64 period;
        QElapsedTimer time;
        time.restart();
        for(int i = 0; i < _numberOfElements; ++i)
        {
            collection->add(i);
        }
        period = time.elapsed();
        return period;
    }

    qint64 benchmarkFind(IndexedCollection *collection){
        qint64 period;
        QElapsedTimer time;
        time.restart();
        for(int i = 0; i < _numberOfElements; ++i)
        {
            collection->find(i);
        }

        period = time.elapsed();
        return period;
    }

    void testCollection(IndexedCollection *collection){
        std::cout << typeid(*collection).name() << std::endl;

        this->smokeTest(collection);
        std::cout << typeid(*collection).name() << ": " << _numberOfElements << " elements inserted for " << this->benchmarkAdd(collection) << " ms" << std::endl;
        std::cout << typeid(*collection).name() << ": " <<_numberOfElements << " elements found for " << this->benchmarkFind(collection) << " ms" << std::endl;

        delete collection;
        std::cout << std::endl;
    }

};



int main()
{
    TestIndexedCollection test;
    test.testCollection(new Vector());
    test.testCollection(new List());
    test.testCollection(new Hash());

    return 0;
}
