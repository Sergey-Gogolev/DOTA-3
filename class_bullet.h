#ifndef CLASS_BULLET_H
#define CLASS_BULLET_H

#include "class_body.h"
#include "rectangle.h"
#include<random>


namespace nBullet
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
        this->HitboxRadius = nBullet::random_number(5, 15);
        this->DMG = nBullet::random_number(10, 30);

        LastHitTimestamp = std::chrono::system_clock::now();
        circle.setRadius(HitboxRadius);
        circle.setOutlineThickness(1);
        circle.setFillColor(sf::Color(255,0,0));
        circle.setOutlineColor(sf::Color(0,0,0));
        circle.setPointCount(10);

        velosity[0] = nBullet::random_number(-100, 100) * 10;
        velosity[1] = nBullet::random_number(-100, 100) * 10;
        position[0] = nBullet::random_number((int)-map.GetXSize()/2.2, (int)map.GetXSize()/2.2);
        position[1] = nBullet::random_number((int)-map.GetYSize()/2.2, (int)map.GetYSize()/2.2);
    };
    ~Bullet(){};

    void CalcMove (const double dt, const Rectangle& map)
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

        position = new_position;
        velosity = new_velosity;
    }

};

#endif
