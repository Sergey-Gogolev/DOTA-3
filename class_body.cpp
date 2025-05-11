#include "class_body.h"

Body::Body(Vector<double> pos, Vector<double> vel, Vector<double> acs): position(pos), velosity(vel), acceleration(acs)
{
    LastHitTimestamp = std::chrono::system_clock::now();
    circle.setRadius(HitboxRadius);
    circle.setOutlineThickness(1);
    circle.setFillColor(sf::Color(255,0,0));
    circle.setOutlineColor(sf::Color(0,0,0));
    circle.setPointCount(10);
}

Body::Body(const Body& that)
{
    LastHitTimestamp = that.LastHitTimestamp;
    position = that.position;
    velosity = that.velosity;
    acceleration = that.acceleration;
    circle = that.circle;
}

Body::Body(Body&& that)
{
    *this = std::move(that);
}

Body::Body(): Body(Vector<double>(2), Vector<double>(2), Vector<double>(2)){};

Body::~Body(){};

    ///////////////////////

void Body::SetPos(const Vector<double>& pos)
{
    position = pos;
}

void Body::SetVel(const Vector<double>& vel)
{
    velosity = vel;
}

void Body::SetAcs(const Vector<double>& acs)
{
    acceleration = acs;
}

void Body::SetHitboxRadius(const double r)
{
    HitboxRadius = r;
}

    /////////////////////////

Vector<double> Body::GetPos() const
{
    return position;
}

Vector<double> Body::GetVel() const
{
    return velosity;
}

Vector<double> Body::GetAcs() const
{
    return acceleration;
}

std::chrono::milliseconds Body::GetLastHitTimestamp() const
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - LastHitTimestamp);
}

double Body::GetHitboxRadius() const
{
    return HitboxRadius;
}

    ////////////////////////

void Body::CalcMove(const double dt, const Rectangle& map)
{
    position += velosity * dt + 0.5 * acceleration * dt * dt;
    velosity += acceleration    * dt;
}

void Body::AddPos(const Vector<double> dpos)
{
    position += dpos;
}

void Body::AddVel(const Vector<double> dvel)
{
    velosity += dvel;
}

void Body::AddAcs(const Vector<double> dacs)
{
    acceleration += dacs;
}

    ///////////////////////

void Body::SetCircle(const unsigned int R, const unsigned int OT, const sf::Color FC, const sf::Color OC, const unsigned int PC)
{
    HitboxRadius = R;
    circle.setRadius(HitboxRadius);
    circle.setOutlineThickness(OT);
    circle.setFillColor(FC);
    circle.setOutlineColor(OC);
    circle.setPointCount(PC);
}

void Body::Draw(int w, int h, double scale, sf::RenderWindow* app)
{
    circle.setPosition(w/2+ position.getElement(0,0)/scale-circle.getRadius(),h/2+position.getElement(1,0)/scale-circle.getRadius());
    app->draw(circle);
}

void Body::SetTexture(const sf::Texture* texture)
{
    this->circle.setOutlineThickness(0);
    this->circle.setFillColor(sf::Color(255,255,255));
    this->circle.setTexture(texture);
}

    ///////////////////////

const Body& Body::operator= (const Body& that)
{
    if (this == &that)
        return *this;
    position = that.position;
    velosity = that.velosity;
    acceleration = that.acceleration;
    circle = that.circle;
    LastHitTimestamp = that.LastHitTimestamp;
    return *this;
}

void Body::operator=(Body&& that)
{
    std::swap(position, that.position);
    std::swap(velosity, that.velosity);
    std::swap(acceleration, that.acceleration);
    std::swap(circle, that.circle);
    std::swap(LastHitTimestamp, that.LastHitTimestamp);
}
