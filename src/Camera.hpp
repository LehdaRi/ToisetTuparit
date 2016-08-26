#ifndef BASICCAMERA_HPP
#define BASICCAMERA_HPP


#include "MathTypes.hpp"
#include "Canvas.hpp"


class Camera {
public:
    Camera(float fov, float aspectRatio, float near, float far);

    void lookAt(const Vector3f& from, const Vector3f& to,
                const Vector3f& up = Vector3Glf{0.0f, 1.0f, 0.0f});
    void projection(float fov, float aspectRatio, float near, float far);

    void moveLocal(const Vector3f& m);

    const Vector3f& getPosition(void) const;
    const Vector3f& getForward(void) const;
    const Vector3f& getRight(void) const;
    const Vector3f& getUp(void) const;

    Matrix4f getVP(void) const;

    const Matrix4Glf& getOrientation(void) const;
    const Matrix4Glf& getProjection(void) const;

private:
    float fov_;
    float fovRatio_;
    float aspectRatio_;

    Matrix4f orientation_;
    Matrix4f projection_;

    Vector3f position_;
    Vector3f forward_;
    Vector3f right_;
    Vector3f up_;
};


#endif  //  BASICCAMERA_HPP

