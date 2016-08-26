#include "App.hpp"
#include "MeshComponent.hpp"
#include "TransformationComponent.hpp"


App::App(sf::Window& window) :
    _window(window),
    _shader("shaders/VS_Simple.glsl", "shaders/FS_Simple.glsl"),
    _camera(90, 16.0/9.0, 0.1f, 100.0f),
    _renderer(_camera, 1920, 1080),
    _time(0.0)
{
    _camera.lookAt(Vector3Glf{0.0f, 5.0f, 10.0f}, Vector3Glf{0.0f, 0.0f, 0.0f});
    _camera.projection(90.0f, 16.0f/9.0f, 0.1f, 100.0f);

    _mesh.loadFromObj("res/obj/icosphere.obj");

    _node = SCENE.addNode();
    SCENE.addComponent<MeshComponent>(_node, _node, &_mesh, &_shader);
    SCENE.addComponent<TransformationComponent>(_node, NodeId());

}

void App::loop(void) {
    while (_window.isOpen()) {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        SCENE(_transVisitor);
        SCENE(_renderer);

        _camera.lookAt(Vector3Glf{10.0*sin(_time*100), 5.0f, 10.0*cos(_time*100)}, Vector3Glf{0.0f, 0.0f, 0.0f});

        //glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

        //_canvas.draw(_shader);

        _window.display();

        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _window.close();
                break;
            }
        }

        _time += 0.001;
    }
}
