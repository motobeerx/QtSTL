#include "testindexedcollection.h"

void TestIndexedCollection::fillCollection(IndexedCollection *collection, int amountOfElements){
    for(int i = 0; i != amountOfElements; ++i){
        collection->add(i*i);
    }
}

void TestIndexedCollection::benchmarkAdd(IndexedCollection *collection){
    for(int i = 0; i < numberOfElements_; ++i){
        collection->add(i);
    }
}

void TestIndexedCollection::benchmarkFind(IndexedCollection *collection){
    for(int i = 0; i < numberOfElements_; ++i){
        collection->find(i);
    }
}


TestIndexedCollection::TestIndexedCollection(QObject* parent):QObject(parent){}


TestIndexedCollection::~TestIndexedCollection() = default;


void TestIndexedCollection::testVector_data(){
    QTest::addColumn<Vector>("collection");
    QTest::addColumn<int>("index");
    QTest::addColumn<std::optional<int>>("expected");

    int numberOfElements = 6;
    Vector vector;
    QTest::newRow("1. Test empty vector") << vector  <<  0 << (std::optional<int>) std::nullopt;
    this->fillCollection(&vector, numberOfElements);
    QTest::newRow("2. Find 0 element in vector") << vector << 0 << (std::optional<int>) 0;
    QTest::newRow("3. Find 1st element in vector") << vector << 1 << (std::optional<int>) 1;
    QTest::newRow("4. Find last(via negative index) element in vector") << vector  << -1 << (std::optional<int>) qPow(numberOfElements - 1, 2);
    QTest::newRow("5. Find last element in vector") << vector  << numberOfElements - 1 << (std::optional<int>) qPow(numberOfElements - 1, 2);
    QTest::newRow("6. Find prelast element in vector") << vector  << numberOfElements - 2 << (std::optional<int>) qPow(numberOfElements - 2, 2);
    QTest::newRow("7. Find afterlast element in vector") << vector  << numberOfElements <<  (std::optional<int>) std::nullopt;
    QTest::newRow("8. Find 1st(via negative index) element in vector") << vector  << -numberOfElements << (std::optional<int>) 0;
    QTest::newRow("9. Find 2nd(via negative index) element in vector") << vector  << 1 - numberOfElements << (std::optional<int>) 1;
    QTest::newRow("10. Find element with invalid negative index(near -size index) in vector") << vector  << -1 - numberOfElements << (std::optional<int>) std::nullopt;
    QTest::newRow("11. Find element with invalid index in vector") << vector  <<  1000 << (std::optional<int>) std::nullopt;
    QTest::newRow("12. Find element with invalid negative index in vector") << vector  << -9735 << (std::optional<int>) std::nullopt;
}

void TestIndexedCollection::testVector(){
    QFETCH(Vector, collection);
    QFETCH(int, index);
    QFETCH(std::optional<int>, expected);

    QCOMPARE(collection.find(index), expected);
}

void TestIndexedCollection::testList_data(){
    QTest::addColumn<List>("collection");
    QTest::addColumn<int>("index");
    QTest::addColumn<std::optional<int>>("expected");

    int numberOfElements = 6;

    List list;
    QTest::newRow("1. Test empty list") << list  <<  0 << (std::optional<int>) std::nullopt;
    this->fillCollection(&list, numberOfElements);
    QTest::newRow("2. Find 0 element in list") << list << 0 << (std::optional<int>) 0;
    QTest::newRow("3. Find 1st element in list") << list << 1 << (std::optional<int>) 1;
    QTest::newRow("4. Find last(via negative index) element in list") << list  << -1 << (std::optional<int>) qPow(numberOfElements - 1, 2);
    QTest::newRow("5. Find last element in list") << list  << numberOfElements - 1 << (std::optional<int>) qPow(numberOfElements - 1, 2);
    QTest::newRow("6. Find prelast element in list") << list  << numberOfElements - 2 << (std::optional<int>) qPow(numberOfElements - 2, 2);
    QTest::newRow("7. Find afterlast element in list") << list  << numberOfElements <<  (std::optional<int>) std::nullopt;
    QTest::newRow("8. Find 1st(via negative index) element in list") << list  << -numberOfElements << (std::optional<int>) 0;
    QTest::newRow("9. Find 2nd(via negative index) element in list") << list  << 1 - numberOfElements << (std::optional<int>) 1;
    QTest::newRow("10. Find element with invalid negative index(near -size index) in list") << list  << -1 - numberOfElements << (std::optional<int>) std::nullopt;
    QTest::newRow("11. Find element with invalid index in list") << list  <<  1000 << (std::optional<int>) std::nullopt;
    QTest::newRow("12. Find element with invalid negative index in list") << list  << -9735 << (std::optional<int>) std::nullopt;
}

void TestIndexedCollection::testList(){
    QFETCH(List, collection);
    QFETCH(int, index);
    QFETCH(std::optional<int>, expected);

    QCOMPARE(collection.find(index), expected);
}

void TestIndexedCollection::testHash_data(){
    QTest::addColumn<Hash>("collection");
    QTest::addColumn<int>("index");
    QTest::addColumn<std::optional<int>>("expected");

    int numberOfElements = 6;

    Hash hash;
    QTest::newRow("1. Test empty list") << hash  <<  0 << (std::optional<int>) std::nullopt;
    this->fillCollection(&hash, numberOfElements);
    QTest::newRow("2. Find 0 element in list") << hash << 0 << (std::optional<int>) 0;
    QTest::newRow("3. Find 1st element in list") << hash << 1 << (std::optional<int>) 1;
    QTest::newRow("4. Find last(via negative index) element in list") << hash  << -1 << (std::optional<int>) qPow(numberOfElements - 1, 2);
    QTest::newRow("5. Find last element in list") << hash  << numberOfElements - 1 << (std::optional<int>) qPow(numberOfElements - 1, 2);
    QTest::newRow("6. Find prelast element in list") << hash  << numberOfElements - 2 << (std::optional<int>) qPow(numberOfElements - 2, 2);
    QTest::newRow("7. Find afterlast element in list") << hash  << numberOfElements <<  (std::optional<int>) std::nullopt;
    QTest::newRow("8. Find 1st(via negative index) element in list") << hash  << -numberOfElements << (std::optional<int>) 0;
    QTest::newRow("9. Find 2nd(via negative index) element in list") << hash  << 1 - numberOfElements << (std::optional<int>) 1;
    QTest::newRow("10. Find element with invalid negative index(near -size index) in list") << hash  << -1 - numberOfElements << (std::optional<int>) std::nullopt;
    QTest::newRow("11. Find element with invalid index in list") << hash  <<  1000 << (std::optional<int>) std::nullopt;
    QTest::newRow("12. Find element with invalid negative index in list") << hash  << -9735 << (std::optional<int>) std::nullopt;

}

void TestIndexedCollection::testHash(){
    QFETCH(Hash, collection);
    QFETCH(int, index);
    QFETCH(std::optional<int>, expected);

    QCOMPARE(collection.find(index), expected);
}



//void TestIndexedCollection::testPerfomanceCPU(){
//    Vector vector;
//    QBENCHMARK{
//        this->benchmarkAdd(&vector);
//        //this->benchmarkFind(&vector);
//    }
//}
