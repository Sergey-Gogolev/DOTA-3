#pragma once

#include "rectangle.h"
#include "class_body.h"

#include <vector>

class Field {
public:
    //типа конструктор
    static Field& Instance();

    //задаём размеры игрового поля
    void SetRectangle(Rectangle rectangle){
        rectangle_ = rectangle;
    }
    // добавление одного объекта
    void AddObject(const std::shared_ptr<Body>& object);

    //получение игрового поля
    Rectangle GetRectangle();

    //получение объектов на поле 
    std::vector<std::shared_ptr<Body>> GetObjects();

    //рисование поля. Рисовать я пока не умею...
    void Render(); 

private:
    Field() = default;
    ~Field() = default;

    //игровое поле единственно
    //так что удалим конструктор и деструктор копирования
    Field(const Field&) = delete;
    Field& operator=(const Field&) = delete;

    //и конструктор и деструктор перемещения
    Field(Field&&) = delete;
    Field& operator=(Field&&) = delete;

    Rectangle rectangle_; 
    std::vector<std::shared_ptr<Body>> objects_; //вектор из умных указателей на объекты
};