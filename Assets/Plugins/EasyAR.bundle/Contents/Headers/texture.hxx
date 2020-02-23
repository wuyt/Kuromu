//=============================================================================================================================
//
// EasyAR Sense 4.0.0-final-7bc4102ce
// Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_TEXTURE_HXX__
#define __EASYAR_TEXTURE_HXX__

#include "easyar/types.hxx"

namespace easyar {

/// <summary>
/// TextureId encapsulates a texture object in rendering API.
/// For OpenGL/OpenGLES, getInt and fromInt shall be used. For Direct3D, getPointer and fromPointer shall be used.
/// </summary>
class TextureId
{
protected:
    easyar_TextureId * cdata_ ;
    void init_cdata(easyar_TextureId * cdata);
    virtual TextureId & operator=(const TextureId & data) { return *this; } //deleted
public:
    TextureId(easyar_TextureId * cdata);
    virtual ~TextureId();

    TextureId(const TextureId & data);
    const easyar_TextureId * get_cdata() const;
    easyar_TextureId * get_cdata();

    /// <summary>
    /// Gets ID of an OpenGL/OpenGLES texture object.
    /// </summary>
    int getInt();
    /// <summary>
    /// Gets pointer of a Direct3D texture object.
    /// </summary>
    void * getPointer();
    /// <summary>
    /// Creates from ID of an OpenGL/OpenGLES texture object.
    /// </summary>
    static void fromInt(int _value, /* OUT */ TextureId * * Return);
    /// <summary>
    /// Creates from pointer of a Direct3D texture object.
    /// </summary>
    static void fromPointer(void * ptr, /* OUT */ TextureId * * Return);
};

}

#endif

#ifndef __IMPLEMENTATION_EASYAR_TEXTURE_HXX__
#define __IMPLEMENTATION_EASYAR_TEXTURE_HXX__

#include "easyar/texture.h"

namespace easyar {

inline TextureId::TextureId(easyar_TextureId * cdata)
    :
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline TextureId::~TextureId()
{
    if (cdata_) {
        easyar_TextureId__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline TextureId::TextureId(const TextureId & data)
    :
    cdata_(NULL)
{
    easyar_TextureId * cdata = NULL;
    easyar_TextureId__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_TextureId * TextureId::get_cdata() const
{
    return cdata_;
}
inline easyar_TextureId * TextureId::get_cdata()
{
    return cdata_;
}
inline void TextureId::init_cdata(easyar_TextureId * cdata)
{
    cdata_ = cdata;
}
inline int TextureId::getInt()
{
    if (cdata_ == NULL) {
        return int();
    }
    int _return_value_ = easyar_TextureId_getInt(cdata_);
    return _return_value_;
}
inline void * TextureId::getPointer()
{
    if (cdata_ == NULL) {
        return NULL;
    }
    void * _return_value_ = easyar_TextureId_getPointer(cdata_);
    return _return_value_;
}
inline void TextureId::fromInt(int arg0, /* OUT */ TextureId * * Return)
{
    easyar_TextureId * _return_value_ = NULL;
    easyar_TextureId_fromInt(arg0, &_return_value_);
    *Return = new TextureId(_return_value_);
}
inline void TextureId::fromPointer(void * arg0, /* OUT */ TextureId * * Return)
{
    easyar_TextureId * _return_value_ = NULL;
    easyar_TextureId_fromPointer(arg0, &_return_value_);
    *Return = new TextureId(_return_value_);
}

}

#endif
