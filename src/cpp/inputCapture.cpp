/******************************************************************************
 * @file        inputCapture.c
 * @copyright   Semillero SIRA 2022 -
 *              Universidad de la Salle, Bogota, Colombia
 * 
 * @brief       File to handle capture input to the algorithm.
 ******************************************************************************/

#include <iostream>
#include <memory>

#include "open3d/Open3D.h"
#include "open3d/io/PointCloudIO.h"

#include "open3d/utility/FileSystem.h"
#include "open3d/utility/Helper.h"
#include "open3d/utility/Logging.h"
#include "open3d/utility/ProgressReporters.h"

#include "inputCapture.h"

extern int InputPointCloud(const std::string & filepath,
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