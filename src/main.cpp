#include "App.hpp"

int main(void) {
    sf::Window window(sf::VideoMode(1280, 720), "ToisetTuparit", sf::Style::Default,
                      sf::ContextSettings{8, 0, 4, 3, 3});
    window.setFramerateLimit(60);
    window.setActive();

    glewInit();

    glEnable(GL_DEPTH_TEST);

    App app(window);

    app.loop();

    return 0;
}
