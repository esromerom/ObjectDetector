/**
 * @file        inputCapture.h
 * @copyright   Semillero SIRA 2022 -
 *              Universidad de la Salle, Bogota, Colombia
 * 
 * @brief       Header file to handle capture input to the algorithm.
 */
#include <iostream>
#include <memory>
#include "open3d/Open3D.h"

/**
 * @brief   Imports a fixed point cloud.
 * @todo    Use args to check or ask for a file or capture device.
 * 
 * @param filepath 
 * @param pointcloud 
 * @return int 
 */
extern int InputPointCloud(const std::string & filepath,
                    open3d::geometry::PointCloud & pointcloud);