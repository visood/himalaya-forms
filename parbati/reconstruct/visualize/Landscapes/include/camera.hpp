// camera.hpp
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/*
 * @class Camera
 * @brief Handles camera movement and view/projection matrices
 */
class Camera {
public:
    /*
     * @brief Camera movement directions
     */
    enum class Direction {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    /*
     * @brief Camera types
     */
    enum class Type {
        PERSPECTIVE,
        ORTHOGRAPHIC
    };

    /*
     * @brief Constructor with position and orientation
     * @param position Initial camera position
     * @param target Point the camera is looking at
     * @param up World up vector
     * @param fov Field of view in degrees
     * @param aspect_ratio Aspect ratio (width/height)
     * @param near_plane Near clipping plane
     * @param far_plane Far clipping plane
     */
    Camera(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 3.0f),
           const glm::vec3& target = glm::vec3(0.0f, 0.0f, 0.0f),
           const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f),
           float fov = 45.0f,
           float aspect_ratio = 1.777f,
           float near_plane = 0.1f,
           float far_plane = 1000.0f);

    /*
     * @brief Gets the view matrix
     * @return 4x4 view matrix
     */
    glm::mat4 get_view_matrix() const;

    /*
     * @brief Gets the projection matrix
     * @return 4x4 projection matrix
     */
    glm::mat4 get_projection_matrix() const;

    /*
     * @brief Gets the camera position
     * @return Camera position vector
     */
    glm::vec3 get_position() const { return _position; }

    /*
     * @brief Gets the camera front direction
     * @return Camera front vector
     */
    glm::vec3 get_front() const { return _front; }

    /*
     * @brief Gets the camera up vector
     * @return Camera up vector
     */
    glm::vec3 get_up() const { return _up; }

    /*
     * @brief Gets the camera right vector
     * @return Camera right vector
     */
    glm::vec3 get_right() const { return _right; }

    /*
     * @brief Sets the camera position
     * @param position New camera position
     */
    void set_position(const glm::vec3& position);

    /*
     * @brief Sets the camera target
     * @param target Point to look at
     */
    void set_target(const glm::vec3& target);

    /*
     * @brief Moves the camera in the specified direction
     * @param direction Movement direction
     * @param distance Distance to move
     */
    void move(Direction direction, float distance);

    /*
     * @brief Rotates the camera based on mouse movement
     * @param xoffset Mouse X offset
     * @param yoffset Mouse Y offset
     * @param constrain_pitch Whether to constrain the pitch
     */
    void rotate(float xoffset, float yoffset, bool constrain_pitch = true);

    /*
     * @brief Zooms the camera by adjusting FOV
     * @param offset Zoom offset
     */
    void zoom(float offset);

    /*
     * @brief Sets the field of view
     * @param fov New field of view in degrees
     */
    void set_fov(float fov);

    /*
     * @brief Sets the aspect ratio
     * @param aspect_ratio New aspect ratio
     */
    void set_aspect_ratio(float aspect_ratio);

    /*
     * @brief Sets the near and far clipping planes
     * @param near_plane Near clipping plane
     * @param far_plane Far clipping plane
     */
    void set_clip_planes(float near_plane, float far_plane);

    /*
     * @brief Sets the camera type
     * @param type Camera type (perspective or orthographic)
     */
    void set_camera_type(Type type);

    /*
     * @brief Sets orthographic projection parameters
     * @param left Left plane
     * @param right Right plane
     * @param bottom Bottom plane
     * @param top Top plane
     */
    void set_orthographic_params(float left, float right, float bottom, float top);

    /*
     * @brief Updates the camera's internal vectors
     */
    void update_camera_vectors();

    /*
     * @brief Gets the camera's field of view
     * @return Field of view in degrees
     */
    float get_fov() const { return _fov; }

    /*
     * @brief Gets the camera's yaw angle
     * @return Yaw angle in degrees
     */
    float get_yaw() const { return _yaw; }

    /*
     * @brief Gets the camera's pitch angle
     * @return Pitch angle in degrees
     */
    float get_pitch() const { return _pitch; }

private:
    // Camera position and orientation
    glm::vec3 _position;
    glm::vec3 _front;
    glm::vec3 _up;
    glm::vec3 _right;
    glm::vec3 _world_up;

    // Euler angles
    float _yaw;
    float _pitch;

    // Camera options
    float _fov;
    float _aspect_ratio;
    float _near_plane;
    float _far_plane;

    // For orthographic projection
    float _ortho_left;
    float _ortho_right;
    float _ortho_bottom;
    float _ortho_top;

    // Camera type
    Type _camera_type;

    // Movement settings
    float _movement_speed;
    float _rotation_speed;
    float _zoom_speed;
};
