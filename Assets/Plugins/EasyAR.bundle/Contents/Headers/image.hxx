//=============================================================================================================================
//
// EasyAR Sense 4.0.0-final-7bc4102ce
// Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_IMAGE_HXX__
#define __EASYAR_IMAGE_HXX__

#include "easyar/types.hxx"

namespace easyar {

/// <summary>
/// Image stores an image data and represents an image in memory.
/// Image raw data can be accessed as byte array. The width/height/etc information are also accessible.
/// You can always access image data since the first version of EasyAR Sense.
///
/// You can do this in iOS
/// ::
///
///     #import &lt;easyar/buffer.oc.h&gt;
///     #import &lt;easyar/image.oc.h&gt;
///
///     easyar_OutputFrame * outputFrame = [outputFrameBuffer peek];
///     if (outputFrame != nil) {
///         easyar_Image * i = [[outputFrame inputFrame] image];
///         easyar_Buffer * b = [i buffer];
///         char * bytes = calloc([b size], 1);
///         memcpy(bytes, [b data], [b size]);
///         // use bytes here
///         free(bytes);
///     }
///
/// Or in Android
/// ::
///
///     import cn.easyar.*;
///
///     OutputFrame outputFrame = outputFrameBuffer.peek();
///     if (outputFrame != null) {
///         InputFrame inputFrame = outputFrame.inputFrame();
///         Image i = inputFrame.image();
///         Buffer b = i.buffer();
///         byte[] bytes = new byte[b.size()];
///         b.copyToByteArray(0, bytes, 0, bytes.length);
///         // use bytes here
///         b.dispose();
///         i.dispose();
///         inputFrame.dispose();
///         outputFrame.dispose();
///     }
/// </summary>
class Image
{
protected:
    easyar_Image * cdata_ ;
    void init_cdata(easyar_Image * cdata);
    virtual Image & operator=(const Image & data) { return *this; } //deleted
public:
    Image(easyar_Image * cdata);
    virtual ~Image();

    Image(const Image & data);
    const easyar_Image * get_cdata() const;
    easyar_Image * get_cdata();

    Image(Buffer * buffer, PixelFormat format, int width, int height);
    /// <summary>
    /// Returns buffer inside image. It can be used to access internal data of image. The content of `Buffer`_ shall not be modified, as they may be accessed from other threads.
    /// </summary>
    void buffer(/* OUT */ Buffer * * Return);
    /// <summary>
    /// Returns image format.
    /// </summary>
    PixelFormat format();
    /// <summary>
    /// Returns image width.
    /// </summary>
    int width();
    /// <summary>
    /// Returns image height.
    /// </summary>
    int height();
    /// <summary>
    /// Checks if the image is empty.
    /// </summary>
    bool empty();
};

}

#endif

#ifndef __IMPLEMENTATION_EASYAR_IMAGE_HXX__
#define __IMPLEMENTATION_EASYAR_IMAGE_HXX__

#include "easyar/image.h"
#include "easyar/buffer.hxx"

namespace easyar {

inline Image::Image(easyar_Image * cdata)
    :
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline Image::~Image()
{
    if (cdata_) {
        easyar_Image__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline Image::Image(const Image & data)
    :
    cdata_(NULL)
{
    easyar_Image * cdata = NULL;
    easyar_Image__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_Image * Image::get_cdata() const
{
    return cdata_;
}
inline easyar_Image * Image::get_cdata()
{
    return cdata_;
}
inline void Image::init_cdata(easyar_Image * cdata)
{
    cdata_ = cdata;
}
inline Image::Image(Buffer * arg0, PixelFormat arg1, int arg2, int arg3)
    :
    cdata_(NULL)
{
    easyar_Image * _return_value_ = NULL;
    easyar_Image__ctor(arg0->get_cdata(), static_cast<easyar_PixelFormat>(arg1), arg2, arg3, &_return_value_);
    init_cdata(_return_value_);
}
inline void Image::buffer(/* OUT */ Buffer * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_Buffer * _return_value_ = NULL;
    easyar_Image_buffer(cdata_, &_return_value_);
    *Return = new Buffer(_return_value_);
}
inline PixelFormat Image::format()
{
    if (cdata_ == NULL) {
        return PixelFormat();
    }
    easyar_PixelFormat _return_value_ = easyar_Image_format(cdata_);
    return static_cast<PixelFormat>(_return_value_);
}
inline int Image::width()
{
    if (cdata_ == NULL) {
        return int();
    }
    int _return_value_ = easyar_Image_width(cdata_);
    return _return_value_;
}
inline int Image::height()
{
    if (cdata_ == NULL) {
        return int();
    }
    int _return_value_ = easyar_Image_height(cdata_);
    return _return_value_;
}
inline bool Image::empty()
{
    if (cdata_ == NULL) {
        return bool();
    }
    bool _return_value_ = easyar_Image_empty(cdata_);
    return _return_value_;
}

}

#endif
