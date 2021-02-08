#ifndef TESTCOMPLEXCOLLECTION_H
#define TESTCOMPLEXCOLLECTION_H

#include "ComplexValueCollection.h"
#include <QObject>
#include <QTest>

class TestComplexCollection: public QObject
{
    Q_OBJECT

    int const numberOfElements_ = 10000;

    void fillRandComplexCollection(ComplexValueCollection * collection, int numberOfElements);
    void fillLinearComplexCollection(ComplexValueCollection * collection, int numberOfElements);

public:
    TestComplexCollection(QObject* parent = 0);
    virtual ~TestComplexCollection() = default;

private slots:
    void testComplexVector_data();
    void testComplexVector();

    void testComplexHash_data();
    void testComplexHash();

    void benchmarkComplexVectorAdd();
    void benchmarkComplexVectorFind();
    void benchmarkComplexVectorFindCustom();

    void benchmarkComplexHashAdd();
    void benchmarkComplexHashFind();
    void benchmarkComplexHashFindCustom();

    void benchmarkComplexVectorCreationFromFile();
    void benchmarkComplexHashCreationFromFile();

    void benchmarkComplexVectorFileFind();
    void benchmarkComplexHashFileFind();
};

#endif // TESTCOMPLEXCOLLECTION_H
