#ifndef COMPLEXVALUE_H
#define COMPLEXVALUE_H

#include <QVector>

struct ComplexValue
{
    /// review: значения по умолчанию нужно максимально избегать
    /// тут я не вижу причин для их использования. И почему -1 ? 
    
    /// review: если конструктор имеет 1 аргумент, то нужно прописать ему explicit. 
    /// это позволит избежать неявного преобразования int -> ComplexValue, которое является некорректным.
    ComplexValue(int const key = -1);
    bool operator==(ComplexValue const &other) const;
    bool operator<(ComplexValue const &other) const;
    int key() const;
private:
    int key_;
    QVector<int> data_;
};

#endif // COMPLEXVALUE_H
