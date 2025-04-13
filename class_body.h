#pragma once

#include "linal.h"
#include <SFML/Graphics.hpp>

class Body
{
protected:
    Vector<double> position;
    Vector<double> velosity;
    Vector<double> acceleration;

    sf::CircleShape circle;

    double HitboxRadius = 10;
    bool EnableHitbox;
private:

public:

    Body(Vector<double> pos, Vector<double> vel, Vector<double> acs): position(pos), velosity(vel), acceleration(acs)
    {
        EnableHitbox = true;
        circle.setRadius(HitboxRadius);
        circle.setOutlineThickness(1);
        circle.setFillColor(sf::Color(255,0,0));
        circle.setOutlineColor(sf::Color(0,0,0));
        circle.setPointCount(10);
    };

    Body(const Body& that)
    {
        position = that.position;
        velosity = that.velosity;
        acceleration = that.acceleration;
        circle = that.circle;
        EnableHitbox = that.EnableHitbox;
    }

    Body(Body&& that)
    {
        *this = std::move(that);
    }

    Body(): Body(Vector<double>(2), Vector<double>(2), Vector<double>(2)){};

    ~Body(){};

    ////////////////////////

    void SetPos(const Vector<double>& pos)
    {
        position = pos;
    }

    void SetVel(const Vector<double>& vel)
    {
        velosity = vel;
    }

    void SetAcs(const Vector<double>& acs)
    {
        acceleration = acs;
    }

    void SetHitboxRadius(const double r)
    {
        HitboxRadius = r;
    }

    /////////////////////////

    Vector<double> GetPos() const
    {
        return position;
    }

    Vector<double> GetVel() const
    {
        return velosity;
    }

    Vector<double> GetAcs() const
    {
        return acceleration;
    }

    bool GetHitbox() const
    {
        return EnableHitbox;
    }

    double GetHitboxRadius() const
    {
        return HitboxRadius;
    }

    ////////////////////////

    virtual void CalcMove (const double dt)
    {
        position += velosity * dt + 0.5 * acceleration * dt * dt;
        velosity += acceleration    * dt;
    }

    void AddPos(const Vector<double> dpos)
    {
        position += dpos;
    }

    void AddVel(const Vector<double> dvel)
    {
        velosity += dvel;
    }

    void AddAcs(const Vector<double> dacs)
    {
        acceleration += dacs;
    }

    ///////////////////////

    void SetCircle(const unsigned int R, const unsigned int OT, const sf::Color FC, const sf::Color OC, const unsigned int PC)
    {
        HitboxRadius = R;
        circle.setRadius(HitboxRadius);
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

    ///////////////////////

    const Body& operator= (const Body& that)
    {
        if (this == &that)
            return *this;
        position = that.position;
        velosity = that.velosity;
        acceleration = that.acceleration;
        circle = that.circle;
        EnableHitbox = that.EnableHitbox;
        return *this;
    }

    void operator=(Body&& that)
    {
        std::swap(position, that.position);
        std::swap(velosity, that.velosity);
        std::swap(acceleration, that.acceleration);
        std::swap(circle, that.circle);
        std::swap(EnableHitbox, that.EnableHitbox);
    }
};
