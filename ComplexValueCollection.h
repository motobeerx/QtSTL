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
    virtual  std::optional<ComplexValue> find(const int key) const = 0;
    virtual int size() const = 0;
    virtual int getRandomeKey() const = 0;
};


class ComplexValueHash: public ComplexValueCollection
{
public:
    void add(const ComplexValue &element);
    std::optional<ComplexValue> find(const int key) const;
    int size() const;
    int getRandomeKey() const;

private:
    QHash<int, ComplexValue> elements_;
};


class ComplexValueVector: public ComplexValueCollection
{
public:
    void add(const ComplexValue &element);
    std::optional<ComplexValue> find(const int key) const;
    int size() const;
    int getRandomeKey() const;

private:
    QVector<ComplexValue> elements_;
};

#endif // COMPLEXVALUECOLLECTION_H
