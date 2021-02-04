#ifndef INDEXEDCOLLECTION_H
#define INDEXEDCOLLECTION_H
#include "ComplexValue.h"
#include <optional>

#include <QVector>
#include <QHash>


class IndexedCollection
{
public:
    virtual ~IndexedCollection() = default;
    virtual void add(const int element) = 0;
    virtual std::optional<int> find(const int index) const = 0;

};


class Vector : public IndexedCollection
{
public:
    void add(const int element) override;
    std::optional<int> find(const int index) const override;
private:
    QVector<int> elements_;
};


class List : public IndexedCollection
{
public:
    void add(const int element) override;
    std::optional<int> find(const int index) const override;

private:
    QList<int> elements_;
};


class Hash : public IndexedCollection
{
public:
    void add(const int element) override;
    std::optional<int> find(const int index) const override;

private:
    QHash<int, int> elements_;
};

class ComplexHash
{
public:
    void add(const ComplexValue &element);
    std::optional<ComplexValue> find(const int key) const;

private:
    QHash<int, ComplexValue> elements_;
};

class ComplexVector
{
public:
    void add(const ComplexValue &element);
    std::optional<ComplexValue> find(const ComplexValue &element) const;

private:
    QVector<ComplexValue> elements_;
};


#endif // INDEXEDCOLLECTION_H
