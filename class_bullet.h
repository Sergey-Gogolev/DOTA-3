#ifndef CLASS_BULLET_H
#define CLASS_BULLET_H

#include "class_body.h"
#include "rectangle.h"
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


class Bullet : public Body {
private:
    double DMG;
public:
    Bullet(Rectangle& map)
    {
        LastHitTimestamp = std::chrono::system_clock::now();
        circle.setRadius(HitboxRadius);
        circle.setOutlineThickness(1);
        circle.setFillColor(sf::Color(255,0,0));
        circle.setOutlineColor(sf::Color(0,0,0));
        circle.setPointCount(10);

        this->HitboxRadius = Melon::random_number(5, 15);
        velosity[0] = Melon::random_number(-100, 100) * 10;
        velosity[1] = Melon::random_number(-100, 100) * 10;
        position[0] = Melon::random_number((int)-map.GetXSize()/2.2, (int)map.GetXSize()/2.2);
        position[1] = Melon::random_number((int)-map.GetYSize()/2.2, (int)map.GetYSize()/2.2);

        this->DMG = Melon::random_number(10, 30);
    };
    ~Bullet(){};

    void virtual CalcMove (const double dt, const Rectangle& map)
    {
        Vector new_position = position + velosity * dt + 0.5 * acceleration * dt * dt;
        Vector new_velosity = velosity + acceleration * dt;

        if (new_position[0] - HitboxRadius < map.GetPos()[0])
            new_velosity[0] = -new_velosity[0];
        else if (new_position[0] + HitboxRadius > map.GetPos()[0] + map.GetXSize())
            new_velosity[0] = -new_velosity[0];

        if (new_position[1] - HitboxRadius < map.GetPos()[1])
            new_velosity[1] = -new_velosity[1];
        else if (new_position[1] + HitboxRadius > map.GetPos()[1] + map.GetYSize())
            new_velosity[1] = -new_velosity[1];

        /*
        else if (new_position[0] - radius_ < map.GetXSize())
        {
        //    new_position[0] = 2 * GetLeft(GetRectangle()) - new_position[0];
            new_velosity[0] = -new_velosity[0];
        }
        else if (new_position[1] + radius_ > map.GetYSize())
        {
            //new_position[1] = 2 * GetUp(GetRectangle()) - new_position[1];
            new_velosity[1] = -new_velosity[1];
        }
        else if (new_position[1] - radius_ < map.GetYSize())
        {
            //new_position[1] = 2 * GetDown(GetRectangle()) - new_position[1];
            new_velosity[1] = -new_velosity[1];
        }
        */

        position = new_position;
        velosity = new_velosity;
    }

};

#endif
