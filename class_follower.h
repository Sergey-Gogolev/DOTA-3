#ifndef CLASS_FOLLOWER_H
#define CLASS_FOLLOWER_H

#include "class_body.h"
#include "class_player.h"
#include "rectangle.h"
#include<random>

namespace nFollower
{
    int random_number(int a, int b)
    {
        std::random_device r;
        std::default_random_engine e(r());
        std::uniform_int_distribution<int> dist(a, b);
        return dist(e);
    };
};



class Follower : public Body {
private:
    const Player* player_ptr;
    double DMG;
public:
    Follower(Rectangle& map, Player* p): player_ptr(p)
    {
        this->HitboxRadius = 10;
        this->DMG = nFollower::random_number(10, 30);

        LastHitTimestamp = std::chrono::system_clock::now();
        circle.setRadius(HitboxRadius);
        circle.setOutlineThickness(1);
        circle.setFillColor(sf::Color(0,255,0));
        circle.setOutlineColor(sf::Color(0,0,0));
        circle.setPointCount(3);

        velosity[0] = nFollower::random_number(-100, 100) * 10;
        velosity[1] = nFollower::random_number(-100, 100) * 10;
        position[0] = nFollower::random_number((int)-map.GetXSize()/2.2, (int)map.GetXSize()/2.2);
        position[1] = nFollower::random_number((int)-map.GetYSize()/2.2, (int)map.GetYSize()/2.2);
    };

    ~Follower(){};

    void CalcMove (const double dt, const Rectangle& map)
    {
        Vector new_position = position + velosity * dt + 0.5 * acceleration * dt * dt;
        Vector new_velosity = velosity + (player_ptr->GetPos() - position)/30;

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

    void Draw(int w, int h, double scale, sf::RenderWindow* app)
    {
        circle.setPosition(w/2+ position.getElement(0,0)/scale-circle.getRadius(),h/2+position.getElement(1,0)/scale-circle.getRadius());
        double v_mod = std::pow(velosity[0] * velosity[0] + velosity[1] * velosity[1], 0.5);
        double angle = std::atan2(velosity[0]/v_mod, velosity[1]/v_mod);
        circle.setRotation(180 - angle / 3.14 * 180);
        app->draw(circle);
    }
};

#endif
