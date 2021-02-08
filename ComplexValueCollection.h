#ifndef COMPLEXVALUECOLLECTION_H
#define COMPLEXVALUECOLLECTION_H


#include "ComplexValue.h"
#include <QVector>
#include <QHash>

class ComplexValueCollection
{
public:
    ComplexValueCollection();
    virtual void add(const ComplexValue &element) = 0;
    virtual void extend(int const key, int const value) = 0;
    virtual const ComplexValue* find(const int key) const = 0;
    virtual int size() const = 0;
    virtual int getRandomeKey() const = 0;
    virtual void print() const =0;
};


class ComplexValueHash: public ComplexValueCollection
{
public:
    void add(const ComplexValue &element);
    void extend(int const key, int const value);
    const ComplexValue* find(const int key) const;
    int size() const;
    int getRandomeKey() const;
    void print() const;

private:
    QHash<int, ComplexValue> elements_;
};


class ComplexValueVector: public ComplexValueCollection
{
public:
    void add(const ComplexValue &element);
    void extend(int const key, int const value);
    const ComplexValue* find(const int key) const;
    int size() const;
    int getRandomeKey() const;
    void print() const;

private:
    QVector<ComplexValue> elements_;
};


void generateData( int numberOfPairs, QString fileName = "randome_data.txt", QString delimiter = ";");
void verifyData(QString fileName = "randome_data.txt");
void readData(ComplexValueCollection *collection, QString fileName = "randome_data.txt", QString delimiter = ";");


#endif // COMPLEXVALUECOLLECTION_H
