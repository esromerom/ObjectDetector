#include <iostream>
#include <memory>

#include "open3d/Open3D.h"

#include "open3d/io/PointCloudIO.h"
#include "open3d/3rdparty/Eigen/Eigen"

#include "open3d/utility/FileSystem.h"
#include "open3d/utility/Helper.h"
#include "open3d/utility/Logging.h"
#include "open3d/utility/ProgressReporters.h"

/**
 * @brief 
 * 
 * @return int 
 */
int InputPointCloud(const std::string & filepath,
                    open3d::geometry::PointCloud & pointcloud) {
    using namespace open3d;
    using namespace io;

    bool print_progress;
    auto params = ReadPointCloudOption::ReadPointCloudOption();
    std::string format = params.format;

    if (format == "auto") {
        format = utility::filesystem::GetFileExtensionInLowerCase(filepath);
    }
    

    /* Default read params. */
    params.format = format;
    params.remove_nan_points = true;
    params.remove_infinite_points = true;
    utility::ConsoleProgressUpdater progress_updater(
            std::string("Reading ") + utility::ToUpper(format) +
                    " file: " + filepath,
            print_progress);
    params.update_progress = progress_updater;

    if (io::ReadPointCloud(filepath, pointcloud, params)) {
        utility::LogInfo("Successfully read {}", filepath);

        /* re-write pcd on 2 diff formats.
        geometry::PointCloud pointcloud_copy;
        pointcloud_copy.CloneFrom(pointcloud);

        if (io::WritePointCloud(filename_xyz, pointcloud)) {
            utility::LogInfo("Successfully wrote {}",
        filename_xyz.c_str()); } else { utility::LogError("Failed to write
        {}", filename_xyz);
        }

        if (io::WritePointCloud(filename_ply, pointcloud_copy)) {
            utility::LogInfo("Successfully wrote {}",
        filename_ply); } else { utility::LogError("Failed to write
        {}", filename_ply);
        }
         */
        return 1;
    } else {
        utility::LogWarning("Failed to read {}", filepath);
        return 0;
    }
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

    if (argc == 2) {
        std::string option(argv[1]);
        if (option == "--skip-for-unit-test") {
            utility::LogInfo("Skiped for unit test.");
            return 0;
        }
    }
    
    // std::string filepath = "../captures/test_point_cloud.ply";
    std::string filepath = "../captures/teapotOut.ply";
    // std::string filepath = "../captures/test_filter_pc_inliers.pcd";    

    /* 1. Test PCD functions */
    geometry::PointCloud pointcloud;
    PrintPointCloud(pointcloud);

    pointcloud.points_.push_back(Eigen::Vector3d(0.0, 0.0, 0.0));
    pointcloud.points_.push_back(Eigen::Vector3d(1.0, 0.0, 0.0));
    pointcloud.points_.push_back(Eigen::Vector3d(0.0, 1.0, 0.0));
    pointcloud.points_.push_back(Eigen::Vector3d(0.0, 0.0, 1.0));

    // visualization::Visualizer visualizer;
    // visualizer.DestroyVisualizerWindow();
    PrintPointCloud(pointcloud);

    geometry::PointCloud capturedPcd;
    InputPointCloud((const std::string &) filepath, capturedPcd);
    // {
    //     utility::ScopeTimer timer("FPFH estimation with Radius 0.25");
    //     // for (int i = 0; i < 20; i++) {
    //     pipelines::registration::ComputeFPFHFeature(
    //             *capturedPcd, geometry::KDTreeSearchParamRadius(0.25));
    //     //}
    // }

    // {
    //     utility::ScopeTimer timer("Normal estimation with KNN20");
    //     for (int i = 0; i < 20; i++) {
    //         capturedPcd->EstimateNormals(open3d::geometry::KDTreeSearchParamKNN(20));
    //     }
    // }
    // std::cout << capturedPcd->normals_[0] << std::endl;
    // std::cout << capturedPcd->normals_[10] << std::endl;

    auto downpcd = capturedPcd.VoxelDownSample(0.05);
    std::shared_ptr<geometry::PointCloud> pointCloud_ptr(
            new geometry::PointCloud);
    *pointCloud_ptr = capturedPcd;
    // visualization::DrawGeometries({pointCloud_ptr});
    
    // auto sphere = geometry::TriangleMesh::CreateSphere(1.0);
    // sphere->ComputeVertexNormals();
    // sphere->PaintUniformColor({0.0, 1.0, 0.0});
    visualization::DrawGeometries({downpcd});
    
    // /** test */
    // visualization::Visualizer visualizer;
    // visualizer.DestroyVisualizerWindow();
    // // visualization::DrawGeometries({capturedPcd});
    // auto downpcd = capturedPcd.VoxelDownSample(0.05);

    // visualization::DrawGeometries({downpcd});
    // // visualizer.CreateVisualizerWindow("Open3D", 1600, 900);

    // std::shared_ptr<geometry::PointCloud> pointCloud_ptr(
    //         new geometry::PointCloud);
    // *pointCloud_ptr = capturedPcd;
    // pointcloud_ptr->NormalizeNormals();

    // std::shared_ptr<geometry::PointCloud> modPointCloud_ptr(
    //         new geometry::PointCloud);
    // modPointCloud_ptr = downpcd;

    // visualizer.AddGeometry(pointCloud_ptr);
    // visualizer.AddGeometry(downpcd);
    // visualizer.CreateVisualizerWindow("Open3D", 1600, 900);
    // visualizer.Run();

    // // while()
    // // {

    // // }
    // system("pause");
    // visualizer.DestroyVisualizerWindow();

    return 0;

}
