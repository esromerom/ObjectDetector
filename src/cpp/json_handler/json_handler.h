/******************************************************************************
 * @file        jsonHandler.cpp
 * @copyright   Semillero SIRA 2022 -
 *              Universidad de la Salle, Bogota, Colombia
 *
 * @brief       Header for the Class to handle json files. 
 ******************************************************************************/

#ifndef JSON_HANDLER_H_INCLUDED
#define JSON_HANDLER_H_INCLUDED

/******************************************************************************
 * Included Files
 ******************************************************************************/

/******************************************************************************
 * Constants and Macros
 ******************************************************************************/

/******************************************************************************
 * Types declarations
 ******************************************************************************/

/******************************************************************************
 * Global Variables Declarations
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

#endif /* JSON_HANDLER_H_INCLUDED */