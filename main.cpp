#include "class_player.cpp"
#include "class_bullet.h"
#include "rectangle.cpp"
#include <cstdio>
#include <cstring>


std::string GetStrHPBar (double hp, double mhp)
{
    std::string s = "[";
    int del = (int)std::round(hp) / 10;
    for (int i = 0; i < (int)std::round(mhp) / 10; i++)
        if (i < del)
            s += '|';
        else
            s += '.';
    s += ']';
    return s;
}

int main()
{
    double dt = 0.001;
    unsigned int phy_engine_update_delay = 5000;
    unsigned long long int render_engine_update_delay = 20000;
    std::cout << std::boolalpha;

    Rectangle map;

    Player* p = new Player();
    p->SetCamBox(20, 20);
    Vector<double> start_pos(2); start_pos[0] = 0; start_pos[1] = 0;
    p->SetPos(std::move(start_pos));


    unsigned int NumberOfBullets = 20;
    std::vector<Bullet*> bullets;
    for (int i = 0; i < NumberOfBullets; i++)
        bullets.push_back(new Bullet(map));

    sf::Font font;
    if (!font.loadFromFile("Driagwa.ttf"))  return EXIT_FAILURE;

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Red);
    text.setPosition(20, 20);

    sf::Text WaistedText;
    WaistedText.setString("YOU ARE \"GOM\" ");
    WaistedText.setFont(font);//шрифтo
    WaistedText.setCharacterSize(50);//размер
    WaistedText.setFillColor(sf::Color::Black);//цвет
    WaistedText.setPosition(300, 150);

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
            if (p->IsAlive())
            {
                while (app.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed) //Если окно закрыли, надо заканчивать работу с ним
                        app.close();
                    p->CalcMove(dt, bullets, map, event);
                }
                p->CheckCollisions(bullets);
            }
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

            if (p->IsAlive())
            {
                text.setString("HP: " + GetStrHPBar(p->GetHP(), p->GetMaxHP()));
                p->Draw(800,600,1,&app);
                app.draw(text);
            }
            else
            {
                p->Draw(800,600,1,&app);
                app.draw(WaistedText);
            }
            app.display();
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
