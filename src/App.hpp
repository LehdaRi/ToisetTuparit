#ifndef APP_HPP
#define APP_HPP


#include <SFML/Window.hpp>

#include "Scene.hpp"


class App {
public:
    App(sf::Window& window);

    void loop(void);

private:
    sf::Window&  _window;
};


#endif // APP_HPP
