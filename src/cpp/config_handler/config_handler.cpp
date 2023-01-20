/******************************************************************************
 * @file       configHandler.cpp
 * @copyright  Semillero SIRA 2022 -
 *             Universidad de la Salle, Bogota, Colombia
 *
 * @brief      Class definition file to handle the settings that govern the program
 ******************************************************************************/

/******************************************************************************
 * Included Files
 ******************************************************************************/

#include "config_handler.h"

/******************************************************************************
 * Constants and Macros
 ******************************************************************************/

/******************************************************************************
 * Types declarations
 ******************************************************************************/

/******************************************************************************
 * Static Functions Declarations
 ******************************************************************************/

/******************************************************************************
 * Global Variables Declarations
 ******************************************************************************/

/******************************************************************************
 * Module Global Variables
 ******************************************************************************/

/******************************************************************************
 * Class Definition
 ******************************************************************************/

/******************************************************************************
 * Functions Definitions
 ******************************************************************************/

ConfigHandler::ConfigHandler() {}

ConfigHandler::~ConfigHandler() {}

void ConfigHandler::loadConfig(const std::string& file_name) {
    std::ifstream file(file_name);
    if (file.is_open()) {
        file >> json_;
        noise_filter_config_.mean_k = json_["noise_filter"]["mean_k"];
        noise_filter_config_.std_dev_mul_thresh = json_["noise_filter"]["std_dev_mul_thresh"];
    } else {
        throw std::runtime_error("Failed to open file: " + file_name);
    }
}

NoiseFilterConfig ConfigHandler::getNoiseFilterConfig() {
    return noise_filter_config_;
}

void ConfigHandler::setNoiseFilterConfig(const NoiseFilterConfig& config) {
    noise_filter_config_ = config;
    json_["noise_filter"]["mean_k"] = config.mean_k;
    json_["noise_filter"]["std_dev_mul_thresh"] = config.std_dev_mul_thresh;
}
private: {
    /* Default config path config file. */
    std::string config_file_;
    JsonHandler json_handler_;
    double threshold_;
    int min_cluster_size_;
    int max_cluster_size_;
    //...
};

/******************************************************************************
 * Private functions definitions
 ******************************************************************************/
