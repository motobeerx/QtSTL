#include "indexedcollection.h"


void Vector::add(const int element) {
    elements_ << element;
}

std::optional<int> Vector::find(const int index) const {
    bool emptyCollection = elements_.isEmpty();
    bool indexInPositiveRange = index < elements_.size();
    bool indexInNegativeRange = index >= -elements_.size();
    bool invalidIndex = indexInPositiveRange xor indexInNegativeRange;
    if(emptyCollection or invalidIndex){
        return std::nullopt;
    }

    int reducedIndex = index < 0 ? (index + elements_.size()) : index;

    return elements_.value(reducedIndex);

}


void List::add(const int element){
    elements_ << element;
}

std::optional<int> List::find(const int index) const {
    bool emptyCollection = elements_.isEmpty();
    bool indexInPositiveRange = index < elements_.size();
    bool indexInNegativeRange = index >= -elements_.size();
    bool invalidIndex = indexInPositiveRange xor indexInNegativeRange;

    if(emptyCollection or invalidIndex){
        return std::nullopt;
    }

    int reducedIndex = index < 0 ? (index + elements_.size()) : index;

    return elements_.value(reducedIndex);
}

void Hash::add(const int element) {
    elements_.insert(elements_.size(), element);
}

std::optional<int> Hash::find(const int index) const {
    bool emptyCollection = elements_.isEmpty();
    bool indexInPositiveRange = index < elements_.size();
    bool indexInNegativeRange = index >= -elements_.size();
    bool invalidIndex = indexInPositiveRange xor indexInNegativeRange;
    if(emptyCollection or invalidIndex){
        return std::nullopt;
    }

    int reducedIndex = index < 0 ? (index + elements_.size()) : index;

    return elements_.value(reducedIndex);
}


void ComplexHash::add(const ComplexValue &element){
    elements_.insert(element.key(), element);
}

std::optional<ComplexValue> ComplexHash::find(const int key) const{
    return elements_.contains(key) ? elements_.value(key) : std::nullopt;
}

void ComplexVector::add(const ComplexValue &element){
    elements_ << element;
}

std::optional<ComplexValue> ComplexVector::find(const ComplexValue &element) const{
    if(elements_.contains(element)){
        return element;
    }
    return std::nullopt;
}
