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
/// 1. ++Переписать на QTest тесты
/// 2. ++Понять https://en.cppreference.com/w/cpp/utility/optional +
/// 4. Узнать синтаксис и семантику for +
/// 5. ++Узнать про деструкторы, операторы new и delete. Как их использовать, чтобы не было утечек памяти.
/// 6. опционально - узнать про тьюринг полноту
/// 7. ++Реализовать классы List и Hash +
/// 8. ++Поменять семантику find - на отрицательных индексах ищет элемент с конца. Сначала поменять тесты, потом код. +
/// 9. ++Написать бенчмарк для операции find +

#include <iostream>
#include <optional>
#include <QtMath>

#include <QTest>
#include <QElapsedTimer>
#include <QVector>
#include <QHash>

class IndexedCollection
{
public:
    virtual ~IndexedCollection() = default;
    virtual void add(const int element) = 0;
    virtual std::optional<int> find(const int index) const = 0;

};


class Vector : public IndexedCollection
{
public:
    void add(const int element) override
    {
        elements_ << element;
    }

    std::optional<int> find(const int index) const override
    {
        if(elements_.isEmpty() or ((index < elements_.size()) xor (index >= -elements_.size()))){
            return std::nullopt;
        }

        int reducedIndex = index < 0 ? (index + elements_.size()) : index;

        return elements_.value(reducedIndex);

    }

private:
    QVector<int> elements_;
};


class List : public IndexedCollection
{
    void add(const int element) override
    {
        elements_ << element;
    }

    std::optional<int> find(const int index) const override
    {
        if(elements_.isEmpty() or ((index < elements_.size()) xor (index >= -elements_.size()))){
            return std::nullopt;
        }

        int reducedIndex = index < 0 ? (index + elements_.size()) : index;

        return elements_.value(reducedIndex);

    }

private:
    QList<int> elements_;
};


class Hash : public IndexedCollection
{
    void add(const int element) override
    {
        elements_.insert(elements_.size(), element);
    }

    std::optional<int> find(const int index) const override
    {
        if(elements_.isEmpty() or ((index < elements_.size()) xor (index >= -elements_.size()))){
            return std::nullopt;
        }

        int reducedIndex = index < 0 ? (index + elements_.size()) : index;

        return elements_.value(reducedIndex);

    }

private:
    QHash<int, int> elements_;
};


class TestIndexedCollection: public QObject{


    int const numberOfElements_ = 1000000;
    IndexedCollection* collection_;

    void fillCollection(int amountOfElements){
        for(int i = 0; i != amountOfElements; ++i){
            collection_->add(i*i);
        }
    }

    qint64 benchmarkAdd(){
        qint64 period;
        QElapsedTimer time;
        time.restart();
        for(int i = 0; i < numberOfElements_; ++i)
        {
            collection_->add(i);
        }
        period = time.elapsed();
        return period;
    }

    qint64 benchmarkFind(){
        qint64 period;
        QElapsedTimer time;
        time.restart();
        for(int i = 0; i < numberOfElements_; ++i)
        {
            collection_->find(i);
        }

        period = time.elapsed();
        return period;
    }

public:
    TestIndexedCollection(IndexedCollection *collection): collection_(collection){};


private slots:
    void testEmptyCollection_data(){
        QTest::addColumn<int>("Index");
        QTest::addColumn<std::optional<int>>("Expected Result");

        QTest::newRow(typeid(*collection_).name()) << 0 << std::nullopt;
        QTest::newRow(typeid(*collection_).name()) << 1 << std::nullopt;
        QTest::newRow(typeid(*collection_).name()) << -1 << std::nullopt;
        QTest::newRow(typeid(*collection_).name()) << 4 << std::nullopt;
        QTest::newRow(typeid(*collection_).name()) << -3 << std::nullopt;
        QTest::newRow(typeid(*collection_).name()) <<  1000 << std::nullopt;
        QTest::newRow(typeid(*collection_).name()) << -9735 << std::nullopt;


    }

    void testEmptyCollection(){
        QFETCH(int, index);
        QFETCH(std::optional<int>, expected);

        QCOMPARE(collection_->find(index), expected);
    }

    void testFilledCollection_data(){
        QTest::addColumn<int>("Index");
        QTest::addColumn<std::optional<int>>("Expected Result");


        int numberOfElements = 6;
        this->fillCollection(numberOfElements);

        QTest::newRow(typeid(*collection_).name()) << 0 << 0;
        QTest::newRow(typeid(*collection_).name()) << 1 << 1;
        QTest::newRow(typeid(*collection_).name()) << -1 << qPow(numberOfElements - 1, 2);
        QTest::newRow(typeid(*collection_).name()) << numberOfElements - 1 << qPow(numberOfElements - 1, 2);
        QTest::newRow(typeid(*collection_).name()) << numberOfElements - 2 << qPow(numberOfElements, 2);
        QTest::newRow(typeid(*collection_).name()) << numberOfElements <<  std::nullopt;
        QTest::newRow(typeid(*collection_).name()) << -numberOfElements << 0;
        QTest::newRow(typeid(*collection_).name()) << 1 - numberOfElements << 1;
        QTest::newRow(typeid(*collection_).name()) << -1 - numberOfElements << std::nullopt;
        QTest::newRow(typeid(*collection_).name()) <<  1000 << std::nullopt;
        QTest::newRow(typeid(*collection_).name()) << -9735 << std::nullopt;

    }

    void testFilledCollection(){

        QFETCH(int, index);
        QFETCH(std::optional<int>, expected);

        QCOMPARE(collection_->find(index), expected);
    }

};



int main()
{
     QTest::qExec(new TestIndexedCollection(new Vector));
     QTest::qExec(new TestIndexedCollection(new List));
     QTest::qExec(new TestIndexedCollection(new Hash));

    return 0;
}
