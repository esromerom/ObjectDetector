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
#include <stdio.h>
#include <string.h>
#include <fstream>

#include "json_handler.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;
/******************************************************************************
 * Constants and Macros
 ******************************************************************************/
const std::string & defaultJsonFile = "template.json";
const std::string & defaultJsonPath = "./";
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
JsonHandler::JsonHandler(const std::string & filepath) : filepath_(filepath) {
    json_ = json::object();
}
 

void JsonHandler::LoadJson() {
    std::ifstream file(filepath_);

    if (file.is_open()) {
        file >> json_;
    } else {
        throw std::runtime_error("Failed to open file: " + filepath_);
    }
    std::ifstream ifs;
}

json JsonHandler::GetJson() const {
        return json_;
    }

void JsonHandler::SetJson(const json& jsonOb) {
        json_.clear();
        json_ = jsonOb;
    }

void JsonHandler::WriteOnJson(const json& jsonOb) {
    SetJson(jsonOb);
    std::ofstream file(filepath_);
    file << json_.dump(4);
}

/******************************************************************************
 * Module Global Variables
 ******************************************************************************/

/******************************************************************************
 * Class Definition
 ******************************************************************************/

/******************************************************************************
 * Functions Definitions
 ******************************************************************************/
void createTemplateJson(const std::string& file_name) {
    json jsonOb;

    /* Populate the JSON object with template data */
    jsonOb["param1"] = 0.0;
    jsonOb["param2"] = "string value";
    jsonOb["param3"] = false;

    /* Write the JSON object to a file */
    std::ofstream file(file_name);
    if (file.is_open()) {
        file << jsonOb;
    } else {
        throw std::runtime_error("Failed to open file: " + file_name);
    }
}
/******************************************************************************
 * Private functions definitions
 ******************************************************************************/