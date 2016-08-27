#include "App.hpp"
#include "MeshComponent.hpp"
#include "TransformationComponent.hpp"


App::App(sf::Window& window) :
    _window(window),
    _shader("shaders/VS_Simple.glsl", "shaders/FS_Simple.glsl"),
    _camera(90, 16.0/9.0, 0.1f, 100.0f),
    _renderer(_camera, 1280, 720),
    _time(0.0)
{
    _camera.lookAt(Vector3Glf{0.0f, 5.0f, 10.0f}, Vector3Glf{0.0f, 0.0f, 0.0f});
    _camera.projection(90.0f, 16.0f/9.0f, 0.1f, 100.0f);

    _mesh.loadFromObj("res/obj/fridge.obj");

    _groundNode = SCENE.addNode();
    auto& pc1 = SCENE.addComponent<PhysicsComponent>(_groundNode, _groundNode, Vector3Glf(0.0, 0.0, 0.0),
                                         new btStaticPlaneShape(btVector3(0, 1, 0), 1),
                                         0, btVector3(0, 0, 0));
    SCENE.addComponent<TransformationComponent>(_groundNode, NodeId());
    _physicsWorld.addBody(pc1);

}

void App::loop(void) {
    double ft = 0.0;

    while (_window.isOpen()) {

        if (_time-ft > 2.0) {
            addFridge(Vector3Glf{0.0f, 20.0f, 0.0f});
            ft = _time;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        _physicsWorld.step(1 / 60.f, 1);

        SCENE(_physVisitor);
        SCENE(_transVisitor);
        SCENE(_renderer);

        _camera.lookAt(Vector3Glf{10.0*sin(_time), 5.0f, 10.0*cos(_time)}, Vector3Glf{0.0f, 0.0f, 0.0f});

        _window.display();

        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _window.close();
                break;
            }
        }

        _time += 1 / 60.f;
    }
}

void App::addFridge(const Vector3Glf& pos) {
    auto node = SCENE.addNode();
    SCENE.addComponent<MeshComponent>(node, node, &_mesh, &_shader);
    SCENE.addComponent<TransformationComponent>(node, NodeId());
    auto& pc = SCENE.addComponent<PhysicsComponent>(node, node, pos,
                                         new btBoxShape(btVector3(1.0, 2.0, 1.0)),
                                         1, btVector3(0, 0, 0));
    _physicsWorld.addBody(pc);
}
