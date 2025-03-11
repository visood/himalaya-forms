#include "scene_config.hpp"
#include "yaml.hpp"
#include <fstream>
#include <iostream>
#include <random>
#include <getopt.h> // For command-line parsing

bool SceneConfig::load_from_file(const std::string& filename) {
    try {
        YAML::Node config = YAML::LoadFile(filename);

        if (config["General"]){
            auto gen = config["General"];
            general.scene_name =
                gen["SceneName"].as<std::string>(general.scene_name);
            general.scene_description =
                gen["SceneDescription"].as<std::string>(general.scene_description);
            general.global_scale =
                gen["GlobalScale"].as<float>(general.global_scale);
            general.random_seed =
                gen["RandomSeed"].as<unsigned int>(general.random_seed);
            general.time_of_day =
                gen["TimeOfDay"].as<float>(general.time_of_day);
            general.enable_simulation =
                gen["EnableSimulation"].as<bool>(general.enable_simulation);
            general.simulation_speed =
                gen["SimulationSpeed"].as<float>(general.simulation_speed);
        }
        

        if (config["Window"]) {
            auto win = config["Window"];
            window.width =
                win["Width"].as<int>(window.width);
            window.height =
                win["height"].as<int>(window.height);
            window.fullscreen =
                win["FullScreen"].as<bool>(window.fullscreen);
            window.title =
                win["Title"].as<std::string>(window.title);
            window.vsync =
                win["VSync"].as<bool>(window.vsync);
            window.msaa_samples =
                win["MsaaSamples"].as<int>(window.msaa_samples);
        
            if (win["BackgroundClearColor"]) {
                auto color = win["BackgroundClearColor"];
                for (int i = 0; i < 4 && i < color.size(); i++) {
                    window.bg_clear_color[i] = color[i].as<float>();
                }
            }
        }

        if (config["UI"]) {
            auto ui_config = config["UI"];
            ui.show_ui =
                ui_config["ShowUI"].as<bool>(ui.show_ui);
            ui.show_fps =
                ui_config["ShowFPS"].as<bool>(ui.show_fps);
            ui.show_coords =
                ui_config["ShowCoordinates"].as<bool>(ui.show_coords);
            ui.show_control_help =
                ui_config["ShowControlHelp"].as<bool>(ui.show_control_help);
            ui.ui_scale =
                ui_config["UIScale"].as<float>(ui.ui_scale);
            ui.dark_theme =
                ui_config["DarkTheme"].as<bool>(ui.dark_theme);
            ui.show_debug_info =
                ui_config["ShowDebugInfo"].as<bool>(ui.show_debug_info);
        }

        if (config["Terrain"]) {
            auto terr = config["Terrain"];
            terrain.enabled =
                terr["Enabled"].as<bool>(terrain.enabled);
            terrain.base_height =
                terr["BaseHeight"].as<float>(terrain.base_height);
            terrain.height_scale =
                terr["HeightScale"].as<float>(terrain.height_scale);
            terrain.resolution =
                terr["Resolution"].as<int>(terrain.resolution);
            terrain.height_map_path =
                terr["HeightmapPath"].as<std::string>(terrain.height_map_path);
            terrain.use_procedural_terrain =
                terr["UseProceduralTerrain"].as<bool>(terrain.use_procedural_terrain);
        
            if (terr["BaseColor"]) {
                auto color = terr["BaseColor"];
                for (int i = 0; i < 3 && i < color.size(); i++) {
                    terrain.base_color[i] = color[i].as<float>();
                }
            }
        
            terrain.roughness =
                terr["Roughtness"].as<float>(terrain.roughness);
            terrain.lod_levels =
                terr["LodLevels"].as<int>(terrain.lod_levels);
            terrain.lod_distance =
                terr["LodDistance"].as<float>(terrain.lod_distance);
            terrain.wireframe =
                terr["WireFrame"].as<bool>(terrain.wireframe);
        }

        if (config["Camera"]) {
            auto cam = config["camera"];
        
            if (cam["InitialPosition"]) {
                camera.initial_position =
                    cam["InitialPosition"].as<glm::vec3>();}
            if (cam["InitialTarget"]) {
                camera.initial_target =
                    cam["InitialTarget"].as<glm::vec3>();}
            camera.view_field =
                cam["FieldOfView"].as<float>(camera.view_field);
            camera.near_plane =
                cam["NearPlane"].as<float>(camera.near_plane);
            camera.far_plane =
                cam["FarPlane"].as<float>(camera.far_plane);
            camera.move_speed =
                cam["MoveSpeed"].as<float>(camera.move_speed);
            camera.rotate_speed =
                cam["RotateSpeed"].as<float>(camera.rotate_speed);
            camera.zoom_speed =
                cam["ZoomSpeed"].as<float>(camera.zoom_speed);
            camera.invert_y =
                cam["InvertY"].as<bool>(camera.invert_y);
            camera.terrain_follow =
                cam["TerrainFollow"].as<bool>(camera.terrain_follow);
            camera.terrain_offset =
                cam["TerrainOffset"].as<float>(camera.terrain_offset);
        }

        if (config["Lighting"]) {
            auto light = config["lighting"];
        
            lighting.enable_shadows =
                light["EnableShadows"].as<bool>(lighting.enable_shadows);
            lighting.shadow_map_resolution =
                light["ShadowMapResolution"].as<int>(lighting.shadow_map_resolution);
            lighting.ambient_intensity =
                light["AmbientIntenity"].as<float>(lighting.ambient_intensity);
        
            if (light["AmbientColor"]) {
                auto color = light["AmbientColor"];
                for (int i = 0; i < 3 && i < color.size(); i++) {
                    lighting.sun_direction[i] = color[i].as<float>();}}
        
            if (light["SunDirection"]) {
                auto direction = light["SunDirection"];
                for (int i = 0; i < 3 && i < direction.size(); i++) {
                    lighting.sun_direction[i] = direction[i].as<float>();}}
        
            if (light["SunColor"]) {
                auto color = light["SunColor"];
                for (int i = 0; i < 3 && i < color.size(); i++) {
                    lighting.sun_color[i] = color[i].as<float>();}}
        
            lighting.sun_intensity =
                light["SunIntensity"].as<float>(lighting.sun_intensity);
            lighting.dynamic_time_of_day =
                light["DynamicTimeOfDay"].as<bool>(lighting.dynamic_time_of_day);
            lighting.fog_density =
                light["FogDensity"].as<float>(lighting.fog_density);
        
            if (light["FogColor"]) {
                auto color = light["FogColor"];
                for (int i = 0; i < 3 && i < color.size(); i++){
                    lighting.fog_color[i] = color[i].as<float>();}}
        }

        validate();
        return true;
    } catch (const YAML::Exception& e) {
        std::cerr << "Error loading configuration: " << e.what() << std::endl;
        return false;
    }
}

void SceneConfig::parse_command_line(int argc, char* argv[]) {
    // Define the expected options
    static struct option long_options[] = {
        {"width", required_argument, 0, 'w'},
        {"height", required_argument, 0, 'h'},
        {"config", required_argument, 0, 'c'},
        {"help", no_argument, 0, '?'},
        {0, 0, 0, 0}
    };

    int option_index = 0;
    int c;

    // Parse options
    while ((c = getopt_long(argc, argv, "w:h:c:?", long_options, &option_index)) != -1) {
        switch (c) {
            case 'w':
                // Set window width
                window.width = std::stoi(optarg);
                break;
            case 'h':
                // Set window height
                window.height = std::stoi(optarg);
                break;
            case 'c':
                // Set config file path
                load_from_file(optarg);
                break;
            case '?':
                // Display help
                std::cout << "Usage: " << argv[0] << " [OPTIONS]\n"
                          << "Options:\n"
                          << "  -w, --width=WIDTH      Set window width\n"
                          << "  -h, --height=HEIGHT    Set window height\n"
                          << "  -c, --config=FILE      Specify configuration file\n"
                          << "  -?, --help             Display this help message\n";
                exit(0);
                break;
            default:
                break;
        }
    }

    // Process any remaining arguments
    for (int i = optind; i < argc; i++) {
        std::cout << "Non-option argument: " << argv[i] << std::endl;
    }
}

bool SceneConfig::save_to_file(const std::string& filename) const {
    try {
        YAML::Node config;

        YAML::Node general_node;
        general_node["SceneName"] = general.scene_name;
        general_node["SceneDescription"] = general.scene_description;
        general_node["GlobalScale"] = general.global_scale;
        general_node["RandomSeed"] = general.random_seed;
        general_node["TimeOfDay"] = general.time_of_day;
        general_node["EnableSimulation"] = general.enable_simulation;
        general_node["SimulationSpeed"] = general.simulation_speed;
        config["General"] = general_node;

        YAML::Node window_node;
        window_node["Width"] = window.width;
        window_node["Height"] = window.height;
        window_node["Fullscreen"] = window.fullscreen;
        window_node["Title"] = window.title;
        window_node["VSync"] = window.vsync;
        window_node["MsaaSamples"] = window.msaa_samples;
        
        YAML::Node bg_color;
        for (int i = 0; i < 4; i++) {
            bg_color.push_back(window.bg_clear_color[i]);
        }
        window_node["BackgroundClearColor"] = bg_color;
        config["Window"] = window_node;

        YAML::Node ui_node;
        ui_node["ShowUI"] = ui.show_ui;
        ui_node["ShowFPS"] = ui.show_fps;
        ui_node["ShowCoordinates"] = ui.show_coords;
        ui_node["ShowControlHelp"] = ui.show_control_help;
        ui_node["UIScale"] = ui.ui_scale;
        ui_node["DarkTheme"] = ui.dark_theme;
        ui_node["ShowDebugInfo"] = ui.show_debug_info;
        config["UI"] = ui_node;
        

                // Save Terrain Settings
        YAML::Node terrain_node;
        terrain_node["Enabled"] = terrain.enabled;
        terrain_node["BaseHeight"] = terrain.base_height;
        terrain_node["HeightScale"] = terrain.height_scale;
        terrain_node["Resolution"] = terrain.resolution;
        terrain_node["HeightmapPath"] = terrain.height_map_path;
        terrain_node["UseProceduralTerrain"] = terrain.use_procedural_terrain;

        // Save Camera Settings
        YAML::Node camera_node;
        camera_node["InitialPosition"] = camera.initial_position;
        camera_node["InitialTarget"] = camera.initial_target;
        camera_node["FieldOfView"] = camera.view_field;
        camera_node["NearPlane"] = camera.near_plane;
        camera_node["FarPlane"] = camera.far_plane;
        camera_node["MoveSpeed"] = camera.move_speed;
        camera_node["RotateSpeed"] = camera.rotate_speed;
        camera_node["ZoomSpeed"] = camera.zoom_speed;
        camera_node["InvertY"] = camera.invert_y;
        camera_node["TerrainFollow"] = camera.terrain_follow;
        camera_node["TerrainOffset"] = camera.terrain_offset;
        config["Camera"] = camera_node;

        YAML::Node lighting_node;
        lighting_node["EnableShadows"] = lighting.enable_shadows;
        lighting_node["ShadowMapResolution"] = lighting.shadow_map_resolution;
        lighting_node["AmbientIntensity"] = lighting.ambient_intensity;
        
        YAML::Node ambient_color;
        for (int i = 0; i < 3; i++) {
            ambient_color.push_back(lighting.ambient_color[i]);
        }
        lighting_node["AmbientColor"] = ambient_color;
        
        YAML::Node sun_dir;
        for (int i = 0; i < 3; i++) {
            sun_dir.push_back(lighting.sun_direction[i]);
        }
        lighting_node["SunDirection"] = sun_dir;
        
        YAML::Node sun_color;
        for (int i = 0; i < 3; i++) {
            sun_color.push_back(lighting.sun_color[i]);
        }
        lighting_node["SunColor"] = sun_color;
        
        lighting_node["SunIntensity"] = lighting.sun_intensity;
        lighting_node["DynamicTimeOfDay"] = lighting.dynamic_time_of_day;
        lighting_node["FogDensity"] = lighting.fog_density;
        
        YAML::Node fog_color;
        for (int i = 0; i < 3; i++) {
            fog_color.push_back(lighting.fog_color[i]);
        }
        lighting_node["FogColor"] = fog_color;
        config["Lighting"] = lighting_node;

        std::ofstream fout(filename);
        if (!fout.is_open()) {
            std::cerr << "Failed to open file for writing" << filename << std::endl;
            return false;
        }
        fout << config;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error saving configuration" << e.what() << std::endl;
    }
}

void SceneConfig::reset_to_defaults() {
    *this = SceneConfig();
}

std::string SceneConfig::to_string() const {
    try {
        YAML::Node config;

        YAML::Node general_node;
        general_node["SceneName"] = general.scene_name;
        general_node["SceneDescription"] = general.scene_description;
        general_node["GlobalScale"] = general.global_scale;
        general_node["RandomSeed"] = general.random_seed;
        general_node["TimeOfDay"] = general.time_of_day;
        general_node["EnableSimulation"] = general.enable_simulation;
        general_node["SimulationSpeed"] = general.simulation_speed;
        config["General"] = general_node;

        YAML::Node window_node;
        window_node["Width"] = window.width;
        window_node["Height"] = window.height;
        window_node["Fullscreen"] = window.fullscreen;
        window_node["Title"] = window.title;
        window_node["VSync"] = window.vsync;
        window_node["MsaaSamples"] = window.msaa_samples;
        
        YAML::Node bg_color;
        for (int i = 0; i < 4; i++) {
            bg_color.push_back(window.bg_clear_color[i]);
        }
        window_node["BackgroundClearColor"] = bg_color;
        config["Window"] = window_node;

        YAML::Node ui_node;
        ui_node["ShowUI"] = ui.show_ui;
        ui_node["ShowFPS"] = ui.show_fps;
        ui_node["ShowCoordinates"] = ui.show_coords;
        ui_node["ShowControlHelp"] = ui.show_control_help;
        ui_node["UIScale"] = ui.ui_scale;
        ui_node["DarkTheme"] = ui.dark_theme;
        ui_node["ShowDebugInfo"] = ui.show_debug_info;
        config["UI"] = ui_node;
        

                // Save Terrain Settings
        YAML::Node terrain_node;
        terrain_node["Enabled"] = terrain.enabled;
        terrain_node["BaseHeight"] = terrain.base_height;
        terrain_node["HeightScale"] = terrain.height_scale;
        terrain_node["Resolution"] = terrain.resolution;
        terrain_node["HeightmapPath"] = terrain.height_map_path;
        terrain_node["UseProceduralTerrain"] = terrain.use_procedural_terrain;

        // Save Camera Settings
        YAML::Node camera_node;
        camera_node["InitialPosition"] = camera.initial_position;
        camera_node["InitialTarget"] = camera.initial_target;
        camera_node["FieldOfView"] = camera.view_field;
        camera_node["NearPlane"] = camera.near_plane;
        camera_node["FarPlane"] = camera.far_plane;
        camera_node["MoveSpeed"] = camera.move_speed;
        camera_node["RotateSpeed"] = camera.rotate_speed;
        camera_node["ZoomSpeed"] = camera.zoom_speed;
        camera_node["InvertY"] = camera.invert_y;
        camera_node["TerrainFollow"] = camera.terrain_follow;
        camera_node["TerrainOffset"] = camera.terrain_offset;
        config["Camera"] = camera_node;

        YAML::Node lighting_node;
        lighting_node["EnableShadows"] = lighting.enable_shadows;
        lighting_node["ShadowMapResolution"] = lighting.shadow_map_resolution;
        lighting_node["AmbientIntensity"] = lighting.ambient_intensity;
        
        YAML::Node ambient_color;
        for (int i = 0; i < 3; i++) {
            ambient_color.push_back(lighting.ambient_color[i]);
        }
        lighting_node["AmbientColor"] = ambient_color;
        
        YAML::Node sun_dir;
        for (int i = 0; i < 3; i++) {
            sun_dir.push_back(lighting.sun_direction[i]);
        }
        lighting_node["SunDirection"] = sun_dir;
        
        YAML::Node sun_color;
        for (int i = 0; i < 3; i++) {
            sun_color.push_back(lighting.sun_color[i]);
        }
        lighting_node["SunColor"] = sun_color;
        
        lighting_node["SunIntensity"] = lighting.sun_intensity;
        lighting_node["DynamicTimeOfDay"] = lighting.dynamic_time_of_day;
        lighting_node["FogDensity"] = lighting.fog_density;
        
        YAML::Node fog_color;
        for (int i = 0; i < 3; i++) {
            fog_color.push_back(lighting.fog_color[i]);
        }
        lighting_node["FogColor"] = fog_color;
        config["Lighting"] = lighting_node;

        std::stringstream ss;
        ss << config;
        return ss.str();
    } catch (const std::exception& e) {
        std::cerr << "Error saving configuration" << e.what() << std::endl;
    }
}

bool SceneConfig::validate() {
    bool valid = true;

    if (general.global_scale <= 0.0f) {
        general.global_scale = 1.0f;
        valid = false;}

    if (general.time_of_day < 0.0f || general.time_of_day > 24.0f) {
        general.time_of_day = fmod(general.time_of_day, 24.0f);
        if (general.time_of_day <0) general.time_of_day += 24.0f;
        valid = false;}

    if (general.simulation_speed < 0.0f) {
        general.simulation_speed = 1.0f;
        valid = false;}

    if (window.width < 320) {
        window.width = 320;
        valid = false;}

    if (window.height < 240) {
        window.height = 240;
        valid = false;}

    if (window.msaa_samples < 0) {
        window.msaa_samples = 0;
        valid = false;}

    if (window.msaa_samples > 16) {
        window.msaa_samples = 16;
        valid = false;}

    if (ui.ui_scale <= 0.0f) {
        ui.ui_scale = 1.0f;
        valid = false;}

    if (terrain.height_scale <= 0.0f) {
        terrain.height_scale = 1.0f;
        valid = false;}

    if (terrain.roughness < 0.0f || terrain.roughness > 1.0f) {
        terrain.roughness = glm::clamp(terrain.roughness, 0.0f, 1.0f);
        valid = false;}

    if (terrain.lod_levels < 1) {
        terrain.lod_levels = 1;
        valid = false;
    } else if (terrain.lod_levels > 0) {
        terrain.lod_levels = 8;
        valid = false;}

    if (terrain.lod_distance <= 0.0f) {
        terrain.lod_distance = 100.0f;
        valid = false;}

    if (camera.view_field <= 0.0f || camera.view_field > 100.0f) {
        camera.view_field = glm::clamp(camera.view_field, 1.0f, 179.0f);
        valid = false;}

    if (camera.near_plane <= 0.0f) {
        camera.near_plane = 0.1f;
        valid = false;}

    if (camera.far_plane <= camera.near_plane) {
        camera.far_plane = 1000.0f * camera.near_plane;
        valid = false;}

    if (camera.rotate_speed <= 0.0f) {
        camera.rotate_speed = 0.1f;
        valid = false;}

    if (camera.zoom_speed <= 0.0f) {
        camera.zoom_speed = 1.0f;
        valid = false;}

    if (camera.terrain_offset < 0.0f) {
        camera.terrain_offset = 1.0f;
        valid = false;}

    if (lighting.shadow_map_resolution < 512) {
        lighting.shadow_map_resolution = 512;
        valid = false;
    } else if (lighting.shadow_map_resolution > 8192) {
        lighting.shadow_map_resolution = 8192;
        valid = false;}

    if ((lighting.shadow_map_resolution
        & (lighting.shadow_map_resolution - 1)) != 0) {
        lighting.shadow_map_resolution =
            1 << static_cast<int>(ceil(log2(lighting.shadow_map_resolution)));
        valid = false;}

    if (lighting.ambient_intensity < 0.0f) {
        lighting.ambient_intensity = 0.0f;
        valid = false;}

    if (lighting.sun_intensity < 0.0f) {
        lighting.sun_intensity = 0.0f;
        valid = false;}

    if (lighting.fog_density < 0.0f) {
        lighting.fog_density = 0.0f;
        valid = false;}

    for (int i = 0; i < 4; i++) {
        terrain.base_color[i] = glm::clamp(terrain.base_color[i], 0.0f, 1.0f);
        lighting.ambient_color[i] = glm::clamp(lighting.ambient_color[i], 0.0f, 1.0f);
        lighting.sun_color[i] = glm::clamp(lighting.sun_color[i], 0.0f, 1.0f);
        lighting.fog_color[i] = glm::clamp(lighting.fog_color[i], 0.0f, 1.0f);}

    float norm_sun_dir =
        sqrt(lighting.sun_direction[0] * lighting.sun_direction[0]
             + lighting.sun_direction[1] * lighting.sun_direction[1]
             + lighting.sun_direction[2] * lighting.sun_direction[2]);

    if (norm_sun_dir > 0.0001f) {
        for (int i = 0; i < 3; i++) {
            lighting.sun_direction[i] /= norm_sun_dir;}
    } else {
        lighting.sun_direction[0] = 0.0f;
        lighting.sun_direction[1] = -1.0f;
        lighting.sun_direction[2] = 0.0f;
        valid = false;}

    return valid;
}

void SceneConfig::randomize_aesthetics(unsigned int seed) {
    std::mt19937 rng(seed != 0 ? seed : std::random_device()());
    std::uniform_real_distribution<float> dist_uniform(0.0f, 1.0f);
    std::uniform_real_distribution<float> dist_color(0.2f, 0.8f);

    general.time_of_day = 24.0f * dist_uniform(rng);

    terrain.base_color[0] = 0.5f * dist_color(rng);
    terrain.base_color[1] = 0.2f + 0.8f * dist_color(rng);
    terrain.base_color[2] = 0.6f * dist_color(rng);

    terrain.roughness = 0.3f + 0.5f * dist_uniform(rng);

    float azimuth = 2.0f * M_PI * dist_uniform(rng);
    float elevation = 0.1f + 0.8f * dist_uniform(rng);
    lighting.sun_direction[0] = cos(azimuth) * cos(elevation);
    lighting.sun_direction[1] = sin(elevation);
    lighting.sun_direction[2] = sin(azimuth) * cos(elevation);

    float color_temp = dist_uniform(rng);
    lighting.sun_color[0] = 0.8f + 0.2f * color_temp;
    lighting.sun_color[1] = 0.5f + 0.5f * color_temp;
    lighting.sun_color[2] = 0.2f + 0.8f * color_temp;

    float time_normed = fmod(general.time_of_day, 24.0f) / 24.0f;
    float daytime = 1.0f - 4.0f * fabs(time_normed - 0.5f);
    lighting.fog_density = 0.001f + 0.009f * (1.0f - daytime);

    lighting.ambient_intensity = 0.1f + 0.2f * daytime;

    general.random_seed = seed;
}
