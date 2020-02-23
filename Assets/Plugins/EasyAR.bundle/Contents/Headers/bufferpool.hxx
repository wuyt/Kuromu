//=============================================================================================================================
//
// EasyAR Sense 4.0.0-final-7bc4102ce
// Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_BUFFERPOOL_HXX__
#define __EASYAR_BUFFERPOOL_HXX__

#include "easyar/types.hxx"

namespace easyar {

/// <summary>
/// BufferPool is a memory pool to reduce memory allocation time consumption for functionality like custom camera interoperability, which needs to allocate memory buffers of a fixed size repeatedly.
/// </summary>
class BufferPool
{
protected:
    easyar_BufferPool * cdata_ ;
    void init_cdata(easyar_BufferPool * cdata);
    virtual BufferPool & operator=(const BufferPool & data) { return *this; } //deleted
public:
    BufferPool(easyar_BufferPool * cdata);
    virtual ~BufferPool();

    BufferPool(const BufferPool & data);
    const easyar_BufferPool * get_cdata() const;
    easyar_BufferPool * get_cdata();

    /// <summary>
    /// block_size is the byte size of each `Buffer`_ .
    /// capacity is the maximum count of `Buffer`_ .
    /// </summary>
    BufferPool(int block_size, int capacity);
    /// <summary>
    /// The byte size of each `Buffer`_ .
    /// </summary>
    int block_size();
    /// <summary>
    /// The maximum count of `Buffer`_ .
    /// </summary>
    int capacity();
    /// <summary>
    /// Current acquired count of `Buffer`_ .
    /// </summary>
    int size();
    /// <summary>
    /// Tries to acquire a memory block. If current acquired count of `Buffer`_ does not reach maximum, a new `Buffer`_ is fetched or allocated, or else null is returned.
    /// </summary>
    void tryAcquire(/* OUT */ Buffer * * Return);
};

#ifndef __EASYAR_OPTIONALOFBUFFER__
#define __EASYAR_OPTIONALOFBUFFER__
struct OptionalOfBuffer
{
    bool has_value;
    Buffer * value;
};
static inline easyar_OptionalOfBuffer OptionalOfBuffer_to_c(Buffer * o);
#endif

}

#endif

#ifndef __IMPLEMENTATION_EASYAR_BUFFERPOOL_HXX__
#define __IMPLEMENTATION_EASYAR_BUFFERPOOL_HXX__

#include "easyar/bufferpool.h"
#include "easyar/buffer.hxx"

namespace easyar {

inline BufferPool::BufferPool(easyar_BufferPool * cdata)
    :
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline BufferPool::~BufferPool()
{
    if (cdata_) {
        easyar_BufferPool__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline BufferPool::BufferPool(const BufferPool & data)
    :
    cdata_(NULL)
{
    easyar_BufferPool * cdata = NULL;
    easyar_BufferPool__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_BufferPool * BufferPool::get_cdata() const
{
    return cdata_;
}
inline easyar_BufferPool * BufferPool::get_cdata()
{
    return cdata_;
}
inline void BufferPool::init_cdata(easyar_BufferPool * cdata)
{
    cdata_ = cdata;
}
inline BufferPool::BufferPool(int arg0, int arg1)
    :
    cdata_(NULL)
{
    easyar_BufferPool * _return_value_ = NULL;
    easyar_BufferPool__ctor(arg0, arg1, &_return_value_);
    init_cdata(_return_value_);
}
inline int BufferPool::block_size()
{
    if (cdata_ == NULL) {
        return int();
    }
    int _return_value_ = easyar_BufferPool_block_size(cdata_);
    return _return_value_;
}
inline int BufferPool::capacity()
{
    if (cdata_ == NULL) {
        return int();
    }
    int _return_value_ = easyar_BufferPool_capacity(cdata_);
    return _return_value_;
}
inline int BufferPool::size()
{
    if (cdata_ == NULL) {
        return int();
    }
    int _return_value_ = easyar_BufferPool_size(cdata_);
    return _return_value_;
}
inline void BufferPool::tryAcquire(/* OUT */ Buffer * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_OptionalOfBuffer _return_value_ = {false, NULL};
    easyar_BufferPool_tryAcquire(cdata_, &_return_value_);
    *Return = (_return_value_.has_value ? new Buffer(_return_value_.value) : NULL);
}

#ifndef __IMPLEMENTATION_EASYAR_OPTIONALOFBUFFER__
#define __IMPLEMENTATION_EASYAR_OPTIONALOFBUFFER__
static inline easyar_OptionalOfBuffer OptionalOfBuffer_to_c(Buffer * o)
{
    if (o != NULL) {
        easyar_OptionalOfBuffer _return_value_ = {true, o->get_cdata()};
        return _return_value_;
    } else {
        easyar_OptionalOfBuffer _return_value_ = {false, NULL};
        return _return_value_;
    }
}
#endif

}

#endif
