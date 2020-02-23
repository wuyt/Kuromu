//=============================================================================================================================
//
// EasyAR Sense 4.0.0-final-7bc4102ce
// Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_IMAGEHELPER_HXX__
#define __EASYAR_IMAGEHELPER_HXX__

#include "easyar/types.hxx"

namespace easyar {

/// <summary>
/// Image helper class.
/// </summary>
class ImageHelper
{
public:
    /// <summary>
    /// Decodes a JPEG or PNG file.
    /// </summary>
    static void decode(Buffer * buffer, /* OUT */ Image * * Return);
};

#ifndef __EASYAR_OPTIONALOFIMAGE__
#define __EASYAR_OPTIONALOFIMAGE__
struct OptionalOfImage
{
    bool has_value;
    Image * value;
};
static inline easyar_OptionalOfImage OptionalOfImage_to_c(Image * o);
#endif

}

#endif

#ifndef __IMPLEMENTATION_EASYAR_IMAGEHELPER_HXX__
#define __IMPLEMENTATION_EASYAR_IMAGEHELPER_HXX__

#include "easyar/imagehelper.h"
#include "easyar/buffer.hxx"
#include "easyar/image.hxx"

namespace easyar {

inline void ImageHelper::decode(Buffer * arg0, /* OUT */ Image * * Return)
{
    easyar_OptionalOfImage _return_value_ = {false, NULL};
    easyar_ImageHelper_decode(arg0->get_cdata(), &_return_value_);
    *Return = (_return_value_.has_value ? new Image(_return_value_.value) : NULL);
}

#ifndef __IMPLEMENTATION_EASYAR_OPTIONALOFIMAGE__
#define __IMPLEMENTATION_EASYAR_OPTIONALOFIMAGE__
static inline easyar_OptionalOfImage OptionalOfImage_to_c(Image * o)
{
    if (o != NULL) {
        easyar_OptionalOfImage _return_value_ = {true, o->get_cdata()};
        return _return_value_;
    } else {
        easyar_OptionalOfImage _return_value_ = {false, NULL};
        return _return_value_;
    }
}
#endif

}

#endif
