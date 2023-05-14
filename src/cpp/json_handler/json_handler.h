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
#include <string.h>

#include "nlohmann/json.hpp"

using json = nlohmann::json;
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
        /**
         * @brief Construct a new Json Handler object
         * @param filepath
         */
        JsonHandler(const std::string& filepath);

        /**
         * @brief   Obtain JSON object from the class JSON file
         * @return  json object (Dictionary)
         */
        void LoadJson();

        /**
         * @brief
         * @param   json    JSON Param to add to class JSON file
         */
        void WriteOnJson(const json& json);

        /**
         * @brief   Get the current JSON object
         */
        json GetJson();

        /**
         * @brief   Gets back the defined filters of the object.
         *
         * @return  json object containning the filters definition.
         */
        json JsonHandler::GetFilters() const;

        /**
         * @brief   Updates the JSON object
         * @param   json
         * @note    It does NOT regenerate the JSON file.
         */
        void SetJson(const json& json);

        std::string filepath_;
        json json_;

};

/******************************************************************************
 * Functions Definitions
 ******************************************************************************/
/**
 * @brief   Create a Template Json object
 *
 * @param   file_name     Name of template file
 *
 * @todo    Should be created by the config_handler.c
 */
void createTemplateJson(const std::string& file_name);

#endif /* JSON_HANDLER_H_INCLUDED */