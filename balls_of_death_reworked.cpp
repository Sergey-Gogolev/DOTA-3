#include<iostream>
#include<random>

namespace Melon
{
    double x_max, x_min, y_max, y_min;

    int random_number(int a, int b)
    {
        std::random_device r;
        std::default_random_engine e(r());
        std::uniform_int_distribution<int> dist(a, b);
        return dist(e);
    };
};


class Ball
{
public:
    Vector<double> position;
    int radius;
    Vector<double> velosity;
    int power; // шарики могут наносить разный урон
    sf::CircleShape circle;

public:
    Ball(): position(Vector<double>(2)), velosity(Vector<double>(2))
    {
        circle.setRadius(10);
        circle.setOutlineThickness(2);
        circle.setFillColor(sf::Color(220,0,0));
        circle.setOutlineColor(sf::Color(0,80,250));
        circle.setPointCount(18);

        this->radius = Melon::random_number(1, 4);
        double Vx = Melon::random_number(Melon::x_min + radius, Melon::x_max - radius);
        double Vy = Melon::random_number(Melon::y_min + radius, Melon::y_max - radius);

        this->velosity[0] = Vx / 1000000;
        this->velosity[1] = Vy / 1000000;

        this->power = Melon::random_number(1, 5);
    };

    //где окажетстя шарик через время dt
    void move(double dt)
    {
        Vector<double> new_position = (this->position) + dt * (this->velosity);

        //шарик не должен попасть за границы поля, поэтому от стенок он должен отскакивать
        //модуль скорости шарика при этом сохраняется
        if (new_position[0] + radius > Melon::x_max)
        {
            new_position[0] = 2 * Melon::x_max - new_position[0];
        }
        else if (new_position[0] - radius < Melon::x_min)
        {
            new_position[0] = 2 * Melon::x_min - new_position[0];
        }
        else if (new_position[1] + radius > Melon::y_max)
        {
            new_position[1] = 2 * Melon::y_max - new_position[0];
        }
        else if (new_position[1] - radius < Melon::y_min)
        {
            new_position[1] = 2 * Melon::y_min - new_position[0];
        }

        position = new_position;
    }

    void Draw(int w, int h, double scale, sf::RenderWindow* app) //Рисуем кружочек в нужном месте. w и h - шрина и высота окна
    {
        circle.setPosition(w/2+ position.getElement(0,0)/scale-circle.getRadius(),h/2+position.getElement(1,0)/scale-circle.getRadius());
        app->draw(circle);
    }

    // можно добавить
    // шарик может иметь ограниченное время жизни
    // шарик может менять свои размеры

};

