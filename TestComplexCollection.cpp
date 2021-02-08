#include "TestComplexCollection.h"
#include <cstdlib>


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

    QTest::newRow("1. Test empty vector") << ComplexValueVector()  <<  0 << (std::optional<int>) std::nullopt;
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

    QCOMPARE(collection.find(key), expected);
}


void TestComplexCollection::testComplexHash_data()
{
    QTest::addColumn<ComplexValueHash>("collection");
    QTest::addColumn<int>("key");
    QTest::addColumn<std::optional<int>>("expected");

    QTest::newRow("1. Test empty hash") << ComplexValueHash()  <<  0 << (std::optional<int>) std::nullopt;
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
    ComplexValueVector vector;
    this->fillRandComplexCollection(&vector, numberOfElements_);
    int target = vector.getRandomeKey();
    std::cout<<target<<std::endl;
    QBENCHMARK{
        vector.find(target);
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
    //std::cout<<target<<std::endl;
    QBENCHMARK{
            hash.find(target);
    }
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
    std::cout<<target<<std::endl;
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
    //std::cout<<target<<std::endl;
    QBENCHMARK{
            hash.find(target);
    }
}

