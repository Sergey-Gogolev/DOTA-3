#include "class_bullet.h"
#include "rectangle.cpp"
#include <cstdio>
#include <cstring>

int main()
{
    double dt = 0.005;
    unsigned int phy_engine_update_delay = 1000;
    unsigned long long int render_engine_update_delay = 5000;
    std::cout << std::boolalpha;

    Rectangle map;

    std::vector<Bullet*> bullets;
    for (int i = 0; i < 500; i++)
        bullets.push_back(new Bullet(map));

    sf::Font font;
    if (!font.loadFromFile("Driagwa.ttf"))  return EXIT_FAILURE;

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
            for (std::vector<Bullet*>::iterator it = bullets.begin(); it < bullets.end(); ++it)
                (*it)->CalcMove(dt, map);
            phy_engine_timing = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now());
            phy_it++;
        }

        if ((std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()) - render_engine_timing).count() >= render_engine_update_delay)
        {
            app.clear(sf::Color(250,250,220));

            map.Draw(800,600,1,&app);

            for (std::vector<Bullet*>::iterator it = bullets.begin(); it < bullets.end(); ++it)
                (*it)->Draw(800,600,1,&app);

            app.display();
            frame++;
            render_engine_timing = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now());
        }
    }
    std::cout << "\nMean FPS:" << frame / (std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now()) - programm_start_timing).count();
    std::cout << "\nMean IPS:" << phy_it / (std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now()) - programm_start_timing).count() << std::endl;
    return 0;
}


