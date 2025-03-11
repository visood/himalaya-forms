// ui_manager.hpp
#pragma once

#include <string>
#include <vector>
#include <functional>
#include <memory>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "scene_config.hpp"
#include "window.hpp"
#include "scene.hpp"

/*
 * @class UIManager
 * @brief Manages the user interface for the application
 */
class UIManager {
public:
    /*
     * @brief Constructor
     * @param window Reference to the application window
     * @param config Reference to the scene configuration
     * @param scene Reference to the scene
     */
    UIManager(Window& window, Scene& scene, SceneConfig& config);

    /*
     * @brief Destructor
     */
    ~UIManager();

    /*
     * @brief Initializes the UI system
     * @return True if initialization was successful
     */
    bool initialize();

    /*
     * @brief Begins a new UI frame
     */
    void begin_frame();

    /*
     * @brief Renders the UI
     */
    void render();

    /*
     * @brief Ends the current UI frame
     */
    void end_frame();

    /*
     * @brief Sets whether the UI is visible
     * @param visible True to show UI, false to hide
     */
    void set_visible(bool visible) { _visible = visible; }

    /*
     * @brief Toggles UI visibility
     */
    void toggle_visibility() { _visible = !_visible; }

    /*
     * @brief Checks if UI is currently visible
     * @return True if UI is visible
     */
    bool is_visible() const { return _visible; }

    /*
     * @brief Sets the UI scale factor
     * @param scale Scale factor for UI elements
     */
    void set_scale(float scale);

    /*
     * @brief Shows an information message
     * @param title Message title
     * @param message Message content
     * @param auto_close Whether to automatically close the message
     */
    void show_message(const std::string& title, const std::string& message, bool auto_close = true);

    /*
     * @brief Adds a custom UI panel
     * @param name Unique name for the panel
     * @param render_function Function to render the panel content
     */
    void add_custom_panel(const std::string& name, std::function<void()> render_function);

    /*
     * @brief Removes a custom UI panel
     * @param name Name of the panel to remove
     */
    void remove_custom_panel(const std::string& name);

private:
    Window& _window;
    SceneConfig& _config;
    Scene& _scene;

    bool _imgui_initialized;
    bool _visible;
    bool _show_demo_window;
    bool _show_metrics_window;
    bool _show_terrain_panel;
    bool _show_water_panel;
    bool _show_vegetation_panel;
    bool _show_sky_panel;
    bool _show_settings_panel;
    bool _show_camera_panel;
    bool _show_debug_panel;

    struct CustomPanel {
        std::string name;
        bool visible;
        std::function<void()> render_function;
    };

    std::vector<CustomPanel> _custom_panels;

    // UI rendering methods
    void _render_main_menu_bar();
    void _render_terrain_panel();
    void _render_water_panel();
    void _render_vegetation_panel();
    void _render_sky_panel();
    void _render_settings_panel();
    void _render_camera_panel();
    void _render_debug_panel();
    void _render_custom_panels();
    void _render_overlay();

    // Helper methods
    void _setup_style();
    void _handle_keyboard_shortcuts();
};
