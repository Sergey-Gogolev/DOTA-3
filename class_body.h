#include "linal.h"
#include <SFML/Graphics.hpp>

class Body
{
protected:
    Vector position;
    Vector velosity;
    Vector acceleration;

    sf::CircleShape circle;

    bool EnableHitbox;
private:

public:

    Body(Vector pos, Vector vel, Vector acs): position(pos), velosity(vel), acceleration(acs)
    {
        EnableHitbox = true;

        circle.setRadius(30);
        circle.setOutlineThickness(2);
        circle.setFillColor(sf::Color(220,180,250));
        circle.setOutlineColor(sf::Color(0,80,250));
        circle.setPointCount(18);
    };

    Body(): Body(Vector(2), Vector(2), Vector(2)){};

    ~Body(){};

    ////////////////////////

    void SetPos(const Vector& pos)
    {
        position = pos;
    }

    void SetVel(const Vector& vel)
    {
        velosity = vel;
    }

    void SetAcs(const Vector& acs)
    {
        acceleration = acs;
    }

    /////////////////////////

    Vector GetPos() const
    {
        return position;
    }

    Vector GetVel() const
    {
        return velosity;
    }

    Vector GetAcs() const
    {
        return acceleration;
    }

    ////////////////////////

    void CalcMove (const double dt)
    {
        position += velosity * dt + 0.5 * acceleration * dt * dt;
        velosity += acceleration * dt;
    }

    void AddPos(const Vector dpos)
    {
        position += position;
    }

    void AddVel(const Vector dvel)
    {
        velosity += dvel;
    }

    void AddAcs(const Vector dacs)
    {
        acceleration += dacs;
    }

    ///////////////////////

    void SetCircle(const unsigned int R, const unsigned int OT, const sf::Color FC, const sf::Color OC, const unsigned int PC)
    {
        circle.setRadius(R);
        circle.setOutlineThickness(OT);
        circle.setFillColor(FC);
        circle.setOutlineColor(OC);
        circle.setPointCount(PC);
    }

    void Draw(int w, int h, double scale, sf::RenderWindow* app) //Рисуем кружочек в нужном месте. w и h - шрина и высота окна
    {
        circle.setPosition(w/2+ position.getElement(0,0)/scale-circle.getRadius(),h/2+position.getElement(1,0)/scale-circle.getRadius());
        app->draw(circle);
    }

    void SetTexture(const sf::Texture* texture) //Уставливаем текстуру
    {
        this->circle.setOutlineThickness(0);                //внешнюю линию убираем
        this->circle.setFillColor(sf::Color(255,255,255));  //цвет - белый, чтобы текстура не меняла свой цвет
        this->circle.setTexture(texture);
    }

};
