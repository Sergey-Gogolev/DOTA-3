#pragma once

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

    Vector<double> cambox = Vector(2);
    Vector<double> ls = Vector(2);
    Vector<double> us = Vector(2);
public:

    Player(Vector<double> pos, Vector<double> vel, Vector<double> acc, unsigned int LVL, double MHP, double MMS, double MS, double ARM): CurrentLevel(LVL), MaxHealthPoints(MHP), MaxMovementSpeed(MMS), MovementSpeed(MS), ArmorPoints(ARM)
    {
        Alive = true;
        HealthPoints = MaxHealthPoints;
        ExperiencePoints = 0;
        EnableHitbox = true;
        HitboxRadius = 20;

        circle.setRadius(20);
        circle.setOutlineThickness(2);
        circle.setFillColor(sf::Color(0,0,250));
        circle.setOutlineColor(sf::Color(0,0,250));
        circle.setPointCount(18);

        ls[0] = 1; ls[1] = 0; us[0] = 0; us[1] = 1;
    };

    Player(): Player(Vector<double>(2), Vector<double>(2), Vector<double>(2), 1, 100.0, 100.0, 3.0, 10.0) {};

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

    void SetCamBox(double a, double b)
    {
        cambox[0] = a;
        cambox[1] = b;
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

    void AddPos(const Vector<double> dpos)
    {
        position += dpos * MovementSpeed;
    }

    void CalcMove(const double dt, std::vector<Body>& Objects, sf::Event& event)
    {
        Vector<double> DeltaPosition = MovementSpeed * (velosity * dt + 0.5 * acceleration * dt * dt);
        Vector<double> DeltaVelosity = acceleration * dt;
        if (event.type == sf::Event::KeyPressed)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                DeltaPosition -= ls * MovementSpeed;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                DeltaPosition += us * MovementSpeed;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                DeltaPosition += ls * MovementSpeed;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                DeltaPosition -= us * MovementSpeed;
        }

        if (std::abs((position + DeltaPosition)[0]) <= cambox[0])
            position[0] += DeltaPosition[0];
        else
        {
            unsigned n = Objects.size();
            Vector<double>  XCamOffset(2); XCamOffset[0] = -DeltaPosition[0];
            for (unsigned i = 0; i < n; i++)
                Objects[i].AddPos(XCamOffset);
        }

        if (std::abs((position + DeltaPosition)[1]) <= cambox[1])
            position[1] += DeltaPosition[1];
        else
        {
            unsigned n = Objects.size();
            Vector<double>  YCamOffset(2); YCamOffset[1] = -DeltaPosition[1];
            for (unsigned i = 0; i < n; i++)
                Objects[i].AddPos(YCamOffset);
        }
    }

    void CheckCollisions(const std::vector<Body>& Objects)
    {
        unsigned n = Objects.size();
        if (!EnableHitbox)
            return;
        unsigned m = 0;
        for (unsigned i = 0; i < n; i++)
        {
            Vector<double> distance = position - Objects[i].GetPos();
            double mod = std::pow(std::pow(distance[0],2) + std::pow(distance[1], 2), 0.5);
            if (Objects[i].GetHitbox() && (mod <= HitboxRadius + Objects[i].GetHitboxRadius()) ){
                std::cout << "\n  OUCH! " << i << " " << mod;
            }
        }
 //       std::cout << "  OUCH! x" << m;
    }
};



















