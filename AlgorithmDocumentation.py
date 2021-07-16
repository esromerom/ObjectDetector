#!/usr/bin/env python3
# encode: utf8

"""
@file       Function list
@copyright  Erik Romero - Semillero SIRA 2021 -
            Universidad de la Salle, Bogota, Colombia

@version    $Revision:$
@change     $Change:$
@date       $Date:$
@authors    $Author:$

@brief      This file contains a list of the components, modules or processes
            the project might contain and develope to achieve its purpose.
            This recopilation is approximative and is based on the original
            Matlab implementation of the algorithm reported in the following
            link: https://link.springer.com/chapter/10.1007/978-3-030-00353-1_40
"""

def GetPointCloud():
    """! This function will obtain 3D point cloud data to process into the
    algorithm either already stored data or captured through connected hardware.
            
    @return:    Point cloud object following.
    
    @note:  This process must interface the GUI and the main program. Must be
            independent of the hardware connected. It should not need input
            parameters to work, they will be defined by the user using the GUI.
    """
    pass


def DenoisePC(pointCloudIn, denoisConfig):
    """! Remove noise from a 3D point cloud object. on the given point cloud
    element, following the configured thresholds and enabled features on
    denoiseConfig. By default the threshold is set following the standard
    deviation of the surrounding points.

    @param pointCloudIn:    Element of the PointCloud class to denoise.
    @param denoisConfig:    De-noise configuration class element with the
                            enabled and configured parameters.
    
    @return:    The filtered point cloud object. And also it could return
                indexes for the inleirs and outliers according to the filter.
    
    @note:      This function is already implemented in the matlab library.
                To verify in available ones for RPi.
    """
    pass

def RotationCsm(ptCloud_in,thetax,thetay,thetaz,Px,Py,Pz):
    """
    Function to perform rotation operation based on the homogeneus components
    matrix over a given
    
    @param ptCloud_in:  Source point cloud
    @param thetax:      Rotation angle on x-axis.
    @param thetay:      Rotation angle on y-axis.
    @param thetaz:      Rotation angle on z-axis.
    @param Px:          Displacement along x-axis.
    @param Py:          Displacement along y-axis.
    @param Pz:          Displacement along z-axis.
    
    @return: ptCloud_out    Transformed point cloud element.
    
    @note:  IT may be implemented more properly in Numpy pkg or similars.
    @note:  Uses 'pctransform' function that might be already included in PCL sources.
    """
    pass
    
    def rotX(angle):
        """
        Abstraction of homogeneus matrix for X rotation.
        @param angle: Angle of rotation along x-axis.

        @return: rotational Matrix for the given the angle.

        @note:  IT may be implemented more properly in Numpy pkg or similars.
        """
        pass

    def rotY(angle):
        """
        Abstraction of homogeneus matrix for Y rotation.
        @param angle: Angle of rotation along y-axis.

        @return: rotational Matrix for the given the angle.

        @note:  IT may be implemented more properly in Numpy pkg or similars.
        """
        pass

    def rotZ(angle):
        """
        Abstraction of homogeneus matrix for Z rotation.
        @param angle: Angle of rotation along z-axis.

        @return: rotational Matrix for the given the angle.

        @note:  IT may be implemented more properly in Numpy pkg or similars.
        """
        pass


def PlaneDetection(ptCloud,maxDistance,maxAngularDistance):
    """
    
    @param ptCloud:
    @param maxDistance:
    @param maxAngularDistance:
    @return: plane
    @return: model,remainPtCloud,inlierIndices,outlierIndices
    """
    
    pass


def PositionalAdjustment():
    """
    :param fg:
    :param gh:
    :return:
    """
    pass

# (Rough adjustment)

# Floor plane detection

# Detection possible Box objects

# Clustering

GetPointCloud()