#include "class_player.h"

Player::Player(Vector<double> pos, Vector<double> vel, Vector<double> acc, unsigned int LVL, double MHP, double MMS, double MS, double ARM): CurrentLevel(LVL), MaxHealthPoints(MHP), MaxMovementSpeed(MMS), MovementSpeed(MS), ArmorPoints(ARM)
{
    Alive = true;
    HealthPoints = MaxHealthPoints;
    ExperiencePoints = 0;
    HitboxRadius = 20;

    circle.setRadius(20);
    circle.setOutlineThickness(2);
    circle.setFillColor(sf::Color(0,0,250));
    circle.setOutlineColor(sf::Color(0,0,250));
    circle.setPointCount(18);

    ls[0] = 1; ls[1] = 0; us[0] = 0; us[1] = 1;
};

Player::Player(): Player(Vector<double>(2), Vector<double>(2), Vector<double>(2), 1, 100.0, 100.0, 3.0, 10.0) {};

Player::~Player(){};

//////////////////////////////////////////////// Set

void Player::SetLVL(unsigned int LVL)
{
    CurrentLevel = LVL;
}

void Player::SetMaxHP(float HP)
{
    MaxHealthPoints = HP;
}

void Player::SetHP(float HP)
{
    HealthPoints = HP;
}

void Player::SetMaxMS(float MS)
{
    MaxMovementSpeed = MS;
}

void Player::SetMS(float MS)
{
    MovementSpeed = MS;
}

void Player::SetARM(float ARM)
{
    ArmorPoints = ARM;
}

void Player::SetCamBox(double a, double b)
{
    cambox[0] = a;
    cambox[1] = b;
}
//////////////////////////////////////////////// Get

unsigned int Player::GetLVL() const
{
    return CurrentLevel;
}

float Player::GetMaxHP() const
{
    return MaxHealthPoints;
}

float Player::GetHP() const
{
    return HealthPoints;
}

float Player::GetMaxMS() const
{
    return MaxMovementSpeed;
}

float Player::GetMs() const
{
    return MovementSpeed;
}

float Player::GetARM() const
{
    return ArmorPoints;
}

//////////////////////////////////////////////// Interstellar Overdrive

void Player::Hit(double DMG)
{
    HealthPoints -= DMG > ArmorPoints ? DMG - ArmorPoints : 0;
};

void Player::Heal(double HP)
{
    HealthPoints += HP;
};

void Player::TakeXP(double XP){};

bool Player::Update()
{
    if (HealthPoints < 0)
        Alive = false;
    if (! Alive)
        this->SetCircle(30, 0, sf::Color(250, 0, 0), sf::Color(0, 0, 0), 18);
    return true;
};


bool Player::ControlMovement(sf::Event& event)
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

void Player::AddPos(const Vector<double> dpos)
{
    position += dpos * MovementSpeed;
}

void Player::CalcMove(const double dt, std::vector<Body*>& Objects, Rectangle& map, sf::Event& event)
{
    Vector mapPos = map.GetPos();
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
        if ((mapPos - position - DeltaPosition)[0] > -HitboxRadius)
        {
            DeltaPosition[0] = (mapPos - position)[0] + HitboxRadius;
        }
        else if ((mapPos - position - DeltaPosition)[0] + map.GetXSize() < HitboxRadius)
        {
            DeltaPosition[0] = (mapPos - position)[0] - HitboxRadius + map.GetXSize();
        }
        unsigned n = Objects.size();
        Vector<double>  XCamOffset(2); XCamOffset[0] = -DeltaPosition[0];
        for (unsigned i = 0; i < n; i++)
            Objects[i]->AddPos(XCamOffset);

        map.AddPos(XCamOffset);

    }


    if (std::abs((position + DeltaPosition)[1]) <= cambox[1])
        position[1] += DeltaPosition[1];
    else
    {
        if ((mapPos - position - DeltaPosition)[1] > -HitboxRadius)
        {
            DeltaPosition[1] = (mapPos - position)[1] + HitboxRadius;
        }
        else if ((mapPos - position - DeltaPosition)[1] + map.GetYSize() < HitboxRadius)
        {
            DeltaPosition[1] = (mapPos - position)[1] - HitboxRadius + map.GetYSize();
        }
        unsigned n = Objects.size();
        Vector<double>  YCamOffset(2); YCamOffset[1] = -DeltaPosition[1];
        for (unsigned i = 0; i < n; i++)
            Objects[i]->AddPos(YCamOffset);
        map.AddPos(YCamOffset);
    }
}

std::vector<Body*>::iterator Player::CheckCollisions(std::vector<Body*>& Objects)
{
    unsigned n = Objects.size();
    if ( std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - this->LastHitTimestamp).count() <= this->ImmunityFramesDuration)
        return Objects.end();
    for (unsigned i = 0; i < n; i++)
    {
        Vector<double> distance = position - Objects[i]->GetPos();
        double mod = std::pow(std::pow(distance[0],2) + std::pow(distance[1], 2), 0.5);
        if (mod <= HitboxRadius + Objects[i]->GetHitboxRadius()){
            this->Hit(20);
            LastHitTimestamp = std::chrono::system_clock::now();
            return Objects.begin() + i;
        }
    }
    return Objects.end();
}

bool Player::IsAlive()
{
    if (HealthPoints > 0)
        return true;
    else
    {
        this->Alive = false;
        this->SetCircle(20, 0, sf::Color(0,0, 0), sf::Color(0,0,0), 15);
        return false;
    }
    return true;
}




















