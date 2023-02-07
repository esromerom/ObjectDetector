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
// #include "json_handler.h"

const std::string defaultPcdPath = PCD_PATH;
const std::string defaultConfPath = CONF_PATH;
const std::string defaultOutputPath = OUTPUT_PATH;

// const std::string filepath = "test_point_cloud.ply";
// const std::string filepath = "test_filter_pc_inliers.pcd";
const std::string defaultPcdFile = "capture1.ply";
const std::string defaultJsonFile = "template.json";

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
    std::string pathFile = defaultConfPath + defaultJsonFile;
    createTemplateJson(pathFile);

    if (argc == 2) {
        std::string option(argv[1]);
        if (option == "--skip-for-unit-test") {
            utility::LogInfo("Skiped for unit test.");
            return 0;
        }
    }

    pathFile = defaultPcdPath + defaultPcdFile;

    /* Import stored capture */
    geometry::PointCloud capturedPcd;
    (void)InputPointCloud((const std::string &) pathFile, capturedPcd);

    std::shared_ptr<geometry::PointCloud> pointCloud_ptr(
            new geometry::PointCloud);
    *pointCloud_ptr = capturedPcd;
    visualization::DrawGeometries({pointCloud_ptr});
    system("pause");

    /* Reduce the amount of data */
    auto downpcd = capturedPcd.VoxelDownSample(0.05);
    visualization::DrawGeometries({downpcd});

    return 0;
}
