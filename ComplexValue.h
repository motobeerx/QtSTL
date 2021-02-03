#ifndef COMPLEXVALUE_H
#define COMPLEXVALUE_H

struct ComplexValue
{
    ComplexValue(int const key);
    bool operator==(ComplexValue const &other) const;
    bool operator<(ComplexValue const &other) const;
    int key() const;
private:
    int key_;

};

#endif // COMPLEXVALUE_H
