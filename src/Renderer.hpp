#ifndef RENDERER_HPP
#define RENDERER_HPP


#include "Visitor.hpp"
#include "MeshComponent.hpp"


class Camera;


class Renderer : public Visitor<Renderer, MeshComponent> {
public:
    Renderer(Camera& camera, uint32_t width, uint32_t height,
             Shader& shader);

    void operator()(MeshComponent& component);

    float time_;
    Eigen::Vector3f lightPos_;

private:
    Camera&             camera_;
    uint32_t            width_;
    uint32_t            height_;

    Shader&  shader_;
};


#endif // RENDERER_HPP
