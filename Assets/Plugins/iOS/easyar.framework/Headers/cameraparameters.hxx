//=============================================================================================================================
//
// EasyAR Sense 4.1.0.7750-f1413084f
// Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_CAMERAPARAMETERS_HXX__
#define __EASYAR_CAMERAPARAMETERS_HXX__

#include "easyar/types.hxx"

namespace easyar {

/// <summary>
/// Camera parameters, including image size, focal length, principal point, camera type and camera rotation against natural orientation.
/// </summary>
class CameraParameters
{
protected:
    easyar_CameraParameters * cdata_ ;
    void init_cdata(easyar_CameraParameters * cdata);
    virtual CameraParameters & operator=(const CameraParameters & data) { return *this; } //deleted
public:
    CameraParameters(easyar_CameraParameters * cdata);
    virtual ~CameraParameters();

    CameraParameters(const CameraParameters & data);
    const easyar_CameraParameters * get_cdata() const;
    easyar_CameraParameters * get_cdata();

    CameraParameters(Vec2I imageSize, Vec2F focalLength, Vec2F principalPoint, CameraDeviceType cameraDeviceType, int cameraOrientation);
    /// <summary>
    /// Image size.
    /// </summary>
    Vec2I size();
    /// <summary>
    /// Focal length, the distance from effective optical center to CCD plane, divided by unit pixel density in width and height directions. The unit is pixel.
    /// </summary>
    Vec2F focalLength();
    /// <summary>
    /// Principal point, coordinates of the intersection point of principal axis on CCD plane against the left-top corner of the image. The unit is pixel.
    /// </summary>
    Vec2F principalPoint();
    /// <summary>
    /// Camera device type. Default, back or front camera. On desktop devices, there are only default cameras. On mobile devices, there is a differentiation between back and front cameras.
    /// </summary>
    CameraDeviceType cameraDeviceType();
    /// <summary>
    /// Camera rotation against device natural orientation.
    /// For Android phones and some Android tablets, this value is 90 degrees.
    /// For Android eye-wear and some Android tablets, this value is 0 degrees.
    /// For all current iOS devices, this value is 90 degrees.
    /// </summary>
    int cameraOrientation();
    /// <summary>
    /// Creates CameraParameters with default camera intrinsics. Default intrinsics are calculated by image size, which is not very precise.
    /// </summary>
    static void createWithDefaultIntrinsics(Vec2I imageSize, CameraDeviceType cameraDeviceType, int cameraOrientation, /* OUT */ CameraParameters * * Return);
    /// <summary>
    /// Get equivalent CameraParameters for a different camera image size.
    /// </summary>
    void getResized(Vec2I imageSize, /* OUT */ CameraParameters * * Return);
    /// <summary>
    /// Calculates the angle required to rotate the camera image clockwise to align it with the screen.
    /// screenRotation is the angle of rotation of displaying screen image against device natural orientation in clockwise in degrees.
    /// For iOS(UIInterfaceOrientationPortrait as natural orientation):
    /// * UIInterfaceOrientationPortrait: rotation = 0
    /// * UIInterfaceOrientationLandscapeRight: rotation = 90
    /// * UIInterfaceOrientationPortraitUpsideDown: rotation = 180
    /// * UIInterfaceOrientationLandscapeLeft: rotation = 270
    /// For Android:
    /// * Surface.ROTATION_0 = 0
    /// * Surface.ROTATION_90 = 90
    /// * Surface.ROTATION_180 = 180
    /// * Surface.ROTATION_270 = 270
    /// </summary>
    int imageOrientation(int screenRotation);
    /// <summary>
    /// Calculates whether the image needed to be flipped horizontally. The image is rotated, then flipped in rendering. When cameraDeviceType is front, a flip is automatically applied. Pass manualHorizontalFlip with true to add a manual flip.
    /// </summary>
    bool imageHorizontalFlip(bool manualHorizontalFlip);
    /// <summary>
    /// Calculates the perspective projection matrix needed by virtual object rendering. The projection transforms points from camera coordinate system to clip coordinate system ([-1, 1]^4). The form of perspective projection matrix is the same as OpenGL, that matrix multiply column vector of homogeneous coordinates of point on the right, ant not like Direct3D, that matrix multiply row vector of homogeneous coordinates of point on the left. But data arrangement is row-major, not like OpenGL&#39;s column-major. Clip coordinate system and normalized device coordinate system are defined as the same as OpenGL&#39;s default.
    /// </summary>
    Matrix44F projection(float nearPlane, float farPlane, float viewportAspectRatio, int screenRotation, bool combiningFlip, bool manualHorizontalFlip);
    /// <summary>
    /// Calculates the orthogonal projection matrix needed by camera background rendering. The projection transforms points from image quad coordinate system ([-1, 1]^2) to clip coordinate system ([-1, 1]^4), with the undefined two dimensions unchanged. The form of orthogonal projection matrix is the same as OpenGL, that matrix multiply column vector of homogeneous coordinates of point on the right, ant not like Direct3D, that matrix multiply row vector of homogeneous coordinates of point on the left. But data arrangement is row-major, not like OpenGL&#39;s column-major. Clip coordinate system and normalized device coordinate system are defined as the same as OpenGL&#39;s default.
    /// </summary>
    Matrix44F imageProjection(float viewportAspectRatio, int screenRotation, bool combiningFlip, bool manualHorizontalFlip);
    /// <summary>
    /// Transforms points from image coordinate system ([0, 1]^2) to screen coordinate system ([0, 1]^2). Both coordinate system is x-left, y-down, with origin at left-top.
    /// </summary>
    Vec2F screenCoordinatesFromImageCoordinates(float viewportAspectRatio, int screenRotation, bool combiningFlip, bool manualHorizontalFlip, Vec2F imageCoordinates);
    /// <summary>
    /// Transforms points from screen coordinate system ([0, 1]^2) to image coordinate system ([0, 1]^2). Both coordinate system is x-left, y-down, with origin at left-top.
    /// </summary>
    Vec2F imageCoordinatesFromScreenCoordinates(float viewportAspectRatio, int screenRotation, bool combiningFlip, bool manualHorizontalFlip, Vec2F screenCoordinates);
    /// <summary>
    /// Checks if two groups of parameters are equal.
    /// </summary>
    bool equalsTo(CameraParameters * other);
};

}

#endif

#ifndef __IMPLEMENTATION_EASYAR_CAMERAPARAMETERS_HXX__
#define __IMPLEMENTATION_EASYAR_CAMERAPARAMETERS_HXX__

#include "easyar/cameraparameters.h"
#include "easyar/vector.hxx"
#include "easyar/matrix.hxx"

namespace easyar {

inline CameraParameters::CameraParameters(easyar_CameraParameters * cdata)
    :
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline CameraParameters::~CameraParameters()
{
    if (cdata_) {
        easyar_CameraParameters__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline CameraParameters::CameraParameters(const CameraParameters & data)
    :
    cdata_(NULL)
{
    easyar_CameraParameters * cdata = NULL;
    easyar_CameraParameters__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_CameraParameters * CameraParameters::get_cdata() const
{
    return cdata_;
}
inline easyar_CameraParameters * CameraParameters::get_cdata()
{
    return cdata_;
}
inline void CameraParameters::init_cdata(easyar_CameraParameters * cdata)
{
    cdata_ = cdata;
}
inline CameraParameters::CameraParameters(Vec2I arg0, Vec2F arg1, Vec2F arg2, CameraDeviceType arg3, int arg4)
    :
    cdata_(NULL)
{
    easyar_CameraParameters * _return_value_ = NULL;
    easyar_CameraParameters__ctor(arg0.get_cdata(), arg1.get_cdata(), arg2.get_cdata(), static_cast<easyar_CameraDeviceType>(arg3), arg4, &_return_value_);
    init_cdata(_return_value_);
}
inline Vec2I CameraParameters::size()
{
    if (cdata_ == NULL) {
        return Vec2I();
    }
    easyar_Vec2I _return_value_ = easyar_CameraParameters_size(cdata_);
    return Vec2I(_return_value_.data[0], _return_value_.data[1]);
}
inline Vec2F CameraParameters::focalLength()
{
    if (cdata_ == NULL) {
        return Vec2F();
    }
    easyar_Vec2F _return_value_ = easyar_CameraParameters_focalLength(cdata_);
    return Vec2F(_return_value_.data[0], _return_value_.data[1]);
}
inline Vec2F CameraParameters::principalPoint()
{
    if (cdata_ == NULL) {
        return Vec2F();
    }
    easyar_Vec2F _return_value_ = easyar_CameraParameters_principalPoint(cdata_);
    return Vec2F(_return_value_.data[0], _return_value_.data[1]);
}
inline CameraDeviceType CameraParameters::cameraDeviceType()
{
    if (cdata_ == NULL) {
        return CameraDeviceType();
    }
    easyar_CameraDeviceType _return_value_ = easyar_CameraParameters_cameraDeviceType(cdata_);
    return static_cast<CameraDeviceType>(_return_value_);
}
inline int CameraParameters::cameraOrientation()
{
    if (cdata_ == NULL) {
        return int();
    }
    int _return_value_ = easyar_CameraParameters_cameraOrientation(cdata_);
    return _return_value_;
}
inline void CameraParameters::createWithDefaultIntrinsics(Vec2I arg0, CameraDeviceType arg1, int arg2, /* OUT */ CameraParameters * * Return)
{
    easyar_CameraParameters * _return_value_ = NULL;
    easyar_CameraParameters_createWithDefaultIntrinsics(arg0.get_cdata(), static_cast<easyar_CameraDeviceType>(arg1), arg2, &_return_value_);
    *Return = new CameraParameters(_return_value_);
}
inline void CameraParameters::getResized(Vec2I arg0, /* OUT */ CameraParameters * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_CameraParameters * _return_value_ = NULL;
    easyar_CameraParameters_getResized(cdata_, arg0.get_cdata(), &_return_value_);
    *Return = new CameraParameters(_return_value_);
}
inline int CameraParameters::imageOrientation(int arg0)
{
    if (cdata_ == NULL) {
        return int();
    }
    int _return_value_ = easyar_CameraParameters_imageOrientation(cdata_, arg0);
    return _return_value_;
}
inline bool CameraParameters::imageHorizontalFlip(bool arg0)
{
    if (cdata_ == NULL) {
        return bool();
    }
    bool _return_value_ = easyar_CameraParameters_imageHorizontalFlip(cdata_, arg0);
    return _return_value_;
}
inline Matrix44F CameraParameters::projection(float arg0, float arg1, float arg2, int arg3, bool arg4, bool arg5)
{
    if (cdata_ == NULL) {
        return Matrix44F();
    }
    easyar_Matrix44F _return_value_ = easyar_CameraParameters_projection(cdata_, arg0, arg1, arg2, arg3, arg4, arg5);
    return Matrix44F(_return_value_.data[0], _return_value_.data[1], _return_value_.data[2], _return_value_.data[3], _return_value_.data[4], _return_value_.data[5], _return_value_.data[6], _return_value_.data[7], _return_value_.data[8], _return_value_.data[9], _return_value_.data[10], _return_value_.data[11], _return_value_.data[12], _return_value_.data[13], _return_value_.data[14], _return_value_.data[15]);
}
inline Matrix44F CameraParameters::imageProjection(float arg0, int arg1, bool arg2, bool arg3)
{
    if (cdata_ == NULL) {
        return Matrix44F();
    }
    easyar_Matrix44F _return_value_ = easyar_CameraParameters_imageProjection(cdata_, arg0, arg1, arg2, arg3);
    return Matrix44F(_return_value_.data[0], _return_value_.data[1], _return_value_.data[2], _return_value_.data[3], _return_value_.data[4], _return_value_.data[5], _return_value_.data[6], _return_value_.data[7], _return_value_.data[8], _return_value_.data[9], _return_value_.data[10], _return_value_.data[11], _return_value_.data[12], _return_value_.data[13], _return_value_.data[14], _return_value_.data[15]);
}
inline Vec2F CameraParameters::screenCoordinatesFromImageCoordinates(float arg0, int arg1, bool arg2, bool arg3, Vec2F arg4)
{
    if (cdata_ == NULL) {
        return Vec2F();
    }
    easyar_Vec2F _return_value_ = easyar_CameraParameters_screenCoordinatesFromImageCoordinates(cdata_, arg0, arg1, arg2, arg3, arg4.get_cdata());
    return Vec2F(_return_value_.data[0], _return_value_.data[1]);
}
inline Vec2F CameraParameters::imageCoordinatesFromScreenCoordinates(float arg0, int arg1, bool arg2, bool arg3, Vec2F arg4)
{
    if (cdata_ == NULL) {
        return Vec2F();
    }
    easyar_Vec2F _return_value_ = easyar_CameraParameters_imageCoordinatesFromScreenCoordinates(cdata_, arg0, arg1, arg2, arg3, arg4.get_cdata());
    return Vec2F(_return_value_.data[0], _return_value_.data[1]);
}
inline bool CameraParameters::equalsTo(CameraParameters * arg0)
{
    if (cdata_ == NULL) {
        return bool();
    }
    bool _return_value_ = easyar_CameraParameters_equalsTo(cdata_, arg0->get_cdata());
    return _return_value_;
}

}

#endif
