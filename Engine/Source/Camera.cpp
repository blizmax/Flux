/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Camera.cpp
** Implements a camera class containing functions perform perspective or
** orthographic transformations on a matrix
**
** Author: Julian Thijssen
** -------------------------------------------------------------------------*/

#include "Camera.h"

#include "Matrix4f.h"
#include "Math.h"
#include <math.h>

namespace Flux {
    Camera::Camera() {

    }

    Camera::Camera(float left, float right, float bottom, float top, float zNear, float zFar) :
        left(left),
        right(right),
        bottom(bottom),
        top(top),
        zNear(zNear),
        zFar(zFar) {

    }

    Camera::Camera(float fovy, float aspect, float zNear, float zFar) :
        fovy(fovy),
        aspect(aspect),
        zNear(zNear),
        zFar(zFar) {

    }

    void Camera::loadProjectionMatrix(Matrix4f& m) {
        m.setIdentity();
        if (perspective) {
            float fovyr = Math::toRadians(fovy);
            m[0] = (float)(1 / tan(fovyr / 2)) / aspect;
            m[5] = (float)(1 / tan(fovyr / 2));
            m[10] = (zNear + zFar) / (zNear - zFar);
            m[11] = -1;
            m[14] = (2 * zNear * zFar) / (zNear - zFar);
            m[15] = -0;
        }
        else {
            m[0] = 2 / (right - left);
            m[5] = 2 / (top - bottom);
            m[10] = -2 / (zFar - zNear);
            m[12] = (left - right) / (right - left);
            m[13] = (bottom - top) / (top - bottom);
            m[14] = (zNear - zFar) / (zFar - zNear);
        }
    }

    void Camera::setPerspective() {
        perspective = true;
    }

    void Camera::setOrthographic() {
        perspective = false;
    }

    float Camera::getFovy() const {
        return fovy;
    }

    float Camera::getAspectRatio() const {
        return aspect;
    }

    float Camera::getZNear() const {
        return zNear;
    }

    float Camera::getZFar() const {
        return zFar;
    }

    void Camera::setFovy(float fovy) {
        this->fovy = fovy;
    }

    void Camera::setAspectRatio(float aspect) {
        this->aspect = aspect;
    }

    void Camera::setZNear(float zNear) {
        this->zNear = zNear;
    }

    void Camera::setZFar(float zFar) {
        this->zFar = zFar;
    }

    void Camera::setBounds(float left, float right, float bottom, float top) {
        this->left = left;
        this->right = right;
        this->bottom = bottom;
        this->top = top;
    }
}