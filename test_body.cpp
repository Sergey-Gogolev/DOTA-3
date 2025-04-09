#include "class_body.h"

int main()
{
    double dt = 0.001;
    Vector<double> ls = Vector(2); ls[0] = 1; ls[1] = 0;
    Vector<double> us = Vector(2); us[0] = 0; us[1] = 1;
    Body chel1;
    Body chel2;
    chel1.SetAcs(500 * ls + 500 * us);
    chel1.SetCircle(50, 30, sf::Color(0,0,250), sf::Color(250,0,0), 3);
    chel2.SetVel(-100 * ls + -10 * us);

    sf::RenderWindow app(sf::VideoMode(800, 600), "SFML window");

    unsigned int i = 0;
    while (app.isOpen())
    {
        i ++;
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) //Если окно закрыли, надо заканчивать работу с ним
                app.close();
        }
        app.clear(sf::Color(250,250,220));

        chel1.CalcMove(dt);
        chel2.CalcMove(dt);
        //Вызываем методы отрисовки для всех
        chel1.Draw(800,600,1,&app);
        chel2.Draw(800,600,1,&app);

        // Заставляем окно обновиться и нарисовать всё
        app.display();
    }
    return 0;
}
