#include "ComplexValue.h"


ComplexValue::ComplexValue(){
    data_ = QVector <int> ();
}

ComplexValue::ComplexValue(int const key):key_(key){
    data_ = QVector <int> ();
}

void ComplexValue::add(const int value)
{
    data_<<value;
}

void ComplexValue::print() const
{
    std::cout<<this->key_<<": ";
    for(int i = 0; i < data_.size(); ++i){
        std::cout<<data_.at(i)<< ", ";
    }
    std::cout<<std::endl;
}

bool ComplexValue::operator==(const ComplexValue &other) const{
    return this->key() == other.key();
}

bool ComplexValue::operator<(const ComplexValue &other) const{
    return this->key() < other.key();
}

int ComplexValue::key() const{
    return key_;
}

// return const &
QVector<int> ComplexValue::value() const
{
    return data_;
}
