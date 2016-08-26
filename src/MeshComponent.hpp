#ifndef MESHCOMPONENT_HPP
#define MESHCOMPONENT_HPP


#include "ComponentBase.hpp"
#include "NodeId.hpp"
#include "Mesh.hpp"


class MeshComponent : public ComponentBase {
public:
    friend class Renderer;
    friend class SpotlightRenderer;

    MeshComponent(const NodeId& node, Mesh* mesh);
    MeshComponent(const NodeId& node, const MeshComponent& other);

private:
    NodeId node_;
    Mesh* mesh_;
};


#endif // MESHCOMPONENT_HPP
