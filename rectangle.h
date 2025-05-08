#ifndef CLASS_RECTANGLE_H
#define CLASS_RECTANGLE_H


class Rectangle{
 //   friend void Player::CalcMove(const double dt, std::vector<Body>& Objects, Rectangle& map, sf::Event& event);
private:

    sf::RectangleShape rectangle;
    Vector<double> position;
    double a;
    double b;

public:
    Rectangle(double a, double b);
    Rectangle();
    ~Rectangle();

    void SetRectangle(Vector<double> boarders, sf::Color c, unsigned int OT, Vector<double> p);
    void AddPos(const Vector<double> DeltaPos);
    Vector<double> GetPos() const;
    double GetXSize() const;
    double GetYSize() const;
    void Draw(int w, int h, double scale, sf::RenderWindow* app);

};
#endif
