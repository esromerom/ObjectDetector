/******************************************************************************
 * @file       configHandler.cpp
 * @copyright  Semillero SIRA 2022 -
 *             Universidad de la Salle, Bogota, Colombia
 *
 * @brief      Class definition file to handle the settings that govern the program
 ******************************************************************************/

#ifndef CONFIG_HANDLER_H_INCLUDED
#define CONFIG_HANDLER_H_INCLUDED

/******************************************************************************
 * Included Files
 ******************************************************************************/

#include <string>

/**
 * @struct  NoiseFilterConfig
 * @brief   Stores the parameters to be used for Noise filtering, including
 *          the kind of filter to use.
 */
struct NoiseFilterConfig {
    double mean_k;
    double std_dev_mul_thresh;
};

/******************************************************************************
 * Public Classes
 ******************************************************************************/
/**
 * @class   ConfigHandler
 * @brief   Handles the configuration object. I may allow to have several instances of
 *          configuration on one execution. Even to modify or reload config from
 *          JSON files.
 * @note    Needs JsonHandler class.
 */
class ConfigHandler {
public:
    ConfigHandler();
    ~ConfigHandler();
    void loadConfig(const std::string& file_name);
    NoiseFilterConfig getNoiseFilterConfig();
    void setNoiseFilterConfig(const NoiseFilterConfig& config);

private:
    nlohmann::json json_;
    NoiseFilterConfig noise_filter_config_;
};

#endif /* CONFIG_HANDLER_H_INCLUDED */