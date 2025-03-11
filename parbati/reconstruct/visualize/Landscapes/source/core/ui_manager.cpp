// ui_manager.cpp
#include "ui_manager.hpp"
#include <stdexcept>
#include <iostream>

UIManager::UIManager(Window& window, Scene& scene, SceneConfig& config)
    : _window(window)
    , _config(config)
    , _scene(scene)
    , _visible(true)
    , _show_demo_window(false)
    , _show_metrics_window(false)
    , _show_terrain_panel(true)
    , _show_water_panel(true)
    , _show_vegetation_panel(true)
    , _show_sky_panel(true)
    , _show_settings_panel(false)
    , _show_camera_panel(false)
    , _show_debug_panel(false)
{
    // Stub implementation
    _imgui_initialized = false;
}

UIManager::~UIManager() {
    // Cleanup ImGui only if it's initialization was successful
    if (_imgui_initialized) {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
}

bool UIManager::initialize() {
    // Create ImGui context
    try{
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        // Setup ImGui IO configuration
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= // Enable keyboard controls
            ImGuiConfigFlags_NavEnableKeyboard;

        // Check if docking is available in this version
        // Docking might need to be explicitly enabled in some ImGui versions
        #ifdef ImGuiConfigFlags_DockingEnable  // Enable docking if available
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        #endif

        // Setup style
        _setup_style();

        // Setup platform/renderer backends
        if (!_window.get_native_handle()) {
            std::cerr << "Window handle is null, cannot initialize ImGui" << std::endl;
            return false;
        }

        bool glfw_init_success =
            ImGui_ImplGlfw_InitForOpenGL(_window.get_native_handle(), true);
        bool opengl_init_success = // Use appropriate GLSL version
            ImGui_ImplOpenGL3_Init("#version 450");

        if (!glfw_init_success || !opengl_init_success) {
            std::cerr << "Failed to initialize ImGui backends" << std::endl;
            return false;
        }

        _imgui_initialized = true;

        return true;
    } catch (const std::exception& e) {
        std::cerr << "Exception during ImGui initialization: "
                  << e.what() << std::endl;
        return false;
    }
}

void UIManager::begin_frame() {
    throw std::runtime_error("UIManager::begin_frame not implemented");
}

void UIManager::render() {
    throw std::runtime_error("UIManager::render not implemented");
}

void UIManager::end_frame() {
    throw std::runtime_error("UIManager::end_frame not implemented");
}

void UIManager::set_scale(float scale) {
    throw std::runtime_error("UIManager::set_scale not implemented");
}

void UIManager::show_message(const std::string& title, const std::string& message, bool auto_close) {
    throw std::runtime_error("UIManager::show_message not implemented");
}

void UIManager::add_custom_panel(const std::string& name, std::function<void()> render_function) {
    throw std::runtime_error("UIManager::add_custom_panel not implemented");
}

void UIManager::remove_custom_panel(const std::string& name) {
    throw std::runtime_error("UIManager::remove_custom_panel not implemented");
}

void UIManager::_render_main_menu_bar() {
    throw std::runtime_error("UIManager::_render_main_menu_bar not implemented");
}

void UIManager::_render_terrain_panel() {
    throw std::runtime_error("UIManager::_render_terrain_panel not implemented");
}

void UIManager::_render_water_panel() {
    throw std::runtime_error("UIManager::_render_water_panel not implemented");
}

void UIManager::_render_vegetation_panel() {
    throw std::runtime_error("UIManager::_render_vegetation_panel not implemented");
}

void UIManager::_render_sky_panel() {
    throw std::runtime_error("UIManager::_render_sky_panel not implemented");
}

void UIManager::_render_settings_panel() {
    throw std::runtime_error("UIManager::_render_settings_panel not implemented");
}

void UIManager::_render_camera_panel() {
    throw std::runtime_error("UIManager::_render_camera_panel not implemented");
}

void UIManager::_render_debug_panel() {
    throw std::runtime_error("UIManager::_render_debug_panel not implemented");
}

void UIManager::_render_custom_panels() {
    throw std::runtime_error("UIManager::_render_custom_panels not implemented");
}

void UIManager::_render_overlay() {
    throw std::runtime_error("UIManager::_render_overlay not implemented");
}

void UIManager::_handle_keyboard_shortcuts() {
    throw std::runtime_error("UIManager::_handle_keyboard_shortcuts not implemented");
}

void UIManager::_setup_style() {
    //Choose between light and dark themes
    if (_config.ui.dark_theme) {
        ImGui::StyleColorsDark();
    } else {
        ImGui::StyleColorsLight();
    }

    // Get style to customize
    ImGuiStyle& style = ImGui::GetStyle();

    // Customize colors
    ImVec4* colors = style.Colors;

        if (_config.ui.dark_theme) {
        // Dark theme inspired by mountains at night/dusk
        colors[ImGuiCol_WindowBg]       = ImVec4(0.06f, 0.06f, 0.10f, 0.94f); // Darker blue-gray
        colors[ImGuiCol_Header]         = ImVec4(0.20f, 0.22f, 0.27f, 0.55f); // Slate
        colors[ImGuiCol_HeaderHovered]  = ImVec4(0.26f, 0.30f, 0.40f, 0.80f);
        colors[ImGuiCol_HeaderActive]   = ImVec4(0.24f, 0.24f, 0.32f, 1.00f);
        colors[ImGuiCol_TitleBg]        = ImVec4(0.12f, 0.12f, 0.18f, 1.00f); // Darker title bars
        colors[ImGuiCol_TitleBgActive]  = ImVec4(0.16f, 0.16f, 0.24f, 1.00f);
        colors[ImGuiCol_Button]         = ImVec4(0.20f, 0.25f, 0.37f, 0.60f); // Indigo-ish buttons
        colors[ImGuiCol_ButtonHovered]  = ImVec4(0.33f, 0.38f, 0.47f, 1.00f);
        colors[ImGuiCol_ButtonActive]   = ImVec4(0.27f, 0.32f, 0.52f, 1.00f);
        colors[ImGuiCol_FrameBg]        = ImVec4(0.15f, 0.15f, 0.22f, 0.54f); // Frame backgrounds
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.26f, 0.40f);
        colors[ImGuiCol_FrameBgActive]  = ImVec4(0.26f, 0.26f, 0.35f, 0.67f);
        colors[ImGuiCol_Tab]            = ImVec4(0.17f, 0.17f, 0.24f, 0.86f);
        colors[ImGuiCol_TabHovered]     = ImVec4(0.29f, 0.30f, 0.39f, 0.80f);
        colors[ImGuiCol_TabActive]      = ImVec4(0.22f, 0.23f, 0.35f, 1.00f);
    } else {
        // Light theme inspired by snow-capped mountains
        colors[ImGuiCol_WindowBg]       = ImVec4(0.95f, 0.95f, 0.97f, 0.94f); // Off-white for windows
        colors[ImGuiCol_Header]         = ImVec4(0.80f, 0.84f, 0.90f, 0.55f); // Light blue-gray
        colors[ImGuiCol_HeaderHovered]  = ImVec4 (0.85f, 0.88f, 0.92f, 0.80f);
        colors[ImGuiCol_HeaderActive]   = ImVec4(0.78f, 0.83f, 0.91f, 1.00f);
        colors[ImGuiCol_TitleBg]        = ImVec4(0.76f, 0.82f, 0.90f, 1.00f); // Light blue title bars
        colors[ImGuiCol_TitleBgActive]  = ImVec4(0.82f, 0.86f, 0.93f, 1.00f);
        colors[ImGuiCol_Button]         = ImVec4(0.74f, 0.78f, 0.85f, 0.60f); // Soft blue buttons
        colors[ImGuiCol_ButtonHovered]  = ImVec4(0.67f, 0.75f, 0.87f, 1.00f);
        colors[ImGuiCol_ButtonActive]   = ImVec4(0.62f, 0.70f, 0.82f, 1.00f);
        colors[ImGuiCol_FrameBg]        = ImVec4(0.86f, 0.88f, 0.92f, 0.54f);// Light frame backgrounds
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.90f, 0.92f, 0.95f, 0.40f);
        colors[ImGuiCol_FrameBgActive]  = ImVec4(0.80f, 0.85f, 0.90f, 0.67f);
        colors[ImGuiCol_Tab]            = ImVec4(0.78f, 0.82f, 0.88f, 0.86f);
        colors[ImGuiCol_TabHovered]     = ImVec4(0.86f, 0.90f, 0.95f, 0.80f);
        colors[ImGuiCol_TabActive]      = ImVec4(0.82f, 0.86f, 0.93f, 1.00f);
    }

    // Accent color for sliders, checkboxes, etc.
    colors[ImGuiCol_SliderGrab]       = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_CheckMark]        = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);

    // UI element styling
    style.FrameRounding     = 4.0f;      // Rounded corners on frames
    style.GrabRounding      = 4.0f;       // Rounded slider grabs
    style.WindowRounding    = 6.0f;     // Rounded window corners
    style.ChildRounding     = 4.0f;      // Rounded child windows
    style.PopupRounding     = 4.0f;      // Rounded popups
    style.ScrollbarRounding = 4.0f;  // Rounded scrollbars
    style.TabRounding       = 4.0f;        // Rounded tabs

    // Scale UI based on configuration
    style.ScaleAllSizes(_config.ui.ui_scale);

    // Adjust spacing for better readability
    style.ItemSpacing =
        ImVec2(8.0f * _config.ui.ui_scale, 4.0f * _config.ui.ui_scale);
    style.ItemInnerSpacing =
        ImVec2(4.0f * _config.ui.ui_scale, 4.0f * _config.ui.ui_scale);

    // Window padding
    style.WindowPadding = ImVec2(10.0f, 10.0f);

    // Alpha settings
    style.Alpha = 1.0f;             // Global alpha
    style.DisabledAlpha = 0.60f;    // Alpha for disabled elements

    // Set various display options
    style.AntiAliasedLines = true;
    style.AntiAliasedFill = true;
    style.CurveTessellationTol = 1.25f;

    // Indent for hierarchical GUI elements
    style.IndentSpacing = 21.0f * _config.ui.ui_scale;

    // Frame padding
    style.FramePadding =
        ImVec2(6.0f * _config.ui.ui_scale, 3.0f * _config.ui.ui_scale);

//    throw std::runtime_error("UIManager::_setup_style not implemented");
}
