#include "TestComplexCollection.h"
#include <cstdlib>


void TestComplexCollection::fillRandComplexCollection(ComplexValueCollection * collection, int numberOfElements){
    /// review: ты хочешь в коллекции 1000000 элементов, но у тебя они будут или с повторяющимися ключами, или их будет <= 1000.
    /// то есть разное поведения для вектора и таблицы
    for(int i = 0; i != numberOfElements; ++i){
        collection->add(ComplexValue(rand() % 1000 + 1));
    }

}

void TestComplexCollection::fillLinearComplexCollection(ComplexValueCollection *collection, int numberOfElements)
{
    for(int i = 0; i != numberOfElements; ++i){
        collection->add(ComplexValue(i));
    }
}

TestComplexCollection::TestComplexCollection(QObject* parent): QObject(parent){}


void TestComplexCollection::testComplexVector_data()
{
    QTest::addColumn<ComplexValueVector>("collection");
    QTest::addColumn<int>("key");
    QTest::addColumn<std::optional<int>>("expected");

    int numberOfElements = 6;
    ComplexValueVector vector;
    
    /// review: если ты тестируешь пустой контейнер, то лучше его передать пустой прямо в тест-кейс:
    /// QTest::newRow("1. Test empty vector") << ComplexValueVector()  <<  0 << (std::optional<int>) std::nullopt;
    
    /// review: подумай, как можно избавиться от преобразования (std::optional<int>) std::nullopt
    QTest::newRow("1. Test empty vector") << vector  <<  0 << (std::optional<int>) std::nullopt;
    this->fillLinearComplexCollection(&vector, numberOfElements);
    QTest::newRow("2. Find 0 element in vector") << vector << 0 << (std::optional<int>) 0;
    QTest::newRow("3. Find 1st element in vector") << vector << 1 << (std::optional<int>) 1;
    QTest::newRow("4. Find last element in vector") << vector  << numberOfElements - 1 << (std::optional<int>) (numberOfElements - 1);
    QTest::newRow("5. Find prelast element in vector") << vector  << numberOfElements - 2 << (std::optional<int>) (numberOfElements - 2);
    QTest::newRow("6. Find afterlast element in vector") << vector  << numberOfElements <<  (std::optional<int>) std::nullopt;
    
    /// review: код, который так сжат, довольно трудно читать. Не нужно жалеть пустого пространства.
    /// Если выровнять его так, как ниже, то будет гораздо приятнее
   
    QTest::newRow("7. Find element with invalid index in vector") 
        << vector  
        <<  1000 
        << (std::optional<int>) std::nullopt;
}


void TestComplexCollection::testComplexVector()
{
    QFETCH(ComplexValueVector, collection);
    QFETCH(int, key);
    QFETCH(std::optional<int>, expected);

    QCOMPARE(collection.find(key), expected);
}


void TestComplexCollection::testComplexHash_data()
{
    QTest::addColumn<ComplexValueHash>("collection");
    QTest::addColumn<int>("key");
    QTest::addColumn<std::optional<int>>("expected");

    int numberOfElements = 6;
    ComplexValueHash hash;
    QTest::newRow("1. Test empty hash") << hash  <<  0 << (std::optional<int>) std::nullopt;
    this->fillLinearComplexCollection(&hash, numberOfElements);
    QTest::newRow("2. Find 0 element in hash") << hash << 0 << (std::optional<int>) 0;
    QTest::newRow("3. Find 1st element in hash") << hash << 1 << (std::optional<int>) 1;
    QTest::newRow("4. Find last element in hash") << hash  << numberOfElements - 1 << (std::optional<int>) (numberOfElements - 1);
    QTest::newRow("5. Find prelast element in hash") << hash  << numberOfElements - 2 << (std::optional<int>) (numberOfElements - 2);
    QTest::newRow("6. Find afterlast element in hash") << hash  << numberOfElements <<  (std::optional<int>) std::nullopt;
    QTest::newRow("7. Find element with invalid index in hash") << hash  <<  1000 << (std::optional<int>) std::nullopt;
}


void TestComplexCollection::testComplexHash()
{
    QFETCH(ComplexValueHash, collection);
    QFETCH(int, key);
    QFETCH(std::optional<int>, expected);

    QCOMPARE(collection.find(key), expected);

}


void TestComplexCollection::benchmarkComplexVectorAdd()
{
    ComplexValueVector vector;
    QBENCHMARK{
       this->fillRandComplexCollection(&vector, numberOfElements_);
    }

}


void TestComplexCollection::benchmarkComplexVectorFind()
{
    /// review: такой бенчмарк абсолютно зависит от  того, что выдал нам getRandomeKey().
    /// то есть на его показания сложно операться, от запуска к запуску он будет давать очень разные показания.
    /// подумай, как этого можно избежать
    ComplexValueVector vector;
    this->fillRandComplexCollection(&vector, numberOfElements_);
    int target = vector.getRandomeKey();
    QBENCHMARK{
        for(int i = 0; i != numberOfElements_; ++i){
            vector.find(target);
        }
    }
}


void TestComplexCollection::benchmarkComplexHashAdd()
{
    ComplexValueHash hash;
    QBENCHMARK{
        this->fillRandComplexCollection(&hash, numberOfElements_);
    }
}




void TestComplexCollection::benchmarkComplexHashFind()
{
    ComplexValueHash hash;
    this->fillRandComplexCollection(&hash, numberOfElements_);
    int target = hash.getRandomeKey();
    QBENCHMARK{
        for(int i = 0; i != numberOfElements_; ++i){
            hash.find(target);
        }
    }
}

