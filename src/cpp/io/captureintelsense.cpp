/**
 * @file    captureIntelsense.cpp
 * 
 * @author  Erik ROMERO
 * 
 * @brief   CApture from intelsense camera.
 */ 

#include <open3d/Open3D.hpp>

int main(int argc, char *argv[]) {
    using namespace open3d;
    open3d::t::io::RealSenseSensorConfig rs_cfg;
    open3d::io::ReadIJsonConvertible(config_filename, rs_cfg);
    RealSenseSensor rs;
    rs.InitSensor(rs_cfg, 0, bag_filename);
    rs.StartCapture(true);  // true: start recording with capture
    for(size_t fid = 0; fid<150; ++fid) {
        im_rgbd = rs.CaptureFrame(true, true);  // wait for frames and align them
        // process im_rgbd.depth_ and im_rgbd.color_
    }
    rs.StopCapture();
}