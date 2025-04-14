#pragma once

#include "class_body.h"
#include "field.h"
#include<iostream>
#include<random>


namespace Melon
{
    int random_number(int a, int b)
    {
        std::random_device r;
        std::default_random_engine e(r());
        std::uniform_int_distribution<int> dist(a, b);
        return dist(e);
    };
};


class Ball : public Body {
public:
    Ball(position(Vector<double>(2)), velosity(Vector<double>(2)))
    {
        circle.setRadius(10);
        circle.setOutlineThickness(2);
        circle.setFillColor(sf::Color(220,0,0));
        circle.setOutlineColor(sf::Color(0,80,250));
        circle.setPointCount(18);

        this->radius = Melon::random_number(1, 4);
        double Vx = Melon::random_number(GetLeft(GetRectangle()) + radius_, GetRight(GetRectangle()) - radius_);
        double Vy = Melon::random_number(GetDown(GetRectangle()) + radius_, GetUp(GetRectangle()) - radius_);

        this->velosity[0] = Vx / 1000000;
        this->velosity[1] = Vy / 1000000;

        this->power = Melon::random_number(1, 5);
    };
    ~Ball() = default;

    void CalcMove (const double dt) override{
        Vector new_position += velosity_ * dt + 0.5 * acceleration_ * dt * dt;
        Vector new_velosity += acceleration_ * dt;

        //шарик не должен попасть за границы поля, поэтому от стенок он должен отскакивать
        //модуль скорости шарика при этом сохраняется
        if (new_position[0] + radius_ > GetRight(GetRectangle()))
        {
            new_position[0] = 2 * GetRight(GetRectangle()) - new_position[0];
            new_velosity[0] = -new_velosity[0];
        }
        else if (new_position[0] - radius_ < GetLeft(GetRectangle()))
        {
            new_position[0] = 2 * GetLeft(GetRectangle()) - new_position[0];
            new_velosity[0] = -new_velosity[0];
        }
        else if (new_position[1] + radius_ > GetUp(GetRectangle()))
        {
            new_position[1] = 2 * GetUp(GetRectangle()) - new_position[1];
            new_velosity[1] = -new_velosity[1];
        }
        else if (new_position[1] - radius_ < GetDown(GetRectangle()))
        {
            new_position[1] = 2 * GetDown(GetRectangle()) - new_position[1];
            new_velosity[1] = -new_velosity[1];
        }

        position_ = new_position;
        velosity_ = new_velosity;
    }

private:
    double radius_;
    Vector position_;
    Vector velocity_;
    Vector acceleration_;

};