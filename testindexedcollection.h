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
    IndexedCollection* collection_;

    void fillCollection(int amountOfElements);
    void benchmarkAdd();
    void benchmarkFind();

public:
    TestIndexedCollection(IndexedCollection *collection, QObject* parent = 0);
    virtual ~TestIndexedCollection();

private slots:
    void init();
    void cleanup();

    void testEmptyCollection_data();
    void testEmptyCollection();
    void testFilledCollection_data();
    void testFilledCollection();
    void testPerfomanceCPU();
};

#endif // TESTINDEXEDCOLLECTION_H
