#ifndef APP_HPP
#define APP_HPP


#include <SFML/Window.hpp>

#include "Scene.hpp"
#include "Shader.hpp"
#include "TransformationVisitor.hpp"
#include "Renderer.hpp"
#include "FFTVisitor.hpp"


class App {
public:
    App(sf::Window& window);

    void loop(void);

private:
    sf::Window& _window;

    Shader      _shader;
    Mesh        _mesh;

    NodeId      _node;

    Camera      _camera;
    TransformationVisitor _transVisitor;
    Renderer    _renderer;

    Canvas      _canvas;
    double      _time;

    FFTVisitor _fftVisitor;
};


#endif // APP_HPP
