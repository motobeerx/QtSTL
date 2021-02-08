#include <QCoreApplication>
/// Разбираемся в эффективности операций добавления и поиска.
/// Пишем абстрактный класс IndexedCollection с двумя методами
/// add - добавляет элемент в коллекцию
/// find - возвращает элемент для указанного индекса
/// Хотим понимать, сколько времени(а потом ещё и памяти) занимает каждая эта операция для N элементов.
/// Хотим использовать TDD и разработку "через компиляцию".
/// Хотим переиспользование кода.

/// Конкретные задачи
/// 1. ++Переписать на QTest тесты
/// 2. ++Понять https://en.cppreference.com/w/cpp/utility/optional +
/// 4. Узнать синтаксис и семантику for +
/// 5. ++Узнать про деструкторы, операторы new и delete. Как их использовать, чтобы не было утечек памяти.
/// 6. опционально - узнать про тьюринг полноту
/// 7. ++Реализовать классы List и Hash +
/// 8. ++Поменять семантику find - на отрицательных индексах ищет элемент с конца. Сначала поменять тесты, потом код. +
/// 9. ++Написать бенчмарк для операции find +
#include "testindexedcollection.h"
#include "TestComplexCollection.h"
#include "ComplexValueCollection.h"

QTEST_MAIN(TestComplexCollection)
//int main()
//{
//    generateData(1000000);
//    ComplexValueCollection* hash = new ComplexValueHash;
//    readData(hash);
//    hash->print();
//    return 0;
//}

