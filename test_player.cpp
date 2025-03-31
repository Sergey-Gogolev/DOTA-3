#include "class_player.h"
#include "balls_of_death_reworked.cpp"


int main()
{
    Melon::x_max = 100;
    Melon::x_min = -100;
    Melon::y_max = 100;
    Melon::y_min = -100;
    double dt = 0.001;

    Body* balls = new Body[10];
    Player p;

    for (int i = 0; i < 10; i++)
    {
        double Vx = Melon::random_number(Melon::x_min, Melon::x_max);
        double Vy = Melon::random_number(Melon::y_min, Melon::y_max);
        Vector v(2);
        v[0] = Vx; v[1] = Vy;
        balls[i].SetVel(v);
        std::cout << balls[i].GetVel() << std::endl;

    }

    sf::RenderWindow app(sf::VideoMode(800, 600), "SFML window");

    while (app.isOpen())
    {
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) //Если окно закрыли, надо заканчивать работу с ним
                app.close();
        p.ControlMovement(event);
        }

        p.CalcMove(dt);
        for (int i = 0; i < 10; i++)
            balls[i].CalcMove(dt);


        app.clear(sf::Color(250,250,220));
        p.Draw(800,600,1,&app);
        for (int i = 0; i < 10; i++)
            balls[i].Draw(800,600,1,&app);

        app.display();
    }
    return 0;
}


/*



*/
