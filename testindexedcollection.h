#ifndef TESTINDEXEDCOLLECTION_H
#define TESTINDEXEDCOLLECTION_H

#include <optional>
#include <QElapsedTimer>
#include <QObject>
#include <QtMath>
#include <QTest>

#include "indexedcollection.h"

class TestIndexedCollection: public QObject{

    Q_OBJECT


    int const numberOfElements_ = 1000000;

    void fillCollection(IndexedCollection *collection, int amountOfElements);
    void benchmarkAdd(IndexedCollection *collection);
    void benchmarkFind(IndexedCollection *collection);

public:
    TestIndexedCollection(QObject* parent = 0);
    virtual ~TestIndexedCollection();

private slots:
    void testVector_data();
    void testVector();

    void testList_data();
    void testList();

    void testHash_data();
    void testHash();

    //void testPerfomanceCPU();
};

#endif // TESTINDEXEDCOLLECTION_H
