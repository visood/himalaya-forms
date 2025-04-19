#include "core/scene_config.hpp"
#include "templates/yaml.hpp"
#include <fstream>
#include <iostream>
#include <random>
#include <getopt.h> // For command-line parsing

bool SceneConfig::load_from_file(const std::string& filename) {
    try {
        YAML::Node config = YAML::LoadFile(filename);

        if (config["Run"]){
            auto gen = config["Run"];
            run.scene_name =
                gen["SceneName"].as<std::string>(run.scene_name);
            run.scene_description =
                gen["SceneDescription"].as<std::string>(run.scene_description);
            run.global_scale =
                gen["GlobalScale"].as<float>(run.global_scale);
            run.random_seed =
                gen["RandomSeed"].as<unsigned int>(run.random_seed);
            run.time_of_day =
                gen["TimeOfDay"].as<float>(run.time_of_day);
            run.enable_simulation =
                gen["EnableSimulation"].as<bool>(run.enable_simulation);
            run.simulation_speed =
                gen["SimulationSpeed"].as<float>(run.simulation_speed);
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

        return validate();
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

        YAML::Node run_node;
        run_node["SceneName"] = run.scene_name;
        run_node["SceneDescription"] = run.scene_description;
        run_node["GlobalScale"] = run.global_scale;
        run_node["RandomSeed"] = run.random_seed;
        run_node["TimeOfDay"] = run.time_of_day;
        run_node["EnableSimulation"] = run.enable_simulation;
        run_node["SimulationSpeed"] = run.simulation_speed;
        config["Run"] = run_node;

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

        YAML::Node run_node;
        run_node["SceneName"] = run.scene_name;
        run_node["SceneDescription"] = run.scene_description;
        run_node["GlobalScale"] = run.global_scale;
        run_node["RandomSeed"] = run.random_seed;
        run_node["TimeOfDay"] = run.time_of_day;
        run_node["EnableSimulation"] = run.enable_simulation;
        run_node["SimulationSpeed"] = run.simulation_speed;
        config["Run"] = run_node;;

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
        config["Window"] = window_node;;

        std::stringstream ss;
        ss << config;
        return ss.str();
    } catch (const std::exception& e) {
        std::cerr << "Error saving configuration" << e.what() << std::endl;
    }
}

bool SceneConfig::validate() {
    bool valid = true;

    if (run.global_scale <= 0.0f) {
        run.global_scale = 1.0f;
        valid = false;}

    if (run.time_of_day < 0.0f || run.time_of_day > 24.0f) {
        run.time_of_day = fmod(run.time_of_day, 24.0f);
        if (run.time_of_day <0) run.time_of_day += 24.0f;
        valid = false;}

    if (run.simulation_speed < 0.0f) {
        run.simulation_speed = 1.0f;
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

    return valid;
}

void SceneConfig::randomize_aesthetics(unsigned int seed) {
    std::mt19937 rng(seed != 0 ? seed : std::random_device()());
    std::uniform_real_distribution<float> dist_uniform(0.0f, 1.0f);
    std::uniform_real_distribution<float> dist_color(0.2f, 0.8f);

    run.time_of_day = 24.0f * dist_uniform(rng);

    run.random_seed = seed;
}
