#include "open3d/Open3D.h"

/**
 * @brief   Imports a fixed point cloud.
 * @todo    Use args to check or ask for a file or capture device.
 * 
 * @return  int 
 */
geometry::PointCloud InputPointCloud(void) {
    using namespace open3d;
    std::string filepath = "../captures/test_point_cloud.ply");
    
    auto pcd = io::CreatePointCloudFromFile(argv[1]);
    return 0;
}