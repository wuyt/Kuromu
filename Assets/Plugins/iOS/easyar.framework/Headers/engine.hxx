//=============================================================================================================================
//
// EasyAR Sense 4.1.0.7750-f1413084f
// Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_ENGINE_HXX__
#define __EASYAR_ENGINE_HXX__

#include "easyar/types.hxx"

namespace easyar {

class Engine
{
public:
    /// <summary>
    /// Gets the version schema hash, which can be used to ensure type declarations consistent with runtime library.
    /// </summary>
    static int schemaHash();
    static bool initialize(String * key);
    /// <summary>
    /// Handles the app onPause, pauses internal tasks.
    /// </summary>
    static void onPause();
    /// <summary>
    /// Handles the app onResume, resumes internal tasks.
    /// </summary>
    static void onResume();
    /// <summary>
    /// Gets error message on initialization failure.
    /// </summary>
    static void errorMessage(/* OUT */ String * * Return);
    /// <summary>
    /// Gets the version number of EasyARSense.
    /// </summary>
    static void versionString(/* OUT */ String * * Return);
    /// <summary>
    /// Gets the product name of EasyARSense. (Including variant, operating system and CPU architecture.)
    /// </summary>
    static void name(/* OUT */ String * * Return);
};

}

#endif

#ifndef __IMPLEMENTATION_EASYAR_ENGINE_HXX__
#define __IMPLEMENTATION_EASYAR_ENGINE_HXX__

#include "easyar/engine.h"

namespace easyar {

inline int Engine::schemaHash()
{
    int _return_value_ = easyar_Engine_schemaHash();
    return _return_value_;
}
inline bool Engine::initialize(String * arg0)
{
    if (easyar_Engine_schemaHash() != 2058628672) {
        return false;
    }
    bool _return_value_ = easyar_Engine_initialize(arg0->get_cdata());
    return _return_value_;
}
inline void Engine::onPause()
{
    easyar_Engine_onPause();
}
inline void Engine::onResume()
{
    easyar_Engine_onResume();
}
inline void Engine::errorMessage(/* OUT */ String * * Return)
{
    easyar_String * _return_value_ = NULL;
    easyar_Engine_errorMessage(&_return_value_);
    *Return = new String(_return_value_);
}
inline void Engine::versionString(/* OUT */ String * * Return)
{
    easyar_String * _return_value_ = NULL;
    easyar_Engine_versionString(&_return_value_);
    *Return = new String(_return_value_);
}
inline void Engine::name(/* OUT */ String * * Return)
{
    easyar_String * _return_value_ = NULL;
    easyar_Engine_name(&_return_value_);
    *Return = new String(_return_value_);
}

}

#endif
