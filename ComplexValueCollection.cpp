
#include "ComplexValueCollection.h"
#include <cstdlib>
#include <QFile>
#include <QTextStream>



ComplexValueCollection::ComplexValueCollection(){}

void ComplexValueHash::add(const ComplexValue &element){
    elements_.insert(element.key(), element);
}

void ComplexValueHash::extend(const int key, const int value)
{
    if(elements_.contains(key)){
        elements_.value(key).add(value);
    }else{
        ComplexValue element(key);
        element.add(value);
        this->add(element);
    }
}

// eleminate copying here
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
    srand (time(NULL));
    int steps = rand() % elements_.size();
    int key = -1;
    auto it = elements_.begin();
    for(int i = 0; i <= steps; ++i){
        key = it.value().key();
        ++it;
    }
    return key;
}

void ComplexValueHash::print() const
{
    auto it = elements_.begin();
    while(it != elements_.end()){
        it.value().print();
        ++it;
    }

}

void ComplexValueVector::add(const ComplexValue &element){
    elements_ << element;
}

void ComplexValueVector::extend(const int key, const int value)
{
    for(int i = 0; i < elements_.size(); ++i){
        if(elements_.at(i).key() == key){
            elements_[i].add(value);
            return;
        }
    }
    ComplexValue element(key);
    element.add(value);
    this->add(element);

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
    srand (time(NULL));
    int index = rand() % this->size();
    return elements_.at(index).key();
}

void ComplexValueVector::print() const
{
    for(int i = 0; i < elements_.size(); ++i){
        elements_.at(i).print();
    }
}



void generateData(int numberOfPairs,  QString fileName, QString delimiter)
{
    srand (time(NULL));
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)){
        QTextStream out(&file);
        for(int i = 0; i != numberOfPairs; ++i){
            out << rand() % 1000001 << delimiter << rand() % 1000001<<"\r\n";
        }
        file.close();
    }
    return;
}

void readData(ComplexValueCollection *collection, QString fileName, QString delimiter)
{
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly)){
        while (!file.atEnd()) {
                QString line = file.readLine();
                QStringList data = line.split(delimiter);
                int key = data.at(0).toInt();
                int value = data.at(1).toInt();
                collection->extend(key, value);
        }
    }
}





























