#include "linal.h"
#include <SFML/Graphics.hpp>
#include "class_body.h"


class Player : public Body
{
protected:
    double MaxHealthPoints;
    double MaxMovementSpeed;
    unsigned int CurrentLevel;
    bool Alive;
    double HealthPoints;
    double ExperiencePoints;
    double ArmorPoints;
    double MovementSpeed;

    double ls_a[2] = {1, 0};
    double us_a[2] = {0, 1};
    Vector ls = Vector(2, ls_a);
    Vector us = Vector(2, us_a);
public:

    Player(Vector pos, Vector vel, Vector acc, unsigned int LVL, double MHP, double MMS, double MS, double ARM): CurrentLevel(LVL), MaxHealthPoints(MHP), MaxMovementSpeed(MMS), MovementSpeed(MS), ArmorPoints(ARM)
    {
        Alive = true;
        HealthPoints = MaxHealthPoints;
        ExperiencePoints = 0;

        circle.setRadius(30);
        circle.setOutlineThickness(2);
        circle.setFillColor(sf::Color(220,180,250));
        circle.setOutlineColor(sf::Color(0,80,250));
        circle.setPointCount(18);
    };

    Player(): Player(Vector(2), Vector(2), Vector(2), 1, 100.0, 100.0, 1.0, 10.0) {};

    ~Player(){};

//////////////////////////////////////////////// Set

    void SetLVL(unsigned int LVL)
    {
        CurrentLevel = LVL;
    }

    void SetMaxHP(float HP)
    {
        MaxHealthPoints = HP;
    }

    void SetHP(float HP)
    {
        HealthPoints = HP;
    }

    void SetMaxMS(float MS)
    {
        MaxMovementSpeed = MS;
    }

    void SetMS(float MS)
    {
        MovementSpeed = MS;
    }

    void SetARM(float ARM)
    {
        ArmorPoints = ARM;
    }

//////////////////////////////////////////////// Get

    unsigned int GetLVL() const
    {
        return CurrentLevel;
    }

    float GetMaxHP() const
    {
        return MaxHealthPoints;
    }

    float GetHP() const
    {
        return HealthPoints;
    }

    float GetMaxMS() const
    {
        return MaxMovementSpeed;
    }

    float GetMs() const
    {
        return MovementSpeed;
    }

    float GetARM() const
    {
        return ArmorPoints;
    }

//////////////////////////////////////////////// Interstellar Overdrive
    void Kill()
    {
        Alive = false;
    };

    void Hit(double DMG)
    {
        HealthPoints -= DMG > ArmorPoints ? DMG - ArmorPoints : 0;
    };

    void Heal(double HP)
    {
        HealthPoints += HP;
    };

    void TakeXP(double XP){};

    bool Update()
    {
        if (HealthPoints < 0)
            Alive = false;
        if (! Alive)
            this->SetCircle(30, 0, sf::Color(250, 0, 0), sf::Color(0, 0, 0), 18);
        return true;
    };


    bool ControlMovement(sf::Event& event)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                this->AddPos(ls * (-1));
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                this->AddPos(us);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                this->AddPos(ls);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                this->AddPos(us * (-1));
        }
        return true;
    };

    void AddPos(const Vector dpos)
    {
        position += dpos * MovementSpeed;
    }

    void CalcMove(const double dt)
    {
        position += MovementSpeed * (velosity * dt + 0.5 * acceleration * dt * dt);
        velosity += acceleration * dt;
    }
};



















