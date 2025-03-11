// camera.cpp
#include "camera.hpp"
#include <stdexcept>
#include <iostream>
#include <algorithm>

Camera::Camera(const glm::vec3& position,
             const glm::vec3& target,
             const glm::vec3& up,
             float fov,
             float aspect_ratio,
             float near_plane,
             float far_plane)
    : _position(position)
    , _world_up(up)
    , _fov(fov)
    , _aspect_ratio(aspect_ratio)
    , _near_plane(near_plane)
    , _far_plane(far_plane)
    , _ortho_left(-10.0f)
    , _ortho_right(10.0f)
    , _ortho_bottom(-10.0f)
    , _ortho_top(10.0f)
    , _camera_type(Type::PERSPECTIVE)
    , _movement_speed(5.0f)
    , _rotation_speed(0.1f)
    , _zoom_speed(1.0f)
    , _yaw(-90.0f) // Default looking along negative z-axis
    , _pitch(0.0f)
{
    set_target(target); // Will calculate front, right and up vectors
}

glm::mat4 Camera::get_view_matrix() const {
    throw std::runtime_error("Camera::get_view_matrix not implemented");
}

glm::mat4 Camera::get_projection_matrix() const {
    throw std::runtime_error("Camera::get_projection_matrix not implemented");
}

void Camera::set_position(const glm::vec3& position) {
    throw std::runtime_error("Camera::set_position not implemented");
}

void Camera::set_target(const glm::vec3& target) {
    throw std::runtime_error("Camera::set_target not implemented");
}

void Camera::move(Direction direction, float distance) {
    throw std::runtime_error("Camera::move not implemented");
}

void Camera::rotate(float xoffset, float yoffset, bool constrain_pitch) {
    throw std::runtime_error("Camera::rotate not implemented");
}

void Camera::zoom(float offset) {
    throw std::runtime_error("Camera::zoom not implemented");
}

void Camera::set_fov(float fov) {
    throw std::runtime_error("Camera::set_fov not implemented");
}

void Camera::set_aspect_ratio(float aspect_ratio) {
    throw std::runtime_error("Camera::set_aspect_ratio not implemented");
}

void Camera::set_clip_planes(float near_plane, float far_plane) {
    throw std::runtime_error("Camera::set_clip_planes not implemented");
}

void Camera::set_camera_type(Type type) {
    throw std::runtime_error("Camera::set_camera_type not implemented");
}

void Camera::set_orthographic_params(float left, float right, float bottom, float top) {
    throw std::runtime_error("Camera::set_orthographic_params not implemented");
}

void Camera::update_camera_vectors() {
    throw std::runtime_error("Camera::update_camera_vectors not implemented");
}
