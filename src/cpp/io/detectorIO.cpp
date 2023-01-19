/**
 * @file    DetectorIO.cpp
 * 
 * @author  Erik ROMERO
 * 
 * @brief   Input/output of the project
 */ 

#include <string.h>

#include "../../Open3D/cpp/open3d/Open3D.h"

int main(int argc, char *argv[]) {
    using namespace open3d;

    pcd = io.read_point_cloud("../../test_data/my_points.txt", format='xyz'

    utility::SetVerbosityLevel(utility::VerbosityLevel::Debug);

    if (argc != 2 ||
        utility::ProgramOptionExistsAny(argc, argv, {"-h", "--help"})) {
        PrintHelp();
        return 1;
    }

    auto pcd = io::CreatePointCloudFromFile(argv[1]);
    {
        utility::ScopeTimer timer("FPFH estimation with Radius 0.25");
        // for (int i = 0; i < 20; i++) {
        // pipelines::registration::ComputeFPFHFeature(
                // *pcd, open3d::geometry::KDTreeSearchParamRadius(0.25));
        //}
    }
}