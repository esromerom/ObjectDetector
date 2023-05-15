/**
 * @file       objectDetector.c
 * @copyright  Semillero SIRA 2022 -
 *             Universidad de la Salle, Bogota, Colombia
 *
 * @brief      Main file of the object detector algorithm. Based on matlab implementation of
 *             reported algorithm in https://link.springer.com/chapter/10.1007/978-3-030-00353-1_40
 */
#include <iostream>
#include <memory>

#include "open3d/Open3D.h"

#include "open3d/io/PointCloudIO.h"
#include "open3d/3rdparty/Eigen/Eigen"

#include "open3d/utility/FileSystem.h"
#include "open3d/utility/Helper.h"
#include "open3d/utility/Logging.h"
#include "open3d/utility/ProgressReporters.h"

/* Related ObjectDetector's includes */
#include "inputCapture.h"
#include "json_handler/json_handler.h"
#include "nlohmann/json.hpp"
// #include "json_handler.h"

#define _ITERATOR_DEBUG_LEVEL 1
#ifdef _DEBUG
  #undef _DEBUG

#include "open3d/Open3D.h"

#include "open3d/io/PointCloudIO.h"
#include "open3d/3rdparty/Eigen/Eigen"

#include "open3d/utility/FileSystem.h"
#include "open3d/utility/Helper.h"
#include "open3d/utility/Logging.h"
#include "open3d/utility/ProgressReporters.h"
  #define _DEBUG
#else

#include "open3d/Open3D.h"

#include "open3d/io/PointCloudIO.h"
#include "open3d/3rdparty/Eigen/Eigen"

#include "open3d/utility/FileSystem.h"
#include "open3d/utility/Helper.h"
#include "open3d/utility/Logging.h"
#include "open3d/utility/ProgressReporters.h"
#endif

const std::string defaultPcdPath = PCD_PATH;
const std::string defaultConfPath = CONF_PATH;
const std::string defaultOutputPath = OUTPUT_PATH;

// const std::string defaultPcdFile = "test_point_cloud.ply";
// const std::string defaultPcdFile = "test_filter_pc_inliers.pcd";
const std::string defaultPcdFile = "capture1.ply";
const std::string defaultJsonFile = "template.json";

/**
 * @brief   Encapsulates the configuration definitions.
 *
 * @todo    Move this to config handler
 */
namespace config {
    /**
     * @brief   Struct to handle filter configurations
     */
    struct filter {
        std::string name;
        float value;
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(filter, name, value)
    // void to_json(json& j, const filter& f) {
    //     j = json{{"name", f.name},{"value", f.value}};
    // }

    // void from_json(const json& j, filter& f) {
    //     j.at("name").get_to(f.name);
    //     j.at("value").get_to(f.value);
    // }
}

void PrintPointCloud(const open3d::geometry::PointCloud &pointcloud) {
    using namespace open3d;

    bool pointcloud_has_normal = pointcloud.HasNormals();
    utility::LogInfo("Pointcloud has %d points.",
                     (int)pointcloud.points_.size());

    Eigen::Vector3d min_bound = pointcloud.GetMinBound();
    Eigen::Vector3d max_bound = pointcloud.GetMaxBound();
    utility::LogInfo(
            "Bounding box is: ({:.4f}, {:.4f}, {:.4f}) - ({:.4f}, {:.4f}, "
            "{:.4f})",
            min_bound(0), min_bound(1), min_bound(2), max_bound(0),
            max_bound(1), max_bound(2));

    for (size_t i = 0; i < pointcloud.points_.size(); i++) {
        if (pointcloud_has_normal) {
            const Eigen::Vector3d &point = pointcloud.points_[i];
            const Eigen::Vector3d &normal = pointcloud.normals_[i];
            utility::LogInfo("{:.6f} {:.6f} {:.6f} {:.6f} {:.6f} {:.6f}",
                             point(0), point(1), point(2), normal(0), normal(1),
                             normal(2));
        } else {
            const Eigen::Vector3d &point = pointcloud.points_[i];
            utility::LogInfo("{:.6f} {:.6f} {:.6f}", point(0), point(1),
                             point(2));
        }
    }
    utility::LogInfo("End of the list.");
}


/**
 * @brief Called to execute a full calculation chain from a point cloud.
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char *argv[]) {
    using namespace open3d;
    using namespace config;

    /** @todo Template created at init of module Json or Config */
    std::string pathToFile = defaultConfPath + defaultJsonFile;
    createTemplateJson(pathToFile);

    if (argc == 2) {
        std::string option(argv[1]);
        if (option == "--skip-for-unit-test") {
            utility::LogInfo("Skiped for unit test.");
            return 0;
        }
    }

    JsonHandler genConfig(pathToFile);
    genConfig.LoadJson();

    json jFilter = genConfig.GetFilters();

    /* convert from JSON: copy each value from the JSON object */
    config::filter filters[5];

    if(jFilter.is_array() == true) {
        uint8_t idx = 0;
        for (json::iterator it = jFilter.begin(); (it != jFilter.end()) && (idx < 10); ++it) {
            // try
            // {
            filters[idx] = jFilter[idx].get<config::filter>();
            utility::LogInfo("{} - {}", filters[idx].name, filters[idx].value);
            idx++;
            // }
            // catch (json::exception& e)
            // {
            //     std::cout << "deserialization failed: " << e.what() << std::endl;
            // }
        }
    }

    pathToFile = defaultPcdPath + defaultPcdFile;

    /* Import stored capture */
    geometry::PointCloud capturedPcd;
    (void)InputPointCloud((const std::string &) pathToFile, capturedPcd);

    std::shared_ptr<geometry::PointCloud> pointCloud_ptr(
            new geometry::PointCloud);
    *pointCloud_ptr = capturedPcd;
    visualization::DrawGeometries({pointCloud_ptr});

    /* Reduce the amount of data */
    auto downpcd = capturedPcd.VoxelDownSample(filters[0].value);
    visualization::DrawGeometries({downpcd});

    return 0;
}
