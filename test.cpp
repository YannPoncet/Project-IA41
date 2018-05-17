using namespace std;

#include <SFML/Graphics.hpp>
#include <iostream>


int main()
{

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
<<<<<<< HEAD
=======
        printf("ta mere boris");
>>>>>>> 9c65e8e9e74c2f4b225275c8f57435ff7ad6f1d7
        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
