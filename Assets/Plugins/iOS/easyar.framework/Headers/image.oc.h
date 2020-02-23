//=============================================================================================================================
//
// EasyAR Sense 4.0.0-final-7bc4102ce
// Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#import "easyar/types.oc.h"

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
@interface easyar_Image : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

+ (easyar_Image *) create:(easyar_Buffer *)buffer format:(easyar_PixelFormat)format width:(int)width height:(int)height;
/// <summary>
/// Returns buffer inside image. It can be used to access internal data of image. The content of `Buffer`_ shall not be modified, as they may be accessed from other threads.
/// </summary>
- (easyar_Buffer *)buffer;
/// <summary>
/// Returns image format.
/// </summary>
- (easyar_PixelFormat)format;
/// <summary>
/// Returns image width.
/// </summary>
- (int)width;
/// <summary>
/// Returns image height.
/// </summary>
- (int)height;
/// <summary>
/// Checks if the image is empty.
/// </summary>
- (bool)empty;

@end
