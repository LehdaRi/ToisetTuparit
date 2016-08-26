#include "Renderer.hpp"
#include "Camera.hpp"
#include "Node.hpp"
#include "TransformationComponent.hpp"
#include "Scene.hpp"

#include <Eigen/Dense>


Renderer::Renderer(Camera& camera, uint32_t width, uint32_t height) :
    camera_         (camera),
    width_          (width),
    height_         (height)
{
	camera_.projection(90.0f, (float)width/(float)height, 0.1f, 100.0f);
}

void Renderer::operator()(MeshComponent& component) {
    auto& tc = component.node_.ref().getComponent<TransformationComponent>();
    Matrix4f model = tc.mCumulative_;

	//GLint old_fbo; glGetIntegerv(GL_FRAMEBUFFER_BINDING, &old_fbo);
	//glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_);

	glViewport(0, 0, width_, height_);

	Matrix4f model_to_clip = camera_.getProjection() * camera_.getOrientation() * model;
	Matrix3f normal_to_world = model.block<3, 3>(0, 0).inverse().transpose();

	// Get the uniform locations from OpenGL.
	GLuint model_to_clip_uniform, normal_to_world_uniform, time_uniform,
           light_position_uniform, model_to_world_uniform;

	model_to_clip_uniform = glGetUniformLocation(*component.shader_, "uModelToClip");
	normal_to_world_uniform = glGetUniformLocation(*component.shader_, "uNormalToWorld");
	model_to_world_uniform = glGetUniformLocation(*component.shader_, "uModelToWorld");
    time_uniform = glGetUniformLocation(*component.shader_, "uTime");
    light_position_uniform = glGetUniformLocation(*component.shader_, "uLightPosition");


	// Set the uniforms and draw.
	glUseProgram(*component.shader_);

	glUniformMatrix4fv(model_to_clip_uniform, 1, GL_FALSE, model_to_clip.data());
	glUniformMatrix3fv(normal_to_world_uniform, 1, GL_FALSE, normal_to_world.data());
	glUniformMatrix4fv(model_to_world_uniform, 1, GL_FALSE, model.data());
	//glUniform3fv(light_position_uniform, 1, lightPos_.data());
    glUniform1f(time_uniform, time_);

    component.mesh_->draw();

	glUseProgram(0);

	//glBindFramebuffer(GL_FRAMEBUFFER, old_fbo);
}
