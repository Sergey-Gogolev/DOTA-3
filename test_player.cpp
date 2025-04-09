#include "class_player.h"
#include "balls_of_death_reworked.cpp"
#include "chrono"
#include <cstdio>
#include <cstring>

int main()
{
    Melon::x_max = 100;
    Melon::x_min = -100;
    Melon::y_max = 100;
    Melon::y_min = -100;
    double dt = 0.001;
    unsigned int phy_engine_update_delay = 5000;
    unsigned long long int render_engine_update_delay = 20000;

    Player p;
    p.SetCamBox(20, 20);
    Vector<double> start_pos(2); start_pos[0] = 20; start_pos[1] = 0;
    p.SetPos(std::move(start_pos));

    double firewood = 0; // trash

    std::vector<Body> balls;
    for (int i = 0; i < 10; i++)
    {
        balls.push_back(Body());
        double Vx = Melon::random_number(Melon::x_min, Melon::x_max);
        double Vy = Melon::random_number(Melon::y_min, Melon::y_max);
        Vector v(2);
        v[0] = Vx; v[1] = Vy;
        firewood += Vx + Vy;
        balls[i].SetVel(v);
        std::cout << "\n Ball number " << &(balls[i]) << " initial velosity: " << balls[i].GetVel() << " and radous: " << balls[i].GetHitboxRadius();
    }

    sf::Font font; //Нужно загрузить шрифт из файла
    if (!font.loadFromFile("Driagwa.ttf"))  return EXIT_FAILURE;
    sf::Text text; //Это наша надпись
    text.setString("The price of firewood: " + std::to_string(firewood));
    text.setFont(font);//шрифт
    text.setCharacterSize(18);//размер
    text.setFillColor(sf::Color::Red);//цвет
    text.setPosition(100, 100);


    sf::RenderWindow app(sf::VideoMode(800, 600), "SFML window");

    auto phy_engine_timing = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now());
    auto render_engine_timing = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now());
    auto programm_start_timing = std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now());
    unsigned int frame = 0;
    unsigned int phy_it = 0;

    while (app.isOpen())
    {
        if ((std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()) - phy_engine_timing).count() >= phy_engine_update_delay)
        {
            sf::Event event;
            while (app.pollEvent(event))
            {
                if (event.type == sf::Event::Closed) //Если окно закрыли, надо заканчивать работу с ним
                    app.close();
                p.CalcMove(dt, balls, event);
            }
            for (int i = 0; i < 10; i++)
                balls[i].CalcMove(dt);
            p.CheckCollisions(balls);
            phy_engine_timing = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now());
            phy_it++;
        }

        if ((std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()) - render_engine_timing).count() >= render_engine_update_delay)
        {
            app.clear(sf::Color(250,250,220));
            p.Draw(800,600,1,&app);
            for (int i = 0; i < 10; i++)
                balls[i].Draw(800,600,1,&app);
            app.draw(text);
            app.display();
            std::cout << "\nPlayer's position: " << p.GetPos();
            frame++;
            render_engine_timing = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now());
        }
    }
    std::cout << "\nMean FPS:" << frame / (std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now()) - programm_start_timing).count();
    std::cout << "\nMean IPS:" << phy_it / (std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now()) - programm_start_timing).count() << std::endl;
    return 0;
}


/*



*/
