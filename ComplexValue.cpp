#include "ComplexValue.h"

ComplexValue::ComplexValue(int const key):key_(key){}

bool ComplexValue::operator==(const ComplexValue &other) const{
    return this->key() == other.key();
}

bool ComplexValue::operator<(const ComplexValue &other) const{
    return this->key() < other.key();
}

int ComplexValue::key() const{
    return key_;
}
