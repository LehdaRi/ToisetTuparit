#include "Camera.hpp"

#include <iostream> //  TEMP


Camera::Camera(float fov, float aspectRatio, float near, float far) :
    fov_(fov), fovRatio_(tan(fov_*0.5f)), aspectRatio_(aspectRatio),
    orientation_(Matrix4f::Identity())
{
    projection(fov_, aspectRatio_, near, far);
}

void Camera::lookAt(const Vector3f& from, const Vector3f& to, const Vector3f& up) {
    position_ = from;
    forward_ = (to - from).normalized();
    right_ = up.cross(-forward_).normalized();
    up_ = -forward_.cross(right_);

    orientation_ << right_[0]       , right_[1]     , right_[2]     , -right_.dot(position_),
                    up_[0]          , up_[1]        , up_[2]        , -up_.dot(position_),
                    -forward_[0]    , -forward_[1]  , -forward_[2]  , forward_.dot(position_) ,
                    0.0f            , 0.0f          , 0.0f          , 1.0f;
}

void Camera::projection(float fov, float aspectRatio, float near, float far) {
    float r = tanf(fov / 2.0f) * near;
    float t = r / aspectRatio;

    projection_ << near/r   , 0.0f      , 0.0f                  , 0.0f                      ,
                   0.0f     , near/t    , 0.0f                  , 0.0f                      ,
                   0.0f     , 0.0f      , -(far+near)/(far-near), -2.0f*far*near/(far-near) ,
                   0.0f     , 0.0f      , -1.0f                 , 0.0f                      ;
}

void Camera::moveLocal(const Vector3f& m) {
    Vector4f m2;
    m2 << m, 0.0f;
    auto m3 = orientation_.transpose()*m2;
    position_ += m3.block<3,1>(0, 0);

    Matrix4f move;
    move <<   1.0f , 0.0f , 0.0f , -m[0],
              0.0f , 1.0f , 0.0f , -m[1],
              0.0f , 0.0f , 1.0f , -m[2],
              0.0f , 0.0f , 0.0f , 1.0f;

    orientation_ = move*orientation_;
}

const Vector3f& Camera::getPosition(void) const {
    return position_;
}

const Vector3f& Camera::getForward(void) const {
    return forward_;
}

const Vector3f& Camera::getRight(void) const {
    return right_;
}

const Vector3f& Camera::getUp(void) const {
    return up_;
}

Matrix4f Camera::getVP(void) const {
    return projection_ * orientation_;
}
/*
Ray Camera::generateRay(float x, float y, unsigned viewWidth, unsigned viewHeight) const {
    Ray out;

    float sx = ((x/viewWidth)*2.0f - 1.0f) * fovRatio_;
    float sy = ((y/viewHeight)*2.0f - 1.0f) * (fovRatio_/aspectRatio_);

    out.o = position_;
    out.d = (forward_ + sx*right_ + sy*up_).normalized();
    out.t = FLT_MAX;

    return out;
}*/

const Matrix4Glf& Camera::getOrientation(void) const {
    return orientation_;
}

const Matrix4Glf& Camera::getProjection(void) const {
    return projection_;
}
