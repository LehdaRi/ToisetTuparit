#ifndef APP_HPP
#define APP_HPP


#include <SFML/Window.hpp>

#include "Scene.hpp"
#include "Shader.hpp"
#include "TransformationVisitor.hpp"
#include "Renderer.hpp"
#include "PhysicsWorld.hpp"
#include "PhysicsVisitor.hpp"


class App {
public:
    App(sf::Window& window);

    void loop(void);

    void addFridge(const Vector3Glf& pos);

private:
    sf::Window&             _window;

    Shader                  _shader;
    Mesh                    _mesh;
    PhysicsWorld            _physicsWorld;

    NodeId                  _groundNode;

    Camera                  _camera;
    TransformationVisitor   _transVisitor;
    PhysicsVisitor          _physVisitor;
    Renderer                _renderer;

    double                  _time;
};


#endif // APP_HPP
