#include "indexedcollection.h"


void Vector::add(const int element) {
    elements_ << element;
}

std::optional<int> Vector::find(const int index) const {
    if(elements_.isEmpty() or ((index < elements_.size()) xor (index >= -elements_.size()))){
        return std::nullopt;
    }

    int reducedIndex = index < 0 ? (index + elements_.size()) : index;

    return elements_.value(reducedIndex);

}


void List::add(const int element){
    elements_ << element;
}

std::optional<int> List::find(const int index) const {
    if(elements_.isEmpty() or ((index < elements_.size()) xor (index >= -elements_.size()))){
        return std::nullopt;
    }

    int reducedIndex = index < 0 ? (index + elements_.size()) : index;

    return elements_.value(reducedIndex);
}

void Hash::add(const int element) {
    elements_.insert(elements_.size(), element);
}

std::optional<int> Hash::find(const int index) const {
    if(elements_.isEmpty() or ((index < elements_.size()) xor (index >= -elements_.size()))){
        return std::nullopt;
    }

    int reducedIndex = index < 0 ? (index + elements_.size()) : index;

    return elements_.value(reducedIndex);
}








