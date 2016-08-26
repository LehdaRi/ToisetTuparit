#ifndef MESHCOMPONENT_HPP
#define MESHCOMPONENT_HPP


#include "ComponentBase.hpp"
#include "NodeId.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"


class MeshComponent : public ComponentBase {
public:
    friend class Renderer;

    MeshComponent(const NodeId& node, Mesh* mesh, Shader* shader);
    MeshComponent(const NodeId& node, const MeshComponent& other);

private:
    NodeId  node_;
    Mesh*   mesh_;
    Shader* shader_;
};


#endif // MESHCOMPONENT_HPP
