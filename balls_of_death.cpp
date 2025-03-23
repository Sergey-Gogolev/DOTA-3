#include<iostream>
#include<random>

using std::cout;
using std::endl;


namespace Melon
{
    double x_max, x_min, y_max, y_min, z_max, z_min;

    int random_number(int a, int b)
    {
        std::random_device r;
        std::default_random_engine e(r());
        std::uniform_int_distribution<int> dist(a, b);
        return dist(e);
    }
}


class Ball: 
{
protected:
    Vector position;
    int radius;
    Vector velosity;
    int dt = 1;

    int power; // шарики могут наносить разный урон

public:
    Ball()
    {
        this->radius = Melon::random_number(1, 4);
        double Vx = Melon::random_number(Melon::x_min + radius, Melon::x_max - radius);
        double Vy = Melon::random_number(Melon::y_min + radius, Melon::y_max - radius);
        double Vz = Melon::random_number(Melon::z_min + radius, Melon::z_max - radius);

        this->velosity = Vector(3, (double[]){ Vx, Vy, Vz });
        this->position = Vector();

        this->power = Melon::random_number(1, 5)
    }

    //где окажетстя шарик через время dt
    Vector move() 
    {
        Vector new_position = (this->position) + dt * (this->velosity);

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
        else if (new_position[2] + radius > Melon::z_max)
        {
            new_position[2] = 2 * Melon::z_max - new_position[0];
        }
        else if (new_position[2] - radius < Melon::z_min)
        {
            new_position[2] = 2 * Melon::z_min - new_position[0];
        }
        return new_position;
    }
    
    // можно добавить
    // шарик может иметь ограниченное время жизни
    // шарик может менять свои размеры
    
};

int main()
{}