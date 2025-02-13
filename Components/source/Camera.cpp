#include "Camera.h"

#include <iostream>

Camera::Camera()
{
    e = Vector4(0, 0, 20);
    d = Vector4(0, 0, -1);
    up = Vector4(0, 1, 0);
    calculate_camera_matrix();
}

Camera::Camera(const Vector4& e, const Vector4& d, const Vector4& up)
{
    this->e = e;
    this->d = d;
    this->up = up;
    calculate_camera_matrix();
}

Camera::~Camera()
{
}

void Camera::calculate_camera_matrix()
{
    Vector4 x, y, z;
    Matrix4 R, T;
    z = e - d; z.normalize();
    x = up.cross(z); x.normalize();
    y = z.cross(x);

    R.identity();
    R.setColumn(0, x);
    R.setColumn(1, y);
    R.setColumn(2, z);

    T.identity();
    T.setColumn(3, -e);

    world2camera = R.transpose() * T;
    world2camera.transpose();
}

Matrix4& Camera::getMatrix()
{
    return world2camera;
}

double* Camera::getGLMatrix()
{
    return getMatrix().getPointer();
}

void Camera::set_center_of_proj(const Vector4& e)
{
    this->e = e;
    calculate_camera_matrix();
}

void Camera::set_center_of_proj(double x, double y, double z)
{
    this->e = Vector4(x, y, z);
    calculate_camera_matrix();
}

void Camera::look_at(const Vector4& d)
{
    this->d = d;
    calculate_camera_matrix();
}

void Camera::look_at(double x, double y, double z)
{
    this->d = Vector4(x, y, z);
    calculate_camera_matrix();
}

void Camera::set_up(const Vector4& up)
{
    this->up = up;
    calculate_camera_matrix();
}

void Camera::set_up(double x, double y, double z)
{
    this->up = Vector4(x, y, z);
    calculate_camera_matrix();
}
