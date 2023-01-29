/******************************************************************************
 * @file        jsonHandler.cpp
 * @copyright   Semillero SIRA 2022 -
 *              Universidad de la Salle, Bogota, Colombia
 *
 * @brief       Class definition file to handle the json files parser that allows
 *              store and modify the parameters of the program on the fly without
 *              With out modify any code and further regeneration of the executable.
 ******************************************************************************/

/******************************************************************************
 * Included Files
 ******************************************************************************/
#include "json_handler.h"

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
/* Constructor */
JsonHandler::JsonHandler(const std::string& filepath) : filepath_(filepath) {}


nlohmann::json JsonHandler::readJson() {
    std::ifstream file(filepath_);
    nlohmann::json json;
    file >> json;
    return json;
}


void JsonHandler::writeJson(const nlohmann::json& json) {
    std::ofstream file(filepath_);
    file << json.dump(4);
}

/******************************************************************************
 * Module Global Variables
 ******************************************************************************/

/******************************************************************************
 * Class Definition
 ******************************************************************************/
class JsonHandler {
public:
    void loadJson(const std::string& file_name) {
        std::ifstream file(file_name);
        if (file.is_open()) {
            file >> json_;
        } else {
            throw std::runtime_error("Failed to open file: " + file_name);
        }
    }
    nlohmann::json getJson() const {
        return json_;
    }
    void setJson(const nlohmann::json& json) {
        json_ = json;
    }

private:
    nlohmann::json json_;
};

/******************************************************************************
 * Functions Definitions
 ******************************************************************************/

/******************************************************************************
 * Private functions definitions
 ******************************************************************************/