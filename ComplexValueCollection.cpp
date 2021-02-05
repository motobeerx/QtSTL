
#include "ComplexValueCollection.h"
#include <cstdlib>

ComplexValueCollection::ComplexValueCollection(){}

void ComplexValueHash::add(const ComplexValue &element){
    elements_.insert(element.key(), element);
}

std::optional<ComplexValue> ComplexValueHash::find(const int key) const{
    /// review: тут ты говоришь - дай мне копию элемента по ключу key, а если такого нет, то новый сконструированный объект.
    /// при этом в конструкторе ComplexValue будет выделена сразу память под вектор интов.
    /// всегда полезно прикинуть сколько будет выделений памяти.
    /// если такой ключ есть: будет сделана 1 копия ComplexValue в element, потом 1 копия при создании std::optional, и потом это скопируется в вызывающий метод.
    /// если такого ключа нет, то будет вызов конструктора ComplexValue в методе QHash::value и копирование его в .
    /// многовато, если учесть что ComplexValue планируется как довольно тяжёлый объект ComplexValue. 
    /// + есть же еще освобождение памяти, и занимает оно по времене немногим меньше выделения памяти.
    /// нужно: если ключа нет в таблице - никаких выделений памяти быть не должно.
    /// если ключ есть в таблице - то тоже выделений памяти быть не должно. Это реально и довольно просто.
    /// подумай над этим и сегодня поговорим про это.
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
    /// review: нельзя ли упростить этот код и убрать из него лишнее копирование списка ключей,
    /// если использовать итераторы?
    QList<int> keys = elements_.keys();
    int steps = rand() % keys.size();
    int key = -1;
    for(int i = 0; i <= steps; ++i){
        key = keys.at(i);
    }
    return key;
}

/// review: нельзя ли улучшить добавление элементов в коллекцию с помощью семантики перемещения
/// вот тут https://xania.org/202101/cpp-by-value-args просто и понятно написано и посчитано как это работает.
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
