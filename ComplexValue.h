#ifndef COMPLEXVALUE_H
#define COMPLEXVALUE_H


#include <QVector>
#include <iostream>

struct ComplexValue
{
    ComplexValue();
    explicit ComplexValue(int const key);
    void add(int const value);
    void print() const;
    bool operator==(ComplexValue const &other) const;
    bool operator<(ComplexValue const &other) const;
    int key() const;
    // return const pointer
    QVector<int> value() const;
private:
    int key_;
    QVector<int> data_;
};

#endif // COMPLEXVALUE_H
