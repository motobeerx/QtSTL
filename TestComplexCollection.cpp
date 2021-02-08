#include "TestComplexCollection.h"
#include <cstdlib>
#include <QElapsedTimer>


void TestComplexCollection::fillRandComplexCollection(ComplexValueCollection * collection, int numberOfElements){
    srand (time(NULL));
    for(int i = 0; i != numberOfElements; ++i){
        collection->add(ComplexValue(rand() % numberOfElements + 1));
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

    QTest::newRow("1. Test empty vector") << ComplexValueVector()  <<  0 <<(std::optional<int>) std::nullopt;
    int numberOfElements = 6;
    ComplexValueVector vector;
    this->fillLinearComplexCollection(&vector, numberOfElements);
    QTest::newRow("2. Find 0 element in vector") << vector << 0 << (std::optional<int>) 0;
    QTest::newRow("3. Find 1st element in vector") << vector << 1 << (std::optional<int>) 1;
    QTest::newRow("4. Find last element in vector") << vector  << numberOfElements - 1 << (std::optional<int>) (numberOfElements - 1);
    QTest::newRow("5. Find prelast element in vector") << vector  << numberOfElements - 2 << (std::optional<int>) (numberOfElements - 2);
    QTest::newRow("6. Find afterlast element in vector") << vector  << numberOfElements <<  (std::optional<int>) std::nullopt;
    QTest::newRow("7. Find element with invalid index in vector") << vector  <<  1000 << (std::optional<int>) std::nullopt;
}


void TestComplexCollection::testComplexVector()
{
    QFETCH(ComplexValueVector, collection);
    QFETCH(int, key);
    QFETCH(std::optional<int>, expected);

    if(collection.find(key) == nullptr){
        QVERIFY(expected == std::nullopt);
    }else{
        QCOMPARE((std::optional<int>) (collection.find(key)->key()), expected);
    }

}


void TestComplexCollection::testComplexHash_data()
{
    QTest::addColumn<ComplexValueHash>("collection");
    QTest::addColumn<int>("key");
    QTest::addColumn<std::optional<int>>("expected");

    QTest::newRow("1. Test empty hash") << ComplexValueHash()  <<  0 <<(std::optional<int>) std::nullopt;
    int numberOfElements = 6;
    ComplexValueHash hash;
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

    if(collection.find(key) == nullptr){
        QVERIFY(expected == std::nullopt);
    }else{
        QCOMPARE((std::optional<int>) (collection.find(key)->key()), expected);
    }

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
    ComplexValueVector vector;
    this->fillRandComplexCollection(&vector, numberOfElements_);
    int target = vector.getRandomeKey();
    QBENCHMARK{
        vector.find(target);
    }
}

void TestComplexCollection::benchmarkComplexVectorFindCustom()
{
    ComplexValueVector vector;
    this->fillRandComplexCollection(&vector, numberOfElements_);

    QElapsedTimer timer;
    qint64 totalTime = 0;
    int amplifier = 1000;
    for(int i = 0; i != numberOfElements_; ++i){
        int target = vector.getRandomeKey();
        timer.restart();
        for(int j = 0; j != amplifier; ++j)
            vector.find(target);
        totalTime += timer.elapsed();
    }

    std::cout<<"\nAverage time of Linear Search in Vector: "<<(double)totalTime/numberOfElements_/amplifier<<std::endl;

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
        hash.find(target);
    }
}

void TestComplexCollection::benchmarkComplexHashFindCustom()
{
    ComplexValueHash hash;
    this->fillRandComplexCollection(&hash, numberOfElements_);

    QElapsedTimer timer;
    qint64 totalTime = 0;
    int amplifier = 100000;
    for(int i = 0; i != numberOfElements_; ++i){
        int target = hash.getRandomeKey();
        timer.restart();
        for(int j = 0; j != amplifier; ++j)
            hash.find(target);
        totalTime += timer.elapsed();
    }

    std::cout<<"\nAverage time of Search in Hash: "<<(double)totalTime/numberOfElements_/amplifier<<std::endl;

}

void TestComplexCollection::benchmarkComplexVectorCreationFromFile()
{
    generateData(numberOfElements_);
    ComplexValueVector vector;
    QBENCHMARK{
        readData(&vector);
    }
}

void TestComplexCollection::benchmarkComplexHashCreationFromFile()
{
    generateData(numberOfElements_);
    ComplexValueHash hash;
    QBENCHMARK{
        readData(&hash);
    }
}

void TestComplexCollection::benchmarkComplexVectorFileFind()
{
    generateData(numberOfElements_);
    ComplexValueVector vector;
    readData(&vector);
    int target = vector.getRandomeKey();
    QBENCHMARK{
        vector.find(target);
    }
}

void TestComplexCollection::benchmarkComplexHashFileFind()
{
    generateData(numberOfElements_);
    ComplexValueHash hash;
    readData(&hash);
    int target = hash.getRandomeKey();
    QBENCHMARK{
        hash.find(target);
    }
}

