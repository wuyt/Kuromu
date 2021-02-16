//=============================================================================================================================
//
// EasyAR Sense 4.1.0.7750-f1413084f
// Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_MATRIX_HXX__
#define __EASYAR_MATRIX_HXX__

#include "easyar/types.hxx"

namespace easyar {

/// <summary>
/// record
/// Square matrix of 4. The data arrangement is row-major.
/// </summary>
struct Matrix44F
{
    /// <summary>
    /// The raw data of matrix.
    /// </summary>
    float data[16];

    Matrix44F();
    Matrix44F(float data_0, float data_1, float data_2, float data_3, float data_4, float data_5, float data_6, float data_7, float data_8, float data_9, float data_10, float data_11, float data_12, float data_13, float data_14, float data_15);
    easyar_Matrix44F get_cdata();
};

/// <summary>
/// record
/// Square matrix of 3. The data arrangement is row-major.
/// </summary>
struct Matrix33F
{
    /// <summary>
    /// The raw data of matrix.
    /// </summary>
    float data[9];

    Matrix33F();
    Matrix33F(float data_0, float data_1, float data_2, float data_3, float data_4, float data_5, float data_6, float data_7, float data_8);
    easyar_Matrix33F get_cdata();
};

}

#endif

#ifndef __IMPLEMENTATION_EASYAR_MATRIX_HXX__
#define __IMPLEMENTATION_EASYAR_MATRIX_HXX__

namespace easyar {

inline Matrix44F::Matrix44F()
{
    this->data[0] = float();
    this->data[1] = float();
    this->data[2] = float();
    this->data[3] = float();
    this->data[4] = float();
    this->data[5] = float();
    this->data[6] = float();
    this->data[7] = float();
    this->data[8] = float();
    this->data[9] = float();
    this->data[10] = float();
    this->data[11] = float();
    this->data[12] = float();
    this->data[13] = float();
    this->data[14] = float();
    this->data[15] = float();
}
inline Matrix44F::Matrix44F(float data_0, float data_1, float data_2, float data_3, float data_4, float data_5, float data_6, float data_7, float data_8, float data_9, float data_10, float data_11, float data_12, float data_13, float data_14, float data_15)
{
    this->data[0] = data_0;
    this->data[1] = data_1;
    this->data[2] = data_2;
    this->data[3] = data_3;
    this->data[4] = data_4;
    this->data[5] = data_5;
    this->data[6] = data_6;
    this->data[7] = data_7;
    this->data[8] = data_8;
    this->data[9] = data_9;
    this->data[10] = data_10;
    this->data[11] = data_11;
    this->data[12] = data_12;
    this->data[13] = data_13;
    this->data[14] = data_14;
    this->data[15] = data_15;
}
inline easyar_Matrix44F Matrix44F::get_cdata()
{
    easyar_Matrix44F _return_value_ = {data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8], data[9], data[10], data[11], data[12], data[13], data[14], data[15]};
    return _return_value_;
}
inline Matrix33F::Matrix33F()
{
    this->data[0] = float();
    this->data[1] = float();
    this->data[2] = float();
    this->data[3] = float();
    this->data[4] = float();
    this->data[5] = float();
    this->data[6] = float();
    this->data[7] = float();
    this->data[8] = float();
}
inline Matrix33F::Matrix33F(float data_0, float data_1, float data_2, float data_3, float data_4, float data_5, float data_6, float data_7, float data_8)
{
    this->data[0] = data_0;
    this->data[1] = data_1;
    this->data[2] = data_2;
    this->data[3] = data_3;
    this->data[4] = data_4;
    this->data[5] = data_5;
    this->data[6] = data_6;
    this->data[7] = data_7;
    this->data[8] = data_8;
}
inline easyar_Matrix33F Matrix33F::get_cdata()
{
    easyar_Matrix33F _return_value_ = {data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8]};
    return _return_value_;
}
}

#endif
