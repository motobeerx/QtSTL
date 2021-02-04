
#include "ComplexValueCollection.h"
#include <cstdlib>

ComplexValueCollection::ComplexValueCollection(){}

void ComplexValueHash::add(const ComplexValue &element){
    elements_.insert(element.key(), element);
}

std::optional<ComplexValue> ComplexValueHash::find(const int key) const{
    ComplexValue element =  elements_.value(key);
    if(element.key() == -1){
        return std::nullopt;
    }
    return element;
}

int ComplexValueHash::size() const
{
    return elements_.size();
}

int ComplexValueHash::getRandomeKey() const
{
    QList<int> keys = elements_.keys();
    int steps = rand() % keys.size();
    int key = -1;
    for(int i = 0; i <= steps; ++i){
        key = keys.at(i);
    }
    return key;
}

void ComplexValueVector::add(const ComplexValue &element){
    elements_ << element;
}

std::optional<ComplexValue> ComplexValueVector::find(const int key) const{
    for(int i = 0; i < elements_.size(); ++i){
        if(elements_.at(i).key() == key){
            return elements_.at(i);
        }
    }
    return std::nullopt;
}

int ComplexValueVector::size() const
{
    return elements_.size();
}

int ComplexValueVector::getRandomeKey() const
{
    int index = rand() % this->size();
    return elements_.at(index).key();
}
