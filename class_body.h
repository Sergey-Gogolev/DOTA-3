#ifndef CLASS_BODY_H
#define CLASS_BODY_H

#include <SFML/Graphics.hpp>
#include "linal.h"
#include "rectangle.h"
#include "chrono"

class Body
{
protected:

    Vector<double> position;
    Vector<double> velosity;
    Vector<double> acceleration;
    sf::CircleShape circle;
    double HitboxRadius = 10;
    std::chrono::time_point<std::chrono::system_clock> LastHitTimestamp;

public:
    /////////////////////// Construcors

    Body(Vector<double> pos, Vector<double> vel, Vector<double> acs);
    Body(const Body& that);
    Body(Body&& that);
    Body();
    ~Body();

    /////////////////////// Set smth

    void SetPos(const Vector<double>& pos);
    void SetVel(const Vector<double>& vel);
    void SetAcs(const Vector<double>& acs);
    void SetHitboxRadius(const double r);

    ///////////////////////// Get smth

    Vector<double> GetPos() const;
    Vector<double> GetVel() const;
    Vector<double> GetAcs() const;
    std::chrono::milliseconds GetLastHitTimestamp() const;
    double GetHitboxRadius() const;

    //////////////////////// Kinematiсs

    virtual void CalcMove (const double dt, Rectangle& map);
    void AddPos(const Vector<double> dpos);
    void AddVel(const Vector<double> dvel);
    void AddAcs(const Vector<double> dacs);

    /////////////////////// Texture

    void SetCircle(const unsigned int R, const unsigned int OT, const sf::Color FC, const sf::Color OC, const unsigned int PC);
    void Draw(int w, int h, double scale, sf::RenderWindow* app);
    void SetTexture(const sf::Texture* texture);

    /////////////////////// Operators overload

    const Body& operator= (const Body& that);
    void operator=(Body&& that);
};

#endif
