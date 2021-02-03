#include "testindexedcollection.h"

void TestIndexedCollection::fillCollection(int amountOfElements){
    for(int i = 0; i != amountOfElements; ++i){
        collection_->add(i*i);
    }
}

void TestIndexedCollection::benchmarkAdd(){
    for(int i = 0; i < numberOfElements_; ++i){
        collection_->add(i);
    }
}

void TestIndexedCollection::benchmarkFind(){
    for(int i = 0; i < numberOfElements_; ++i){
        collection_->find(i);
    }
}


TestIndexedCollection::TestIndexedCollection(IndexedCollection *collection, QObject* parent):QObject(parent){
    collection_ = collection;
};

TestIndexedCollection::~TestIndexedCollection(){
    delete collection_;
}

void TestIndexedCollection::init()
{

};

void TestIndexedCollection::cleanup()
{

};

/// review: если делать тесты чистыми, то эти два метода можно объединить
/// testEmptyCollection и testFilledCollection. Просто будем создавать пустую коллекцию.
/// выглядит странным такой тест пустой коллекции, потому что тут проверяется только
/// одно условие, что коллекция пуста. Передаваемый индекс при этом значения не имеет.
void TestIndexedCollection::testEmptyCollection_data(){
    QTest::addColumn<int>("index");
    QTest::addColumn<std::optional<int>>("expected");

    /// review: все тест-кейсы имеют одинаковые имена. Если один упадёт, как мы его найдём тут?
    QTest::newRow(typeid(*collection_).name()) << 0 <<(std::optional<int>) std::nullopt;
    QTest::newRow(typeid(*collection_).name()) << 1 << (std::optional<int>) std::nullopt;
    QTest::newRow(typeid(*collection_).name()) << -1 << (std::optional<int>) std::nullopt;
    QTest::newRow(typeid(*collection_).name()) << 4 << (std::optional<int>) std::nullopt;
    QTest::newRow(typeid(*collection_).name()) << -3 << (std::optional<int>) std::nullopt;
    QTest::newRow(typeid(*collection_).name()) <<  1000 << (std::optional<int>) std::nullopt;
    QTest::newRow(typeid(*collection_).name()) << -9735 << (std::optional<int>) std::nullopt;


}

void TestIndexedCollection::testEmptyCollection(){
    QFETCH(int, index);
    QFETCH(std::optional<int>, expected);

    QCOMPARE(collection_->find(index), expected);
}

void TestIndexedCollection::testFilledCollection_data(){
    QTest::addColumn<int>("index");
    QTest::addColumn<std::optional<int>>("expected");


    int numberOfElements = 6;
    this->fillCollection(numberOfElements);

    QTest::newRow(typeid(*collection_).name()) << 0 << (std::optional<int>) 0;
    QTest::newRow(typeid(*collection_).name()) << 1 << (std::optional<int>) 1;
    QTest::newRow(typeid(*collection_).name()) << -1 << (std::optional<int>) qPow(numberOfElements - 1, 2);
    QTest::newRow(typeid(*collection_).name()) << numberOfElements - 1 << (std::optional<int>) qPow(numberOfElements - 1, 2);
    QTest::newRow(typeid(*collection_).name()) << numberOfElements - 2 << (std::optional<int>) qPow(numberOfElements - 2, 2);
    QTest::newRow(typeid(*collection_).name()) << numberOfElements <<  (std::optional<int>) std::nullopt;;
    QTest::newRow(typeid(*collection_).name()) << -numberOfElements << (std::optional<int>) 0;
    QTest::newRow(typeid(*collection_).name()) << 1 - numberOfElements << (std::optional<int>) 1;
    QTest::newRow(typeid(*collection_).name()) << -1 - numberOfElements << (std::optional<int>) std::nullopt;;
    QTest::newRow(typeid(*collection_).name()) <<  1000 << (std::optional<int>) std::nullopt;;
    QTest::newRow(typeid(*collection_).name()) << -9735 << (std::optional<int>) std::nullopt;;

}

void TestIndexedCollection::testFilledCollection(){

    QFETCH(int, index);
    QFETCH(std::optional<int>, expected);

    QCOMPARE(collection_->find(index), expected);
}

void TestIndexedCollection::testPerfomanceCPU(){

    QBENCHMARK{
        this->benchmarkAdd();
        this->benchmarkFind();
    }
}
