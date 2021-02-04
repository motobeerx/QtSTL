#ifndef COMPLEXVALUE_H
#define COMPLEXVALUE_H

#include <QVector>

struct ComplexValue
{
    ComplexValue(int const key = -1);
    bool operator==(ComplexValue const &other) const;
    bool operator<(ComplexValue const &other) const;
    int key() const;
private:
    int key_;
    QVector<int> data_;
};

#endif // COMPLEXVALUE_H
