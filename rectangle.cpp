#include "rectangle.h"

Rectangle::Rectangle(double a, double b): a(a), b(b), position(2)
{
    position[0] = -a/2; position[1] = -b/2;
    rectangle.setSize(sf::Vector2f(a, b));
    rectangle.setFillColor(sf::Color::Transparent);
    rectangle.setOutlineColor(sf::Color::Black);
    rectangle.setOutlineThickness(5);
    rectangle.setPosition(0, 0);
}

Rectangle::Rectangle(): Rectangle(780, 580){};
Rectangle::~Rectangle(){};

void Rectangle::SetRectangle(Vector<double> boarders, sf::Color c, unsigned int OT, Vector<double> p)
{
    rectangle.setSize(sf::Vector2f(boarders[0], boarders[1]));
    rectangle.setOutlineColor(c);
    rectangle.setOutlineThickness(OT);
    rectangle.setPosition(p[0], p[1]);
}

void Rectangle::AddPos(const Vector<double> DeltaPos)
{
    position += DeltaPos;
}


Vector<double> Rectangle::GetPos() const
{
    return position;
}

double Rectangle::GetXSize() const
{
    return a;
}

double Rectangle::GetYSize() const
{
    return b;
}

void Rectangle::Draw(int w, int h, double scale, sf::RenderWindow* app)
{
    rectangle.setPosition(w/2 + position[0] ,h/2 + position[1]);
    app->draw(rectangle);
}
