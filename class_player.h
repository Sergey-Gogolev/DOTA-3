#ifndef CLASS_PLAYER_H
#define CLASS_PLAYER_H

#include "class_body.cpp"
#include "class_bullet.h"
#include "rectangle.h"

class Player : public Body
{
protected:

    static const unsigned ImmunityFramesDuration = 500;
    double MaxHealthPoints;
    double MaxMovementSpeed;
    unsigned int CurrentLevel;
    bool Alive;
    double HealthPoints;
    double ExperiencePoints;
    double ArmorPoints;
    double MovementSpeed;

    Vector<double> cambox = Vector(2);
    Vector<double> ls = Vector(2);
    Vector<double> us = Vector(2);

public:

    Player(Vector<double> pos, Vector<double> vel, Vector<double> acc, unsigned int LVL, double MHP, double MMS, double MS, double ARM);
    Player();
    ~Player();

//////////////////////////////////////////////// Set

    void SetLVL(unsigned int LVL);
    void SetMaxHP(float HP);
    void SetHP(float HP);
    void SetMaxMS(float MS);
    void SetMS(float MS);
    void SetARM(float ARM);
    void SetCamBox(double a, double b);

//////////////////////////////////////////////// Get

    unsigned int GetLVL() const;
    float GetMaxHP() const;
    float GetHP() const;
    float GetMaxMS() const;
    float GetMs() const;
    float GetARM() const;

//////////////////////////////////////////////// Interstellar Overdrive

    void Hit(double DMG);
    void Heal(double HP);
    void TakeXP(double XP);
    bool Update();
    bool ControlMovement(sf::Event& event);
    void AddPos(const Vector<double> dpos);
    void CalcMove(const double dt, std::vector<Bullet*>& Objects, Rectangle& map, sf::Event& event);
    bool CheckCollisions(const std::vector<Bullet*>& Objects);
    bool IsAlive();
};

#endif
