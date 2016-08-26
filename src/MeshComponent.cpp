#include "MeshComponent.hpp"


MeshComponent::MeshComponent(const NodeId& node, Mesh* mesh, Shader* shader) :
    node_   (node),
    mesh_   (mesh),
    shader_ (shader)
{}

MeshComponent::MeshComponent(const NodeId& node, const MeshComponent& other) :
    node_   (node),
    mesh_   (other.mesh_),
    shader_ (other.shader_)
{}
