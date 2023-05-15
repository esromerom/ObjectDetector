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

#include "open3d/utility/FileSystem.h"
#include "open3d/utility/Helper.h"
#include "open3d/utility/Logging.h"
#include "open3d/utility/ProgressReporters.h"

#include "json_handler.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;
using namespace open3d;
/******************************************************************************
 * Constants and Macros
 ******************************************************************************/

/******************************************************************************
 * Types declarations
 ******************************************************************************/

/******************************************************************************
 * Static Functions Declarations
 ******************************************************************************/
static void loadJsonFile(std::string filepath, json * jObject);

/******************************************************************************
 * Global Variables Declarations
 ******************************************************************************/

/******************************************************************************
 * Module Global Variables
 ******************************************************************************/

/******************************************************************************
 * Class Functions Definition
 ******************************************************************************/
/* Constructor */
JsonHandler::JsonHandler(const std::string & filepath) : filepath_(filepath) {
    this->json_ = json::object();
}

void JsonHandler::LoadJson() {
    loadJsonFile(this->filepath_, &this->json_);
}

json JsonHandler::GetJson(){
    return this->json_;
}

json JsonHandler::GetFilters() const {
    assert(this->json_.is_null() == false);
    json jTemp;

    if (this->json_.contains("features") == true) {
        jTemp = this->json_["features"];
        /* Simple JSON definitions - Not an JSON array */
        if (jTemp.contains("filters") == true) {
            return jTemp["filters"];
        }
        /* Is it an array? */
        else if (jTemp.is_array() == true) {
            for (json::iterator it = jTemp.begin(); it != jTemp.end(); ++it) {
                if ((*it).contains("filters") == true) {
                    return (*it)["filters"];
                }
            }
        }
        else { /* Nothing at all found */
            utility::LogError("None filter found");
        }
    }
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
 * Functions Definitions
 ******************************************************************************/
void createTemplateJson(const std::string& file_name) {
    json jTemplate;
    json jFilters;

    /* By default should be null */
    jTemplate["input"] =  {{"name", "capture1.ply"},{"type", "file"}};

    /* In order to allow graphic interface or not. */
    jTemplate["interface"] = "false";

    /* Listing supported features  */
    jTemplate["features"] = json::array({ });

    /* Listing supported Filters */
    jFilters["filters"] = json::array({ });
    jFilters["filters"].push_back({{"name", "voxel"},{"value", 0.1}});
    jFilters["filters"].push_back({{"name", "denoise"},{"value", 0.2}});

    jTemplate["features"].push_back(jFilters);

    std::ofstream file(file_name);
    if (file.is_open()) {
        file << std::setw(2) << jTemplate;
    } else {
        throw std::runtime_error("Failed to open file: " + file_name);
    }
}
/******************************************************************************
 * Private functions definitions
 ******************************************************************************/
static void loadJsonFile(std::string filepath, json* jObject) {
    json jTemp;
    std::ifstream file(filepath);
    file >> jTemp;

    if (jTemp.is_null() == false) {
        // jObject = json::parse(jObject);
        utility::LogInfo("Successfully read {}", filepath);
        utility::LogInfo("{}", jTemp);
        *jObject = jTemp;
    } else {
        throw std::runtime_error("Failed to open file: " + filepath);
    }
}