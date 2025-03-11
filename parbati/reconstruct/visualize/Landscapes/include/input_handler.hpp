// input_handler.hpp
#pragma once

#include <functional>
#include <unordered_map>
#include <vector>
#include <utility>
//#include <GLFW/glfw3.h>
#include "window.hpp"

/*
 * @class InputHandler
 * @brief Handles user input from keyboard, mouse and other devices
 */
class InputHandler {
public:
    /*
     * @brief Constructor
     * @param window Reference to the application window
     */
    InputHandler(Window& window);

    /*
     * @brief Destructor
     */
    ~InputHandler();

    /*
     * @brief Initializes the input handler
     * @return True if initialization was successful
     */
    bool initialize();

    /*
     * @brief Updates the input state
     * @param delta_time Time elapsed since last update
     *
     * 1. Poll the window for new input events
     * 2. Update internal state tracking (key states, mouse positions)
     * 3. Trigger any registered callbacks for input events
     * 4. Calculate derived values like mouse movement deltas
     * 5. Process any queued input commands
     */
    void update(float delta_time);

    /*
     * @brief Registers a callback for a specific key
     * @param key Key code
     * @param callback Function to call when key is pressed
     */
    void register_key_callback(int key, std::function<void()> callback);

    /*
     * @brief Registers a callback for a mouse button
     * @param button Mouse button code
     * @param callback Function to call when button is pressed
     */
    void register_mouse_button_callback(int button, std::function<void()> callback);

    /*
     * @brief Registers a callback for mouse movement
     * @param callback Function to call when mouse moves
     */
    void register_mouse_move_callback(std::function<void(double, double)> callback);

    /*
     * @brief Registers a callback for mouse scroll
     * @param callback Function to call when mouse wheel scrolls
     */
    void register_mouse_scroll_callback(std::function<void(double)> callback);

    /*
     * @brief Gets the current mouse position
     * @return Pair of x, y coordinates
     */
    std::pair<double, double> get_mouse_position() const;

    /*
     * @brief Gets the mouse movement delta since last update
     * @return Pair of x, y deltas
     */
    std::pair<double, double> get_mouse_delta() const;

    /*
     * @brief Checks if a key is currently pressed
     * @param key Key code to check
     * @return True if the key is pressed
     */
    bool is_key_pressed(int key) const;

    /*
     * @brief Checks if a key was just pressed this frame
     * @param key Key code to check
     * @return True if the key was just pressed
     */
    bool was_key_pressed(int key) const;

    /*
     * @brief Checks if a key was just released this frame
     * @param key Key code to check
     * @return True if the key was just released
     */
    bool was_key_released(int key) const;

    /*
     * @brief Checks if a mouse button is currently pressed
     * @param button Mouse button code to check
     * @return True if the button is pressed
     */
    bool is_mouse_button_pressed(int button) const;

    /*
     * @brief Gets the mouse scroll delta
     * @return Scroll delta value
     */
    double get_scroll_delta() const;

private:
    Window& _window;

    // Keyboard state
    std::unordered_map<int, bool> _current_key_states;
    std::unordered_map<int, bool> _previous_key_states;

    // Mouse state
    std::unordered_map<int, bool> _current_mouse_button_states;
    std::unordered_map<int, bool> _previous_mouse_button_states;
    double _mouse_x, _mouse_y;
    double _previous_mouse_x, _previous_mouse_y;
    double _scroll_delta;

    // Callbacks
    std::unordered_map<int, std::function<void()>> _key_callbacks;
    std::unordered_map<int, std::function<void()>> _mouse_button_callbacks;
    std::vector<std::function<void(double, double)>> _mouse_move_callbacks;
    std::vector<std::function<void(double)>> _mouse_scroll_callbacks;

    // GLFW callback wrappers
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};
