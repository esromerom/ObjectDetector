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
    Fit a plane to a 3-D point cloud, based on the PCFITPLANE (matlab) function.

    @param ptCloud:             Point cloud object
                                @type Point cloud object.
    @param maxDistance:         Euclidian distance threshold allowed from inliers points to the
                                found plane.
                                @type Escalar euclidian distance [?]
    @param referenceVector:     Vector reference used as orientation constraint to fit the plane.
                                @type 1x3 vector [-]
    @param maxAngularDistance:  Maximum allowed absolute angular distance in degrees between the
                                normal vector of plane and the reference orientation. (5 degrees by default)
                                @type Escalar [degrees]

    @return: plane              Point cloud containing the detected plane.
    @return: model              Descriptor of plane model object.
    @return: remainPtCloud      Point cloud outside the detected plane.
    @return: inliersIdx         Indexes for inliers points.
    @return: outliersIdx        Indexes for outliers points.
    """

    [plane, model, remainPtCloud, inliersIdx, outliersIdx] = [0, 0, 0, 0, 0]
    return [plane, model, remainPtCloud, inliersIdx, outliersIdx]


def TransformRefFloorPlane(): # TODO
    """
    Obtener transformacion con referencia al plano tierra
    alphaG= atan2(-nG(1,2), nG(1,3));
    betaG= asin(nG(1,1));
    h=model_ptCloudG.Parameters(1,4);
    ptCloudG_alg_h=Rotacion_csm(ptCloudG,alphaG,betaG,0,0,0,0);
    ptCloudG_alg=Rotacion_csm(ptCloudG_alg_h,0,0,0,0,0,h);
    @return:
    """


def DeleteFloorplane(): # TODO
    """
    % Eliminar plano tierra
    ptCloudG_Boxes_h=Rotacion_csm(remainPtCloudG,alphaG,betaG,0,0,0,0);
    ptCloudG_Boxes=Rotacion_csm(ptCloudG_Boxes_h,0,0,0,0,0,h);
    @return:
    """


def RemoveInvalidPoints(): # TODO
    """
    % Detecci??n de objetos candidatos a ser cajas
    [ptCloud_objects,ind_remv1]= removeInvalidPoints(ptCloudG_Boxes_dn);
    ind_boxes_dn_rv=ind_boxes_dn(ind_remv1');
    """


def ClusterBoxesWc(ptCloud,bandwidth): #TODO
    """
    Based on MeanShiftCluster function to detect patterns
    @param ptCloud:     Point cloud object
    @param bandwidth:   Bandwith parameter. @type Scalar
    
    @return:    ptCloudsOut
    @return:    ptCloudsOut_plane
    @return:    clustMembsCell
    @return:    clustPlaneCell
    
    """
    
    [ptCloudsOut, ptCloudsOut_plane, clustMembsCell, clustPlaneCell] = [0, 0, 0, 0]
    return [ptCloudsOut, ptCloudsOut_plane, clustMembsCell, clustPlaneCell]


def PositionalAdjustment(): #TODO
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