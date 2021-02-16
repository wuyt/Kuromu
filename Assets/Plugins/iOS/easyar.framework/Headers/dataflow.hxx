//=============================================================================================================================
//
// EasyAR Sense 4.1.0.7750-f1413084f
// Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_DATAFLOW_HXX__
#define __EASYAR_DATAFLOW_HXX__

#include "easyar/types.hxx"

namespace easyar {

/// <summary>
/// Signal input port.
/// It is used to expose input port for a component.
/// All members of this class is thread-safe.
/// </summary>
class SignalSink
{
protected:
    easyar_SignalSink * cdata_ ;
    void init_cdata(easyar_SignalSink * cdata);
    virtual SignalSink & operator=(const SignalSink & data) { return *this; } //deleted
public:
    SignalSink(easyar_SignalSink * cdata);
    virtual ~SignalSink();

    SignalSink(const SignalSink & data);
    const easyar_SignalSink * get_cdata() const;
    easyar_SignalSink * get_cdata();

    /// <summary>
    /// Input data.
    /// </summary>
    void handle();
};

/// <summary>
/// Signal output port.
/// It is used to expose output port for a component.
/// All members of this class is thread-safe.
/// </summary>
class SignalSource
{
protected:
    easyar_SignalSource * cdata_ ;
    void init_cdata(easyar_SignalSource * cdata);
    virtual SignalSource & operator=(const SignalSource & data) { return *this; } //deleted
public:
    SignalSource(easyar_SignalSource * cdata);
    virtual ~SignalSource();

    SignalSource(const SignalSource & data);
    const easyar_SignalSource * get_cdata() const;
    easyar_SignalSource * get_cdata();

    /// <summary>
    /// Sets data handler.
    /// </summary>
    void setHandler(OptionalOfFunctorOfVoid handler);
    /// <summary>
    /// Connects to input port.
    /// </summary>
    void connect(SignalSink * sink);
    /// <summary>
    /// Disconnects.
    /// </summary>
    void disconnect();
};

/// <summary>
/// Input frame input port.
/// It is used to expose input port for a component.
/// All members of this class is thread-safe.
/// </summary>
class InputFrameSink
{
protected:
    easyar_InputFrameSink * cdata_ ;
    void init_cdata(easyar_InputFrameSink * cdata);
    virtual InputFrameSink & operator=(const InputFrameSink & data) { return *this; } //deleted
public:
    InputFrameSink(easyar_InputFrameSink * cdata);
    virtual ~InputFrameSink();

    InputFrameSink(const InputFrameSink & data);
    const easyar_InputFrameSink * get_cdata() const;
    easyar_InputFrameSink * get_cdata();

    /// <summary>
    /// Input data.
    /// </summary>
    void handle(InputFrame * inputData);
};

/// <summary>
/// Input frame output port.
/// It is used to expose output port for a component.
/// All members of this class is thread-safe.
/// </summary>
class InputFrameSource
{
protected:
    easyar_InputFrameSource * cdata_ ;
    void init_cdata(easyar_InputFrameSource * cdata);
    virtual InputFrameSource & operator=(const InputFrameSource & data) { return *this; } //deleted
public:
    InputFrameSource(easyar_InputFrameSource * cdata);
    virtual ~InputFrameSource();

    InputFrameSource(const InputFrameSource & data);
    const easyar_InputFrameSource * get_cdata() const;
    easyar_InputFrameSource * get_cdata();

    /// <summary>
    /// Sets data handler.
    /// </summary>
    void setHandler(OptionalOfFunctorOfVoidFromInputFrame handler);
    /// <summary>
    /// Connects to input port.
    /// </summary>
    void connect(InputFrameSink * sink);
    /// <summary>
    /// Disconnects.
    /// </summary>
    void disconnect();
};

/// <summary>
/// Output frame input port.
/// It is used to expose input port for a component.
/// All members of this class is thread-safe.
/// </summary>
class OutputFrameSink
{
protected:
    easyar_OutputFrameSink * cdata_ ;
    void init_cdata(easyar_OutputFrameSink * cdata);
    virtual OutputFrameSink & operator=(const OutputFrameSink & data) { return *this; } //deleted
public:
    OutputFrameSink(easyar_OutputFrameSink * cdata);
    virtual ~OutputFrameSink();

    OutputFrameSink(const OutputFrameSink & data);
    const easyar_OutputFrameSink * get_cdata() const;
    easyar_OutputFrameSink * get_cdata();

    /// <summary>
    /// Input data.
    /// </summary>
    void handle(OutputFrame * inputData);
};

/// <summary>
/// Output frame output port.
/// It is used to expose output port for a component.
/// All members of this class is thread-safe.
/// </summary>
class OutputFrameSource
{
protected:
    easyar_OutputFrameSource * cdata_ ;
    void init_cdata(easyar_OutputFrameSource * cdata);
    virtual OutputFrameSource & operator=(const OutputFrameSource & data) { return *this; } //deleted
public:
    OutputFrameSource(easyar_OutputFrameSource * cdata);
    virtual ~OutputFrameSource();

    OutputFrameSource(const OutputFrameSource & data);
    const easyar_OutputFrameSource * get_cdata() const;
    easyar_OutputFrameSource * get_cdata();

    /// <summary>
    /// Sets data handler.
    /// </summary>
    void setHandler(OptionalOfFunctorOfVoidFromOutputFrame handler);
    /// <summary>
    /// Connects to input port.
    /// </summary>
    void connect(OutputFrameSink * sink);
    /// <summary>
    /// Disconnects.
    /// </summary>
    void disconnect();
};

/// <summary>
/// Feedback frame input port.
/// It is used to expose input port for a component.
/// All members of this class is thread-safe.
/// </summary>
class FeedbackFrameSink
{
protected:
    easyar_FeedbackFrameSink * cdata_ ;
    void init_cdata(easyar_FeedbackFrameSink * cdata);
    virtual FeedbackFrameSink & operator=(const FeedbackFrameSink & data) { return *this; } //deleted
public:
    FeedbackFrameSink(easyar_FeedbackFrameSink * cdata);
    virtual ~FeedbackFrameSink();

    FeedbackFrameSink(const FeedbackFrameSink & data);
    const easyar_FeedbackFrameSink * get_cdata() const;
    easyar_FeedbackFrameSink * get_cdata();

    /// <summary>
    /// Input data.
    /// </summary>
    void handle(FeedbackFrame * inputData);
};

/// <summary>
/// Feedback frame output port.
/// It is used to expose output port for a component.
/// All members of this class is thread-safe.
/// </summary>
class FeedbackFrameSource
{
protected:
    easyar_FeedbackFrameSource * cdata_ ;
    void init_cdata(easyar_FeedbackFrameSource * cdata);
    virtual FeedbackFrameSource & operator=(const FeedbackFrameSource & data) { return *this; } //deleted
public:
    FeedbackFrameSource(easyar_FeedbackFrameSource * cdata);
    virtual ~FeedbackFrameSource();

    FeedbackFrameSource(const FeedbackFrameSource & data);
    const easyar_FeedbackFrameSource * get_cdata() const;
    easyar_FeedbackFrameSource * get_cdata();

    /// <summary>
    /// Sets data handler.
    /// </summary>
    void setHandler(OptionalOfFunctorOfVoidFromFeedbackFrame handler);
    /// <summary>
    /// Connects to input port.
    /// </summary>
    void connect(FeedbackFrameSink * sink);
    /// <summary>
    /// Disconnects.
    /// </summary>
    void disconnect();
};

/// <summary>
/// Input frame fork.
/// It is used to branch and transfer input frame to multiple components in parallel.
/// All members of this class is thread-safe.
/// </summary>
class InputFrameFork
{
protected:
    easyar_InputFrameFork * cdata_ ;
    void init_cdata(easyar_InputFrameFork * cdata);
    virtual InputFrameFork & operator=(const InputFrameFork & data) { return *this; } //deleted
public:
    InputFrameFork(easyar_InputFrameFork * cdata);
    virtual ~InputFrameFork();

    InputFrameFork(const InputFrameFork & data);
    const easyar_InputFrameFork * get_cdata() const;
    easyar_InputFrameFork * get_cdata();

    /// <summary>
    /// Input port.
    /// </summary>
    void input(/* OUT */ InputFrameSink * * Return);
    /// <summary>
    /// Output port.
    /// </summary>
    void output(int index, /* OUT */ InputFrameSource * * Return);
    /// <summary>
    /// Output count.
    /// </summary>
    int outputCount();
    /// <summary>
    /// Creates an instance.
    /// </summary>
    static void create(int outputCount, /* OUT */ InputFrameFork * * Return);
};

/// <summary>
/// Output frame fork.
/// It is used to branch and transfer output frame to multiple components in parallel.
/// All members of this class is thread-safe.
/// </summary>
class OutputFrameFork
{
protected:
    easyar_OutputFrameFork * cdata_ ;
    void init_cdata(easyar_OutputFrameFork * cdata);
    virtual OutputFrameFork & operator=(const OutputFrameFork & data) { return *this; } //deleted
public:
    OutputFrameFork(easyar_OutputFrameFork * cdata);
    virtual ~OutputFrameFork();

    OutputFrameFork(const OutputFrameFork & data);
    const easyar_OutputFrameFork * get_cdata() const;
    easyar_OutputFrameFork * get_cdata();

    /// <summary>
    /// Input port.
    /// </summary>
    void input(/* OUT */ OutputFrameSink * * Return);
    /// <summary>
    /// Output port.
    /// </summary>
    void output(int index, /* OUT */ OutputFrameSource * * Return);
    /// <summary>
    /// Output count.
    /// </summary>
    int outputCount();
    /// <summary>
    /// Creates an instance.
    /// </summary>
    static void create(int outputCount, /* OUT */ OutputFrameFork * * Return);
};

/// <summary>
/// Output frame join.
/// It is used to aggregate output frame from multiple components in parallel.
/// All members of this class is thread-safe.
/// It shall be noticed that connections and disconnections to the inputs shall not be performed during the flowing of data, or it may stuck in a state that no frame can be output. (It is recommended to complete dataflow connection before start a camera.)
/// </summary>
class OutputFrameJoin
{
protected:
    easyar_OutputFrameJoin * cdata_ ;
    void init_cdata(easyar_OutputFrameJoin * cdata);
    virtual OutputFrameJoin & operator=(const OutputFrameJoin & data) { return *this; } //deleted
public:
    OutputFrameJoin(easyar_OutputFrameJoin * cdata);
    virtual ~OutputFrameJoin();

    OutputFrameJoin(const OutputFrameJoin & data);
    const easyar_OutputFrameJoin * get_cdata() const;
    easyar_OutputFrameJoin * get_cdata();

    /// <summary>
    /// Input port.
    /// </summary>
    void input(int index, /* OUT */ OutputFrameSink * * Return);
    /// <summary>
    /// Output port.
    /// </summary>
    void output(/* OUT */ OutputFrameSource * * Return);
    /// <summary>
    /// Input count.
    /// </summary>
    int inputCount();
    /// <summary>
    /// Creates an instance. The default joiner will be used, which takes input frame from the first input and first result or null of each input. The first result of every input will be placed at the corresponding input index of results of the final output frame.
    /// </summary>
    static void create(int inputCount, /* OUT */ OutputFrameJoin * * Return);
    /// <summary>
    /// Creates an instance. A custom joiner is specified.
    /// </summary>
    static void createWithJoiner(int inputCount, FunctorOfOutputFrameFromListOfOutputFrame joiner, /* OUT */ OutputFrameJoin * * Return);
};

/// <summary>
/// Feedback frame fork.
/// It is used to branch and transfer feedback frame to multiple components in parallel.
/// All members of this class is thread-safe.
/// </summary>
class FeedbackFrameFork
{
protected:
    easyar_FeedbackFrameFork * cdata_ ;
    void init_cdata(easyar_FeedbackFrameFork * cdata);
    virtual FeedbackFrameFork & operator=(const FeedbackFrameFork & data) { return *this; } //deleted
public:
    FeedbackFrameFork(easyar_FeedbackFrameFork * cdata);
    virtual ~FeedbackFrameFork();

    FeedbackFrameFork(const FeedbackFrameFork & data);
    const easyar_FeedbackFrameFork * get_cdata() const;
    easyar_FeedbackFrameFork * get_cdata();

    /// <summary>
    /// Input port.
    /// </summary>
    void input(/* OUT */ FeedbackFrameSink * * Return);
    /// <summary>
    /// Output port.
    /// </summary>
    void output(int index, /* OUT */ FeedbackFrameSource * * Return);
    /// <summary>
    /// Output count.
    /// </summary>
    int outputCount();
    /// <summary>
    /// Creates an instance.
    /// </summary>
    static void create(int outputCount, /* OUT */ FeedbackFrameFork * * Return);
};

/// <summary>
/// Input frame throttler.
/// There is a input frame input port and a input frame output port. It can be used to prevent incoming frames from entering algorithm components when they have not finished handling previous workload.
/// InputFrameThrottler occupies one buffer of camera. Use setBufferCapacity of camera to set an amount of buffers that is not less than the sum of amount of buffers occupied by all components. Refer to `Overview &lt;Overview.html&gt;`__ .
/// All members of this class is thread-safe.
/// It shall be noticed that connections and disconnections to signalInput shall not be performed during the flowing of data, or it may stuck in a state that no frame can be output. (It is recommended to complete dataflow connection before start a camera.)
/// </summary>
class InputFrameThrottler
{
protected:
    easyar_InputFrameThrottler * cdata_ ;
    void init_cdata(easyar_InputFrameThrottler * cdata);
    virtual InputFrameThrottler & operator=(const InputFrameThrottler & data) { return *this; } //deleted
public:
    InputFrameThrottler(easyar_InputFrameThrottler * cdata);
    virtual ~InputFrameThrottler();

    InputFrameThrottler(const InputFrameThrottler & data);
    const easyar_InputFrameThrottler * get_cdata() const;
    easyar_InputFrameThrottler * get_cdata();

    /// <summary>
    /// Input port.
    /// </summary>
    void input(/* OUT */ InputFrameSink * * Return);
    /// <summary>
    /// Camera buffers occupied in this component.
    /// </summary>
    int bufferRequirement();
    /// <summary>
    /// Output port.
    /// </summary>
    void output(/* OUT */ InputFrameSource * * Return);
    /// <summary>
    /// Input port for clearance signal.
    /// </summary>
    void signalInput(/* OUT */ SignalSink * * Return);
    /// <summary>
    /// Creates an instance.
    /// </summary>
    static void create(/* OUT */ InputFrameThrottler * * Return);
};

/// <summary>
/// Output frame buffer.
/// There is an output frame input port and output frame fetching function. It can be used to convert output frame fetching from asynchronous pattern to synchronous polling pattern, which fits frame by frame rendering.
/// OutputFrameBuffer occupies one buffer of camera. Use setBufferCapacity of camera to set an amount of buffers that is not less than the sum of amount of buffers occupied by all components. Refer to `Overview &lt;Overview.html&gt;`__ .
/// All members of this class is thread-safe.
/// </summary>
class OutputFrameBuffer
{
protected:
    easyar_OutputFrameBuffer * cdata_ ;
    void init_cdata(easyar_OutputFrameBuffer * cdata);
    virtual OutputFrameBuffer & operator=(const OutputFrameBuffer & data) { return *this; } //deleted
public:
    OutputFrameBuffer(easyar_OutputFrameBuffer * cdata);
    virtual ~OutputFrameBuffer();

    OutputFrameBuffer(const OutputFrameBuffer & data);
    const easyar_OutputFrameBuffer * get_cdata() const;
    easyar_OutputFrameBuffer * get_cdata();

    /// <summary>
    /// Input port.
    /// </summary>
    void input(/* OUT */ OutputFrameSink * * Return);
    /// <summary>
    /// Camera buffers occupied in this component.
    /// </summary>
    int bufferRequirement();
    /// <summary>
    /// Output port for frame arrival. It can be connected to `InputFrameThrottler.signalInput`_ .
    /// </summary>
    void signalOutput(/* OUT */ SignalSource * * Return);
    /// <summary>
    /// Fetches the most recent `OutputFrame`_ .
    /// </summary>
    void peek(/* OUT */ OutputFrame * * Return);
    /// <summary>
    /// Creates an instance.
    /// </summary>
    static void create(/* OUT */ OutputFrameBuffer * * Return);
    /// <summary>
    /// Pauses output of `OutputFrame`_ . After execution, all results of `OutputFrameBuffer.peek`_ will be empty. `OutputFrameBuffer.signalOutput`_  is not affected.
    /// </summary>
    void pause();
    /// <summary>
    /// Resumes output of `OutputFrame`_ .
    /// </summary>
    void resume();
};

/// <summary>
/// Input frame to output frame adapter.
/// There is an input frame input port and an output frame output port. It can be used to wrap an input frame into an output frame, which can be used for rendering without an algorithm component. Refer to `Overview &lt;Overview.html&gt;`__ .
/// All members of this class is thread-safe.
/// </summary>
class InputFrameToOutputFrameAdapter
{
protected:
    easyar_InputFrameToOutputFrameAdapter * cdata_ ;
    void init_cdata(easyar_InputFrameToOutputFrameAdapter * cdata);
    virtual InputFrameToOutputFrameAdapter & operator=(const InputFrameToOutputFrameAdapter & data) { return *this; } //deleted
public:
    InputFrameToOutputFrameAdapter(easyar_InputFrameToOutputFrameAdapter * cdata);
    virtual ~InputFrameToOutputFrameAdapter();

    InputFrameToOutputFrameAdapter(const InputFrameToOutputFrameAdapter & data);
    const easyar_InputFrameToOutputFrameAdapter * get_cdata() const;
    easyar_InputFrameToOutputFrameAdapter * get_cdata();

    /// <summary>
    /// Input port.
    /// </summary>
    void input(/* OUT */ InputFrameSink * * Return);
    /// <summary>
    /// Output port.
    /// </summary>
    void output(/* OUT */ OutputFrameSource * * Return);
    /// <summary>
    /// Creates an instance.
    /// </summary>
    static void create(/* OUT */ InputFrameToOutputFrameAdapter * * Return);
};

/// <summary>
/// Input frame to feedback frame adapter.
/// There is an input frame input port, a historic output frame input port and a feedback frame output port. It can be used to combine an input frame and a historic output frame into a feedback frame, which is required by algorithm components such as `ImageTracker`_ .
/// On every input of an input frame, a feedback frame is generated with a previously input historic feedback frame. If there is no previously input historic feedback frame, it is null in the feedback frame.
/// InputFrameToFeedbackFrameAdapter occupies one buffer of camera. Use setBufferCapacity of camera to set an amount of buffers that is not less than the sum of amount of buffers occupied by all components. Refer to `Overview &lt;Overview.html&gt;`__ .
/// All members of this class is thread-safe.
/// </summary>
class InputFrameToFeedbackFrameAdapter
{
protected:
    easyar_InputFrameToFeedbackFrameAdapter * cdata_ ;
    void init_cdata(easyar_InputFrameToFeedbackFrameAdapter * cdata);
    virtual InputFrameToFeedbackFrameAdapter & operator=(const InputFrameToFeedbackFrameAdapter & data) { return *this; } //deleted
public:
    InputFrameToFeedbackFrameAdapter(easyar_InputFrameToFeedbackFrameAdapter * cdata);
    virtual ~InputFrameToFeedbackFrameAdapter();

    InputFrameToFeedbackFrameAdapter(const InputFrameToFeedbackFrameAdapter & data);
    const easyar_InputFrameToFeedbackFrameAdapter * get_cdata() const;
    easyar_InputFrameToFeedbackFrameAdapter * get_cdata();

    /// <summary>
    /// Input port.
    /// </summary>
    void input(/* OUT */ InputFrameSink * * Return);
    /// <summary>
    /// Camera buffers occupied in this component.
    /// </summary>
    int bufferRequirement();
    /// <summary>
    /// Side input port for historic output frame input.
    /// </summary>
    void sideInput(/* OUT */ OutputFrameSink * * Return);
    /// <summary>
    /// Output port.
    /// </summary>
    void output(/* OUT */ FeedbackFrameSource * * Return);
    /// <summary>
    /// Creates an instance.
    /// </summary>
    static void create(/* OUT */ InputFrameToFeedbackFrameAdapter * * Return);
};

#ifndef __EASYAR_FUNCTOROFVOID__
#define __EASYAR_FUNCTOROFVOID__
struct FunctorOfVoid
{
    void * _state;
    void (* func)(void * _state);
    void (* destroy)(void * _state);
    FunctorOfVoid(void * _state, void (* func)(void * _state), void (* destroy)(void * _state));
};

static void FunctorOfVoid_func(void * _state, /* OUT */ easyar_String * * _exception);
static void FunctorOfVoid_destroy(void * _state);
static inline easyar_FunctorOfVoid FunctorOfVoid_to_c(FunctorOfVoid f);
#endif

#ifndef __EASYAR_OPTIONALOFFUNCTOROFVOID__
#define __EASYAR_OPTIONALOFFUNCTOROFVOID__
struct OptionalOfFunctorOfVoid
{
    bool has_value;
    FunctorOfVoid value;
};
static inline easyar_OptionalOfFunctorOfVoid OptionalOfFunctorOfVoid_to_c(OptionalOfFunctorOfVoid o);
#endif

#ifndef __EASYAR_FUNCTOROFVOIDFROMINPUTFRAME__
#define __EASYAR_FUNCTOROFVOIDFROMINPUTFRAME__
struct FunctorOfVoidFromInputFrame
{
    void * _state;
    void (* func)(void * _state, InputFrame *);
    void (* destroy)(void * _state);
    FunctorOfVoidFromInputFrame(void * _state, void (* func)(void * _state, InputFrame *), void (* destroy)(void * _state));
};

static void FunctorOfVoidFromInputFrame_func(void * _state, easyar_InputFrame *, /* OUT */ easyar_String * * _exception);
static void FunctorOfVoidFromInputFrame_destroy(void * _state);
static inline easyar_FunctorOfVoidFromInputFrame FunctorOfVoidFromInputFrame_to_c(FunctorOfVoidFromInputFrame f);
#endif

#ifndef __EASYAR_OPTIONALOFFUNCTOROFVOIDFROMINPUTFRAME__
#define __EASYAR_OPTIONALOFFUNCTOROFVOIDFROMINPUTFRAME__
struct OptionalOfFunctorOfVoidFromInputFrame
{
    bool has_value;
    FunctorOfVoidFromInputFrame value;
};
static inline easyar_OptionalOfFunctorOfVoidFromInputFrame OptionalOfFunctorOfVoidFromInputFrame_to_c(OptionalOfFunctorOfVoidFromInputFrame o);
#endif

#ifndef __EASYAR_FUNCTOROFVOIDFROMOUTPUTFRAME__
#define __EASYAR_FUNCTOROFVOIDFROMOUTPUTFRAME__
struct FunctorOfVoidFromOutputFrame
{
    void * _state;
    void (* func)(void * _state, OutputFrame *);
    void (* destroy)(void * _state);
    FunctorOfVoidFromOutputFrame(void * _state, void (* func)(void * _state, OutputFrame *), void (* destroy)(void * _state));
};

static void FunctorOfVoidFromOutputFrame_func(void * _state, easyar_OutputFrame *, /* OUT */ easyar_String * * _exception);
static void FunctorOfVoidFromOutputFrame_destroy(void * _state);
static inline easyar_FunctorOfVoidFromOutputFrame FunctorOfVoidFromOutputFrame_to_c(FunctorOfVoidFromOutputFrame f);
#endif

#ifndef __EASYAR_OPTIONALOFFUNCTOROFVOIDFROMOUTPUTFRAME__
#define __EASYAR_OPTIONALOFFUNCTOROFVOIDFROMOUTPUTFRAME__
struct OptionalOfFunctorOfVoidFromOutputFrame
{
    bool has_value;
    FunctorOfVoidFromOutputFrame value;
};
static inline easyar_OptionalOfFunctorOfVoidFromOutputFrame OptionalOfFunctorOfVoidFromOutputFrame_to_c(OptionalOfFunctorOfVoidFromOutputFrame o);
#endif

#ifndef __EASYAR_FUNCTOROFVOIDFROMFEEDBACKFRAME__
#define __EASYAR_FUNCTOROFVOIDFROMFEEDBACKFRAME__
struct FunctorOfVoidFromFeedbackFrame
{
    void * _state;
    void (* func)(void * _state, FeedbackFrame *);
    void (* destroy)(void * _state);
    FunctorOfVoidFromFeedbackFrame(void * _state, void (* func)(void * _state, FeedbackFrame *), void (* destroy)(void * _state));
};

static void FunctorOfVoidFromFeedbackFrame_func(void * _state, easyar_FeedbackFrame *, /* OUT */ easyar_String * * _exception);
static void FunctorOfVoidFromFeedbackFrame_destroy(void * _state);
static inline easyar_FunctorOfVoidFromFeedbackFrame FunctorOfVoidFromFeedbackFrame_to_c(FunctorOfVoidFromFeedbackFrame f);
#endif

#ifndef __EASYAR_OPTIONALOFFUNCTOROFVOIDFROMFEEDBACKFRAME__
#define __EASYAR_OPTIONALOFFUNCTOROFVOIDFROMFEEDBACKFRAME__
struct OptionalOfFunctorOfVoidFromFeedbackFrame
{
    bool has_value;
    FunctorOfVoidFromFeedbackFrame value;
};
static inline easyar_OptionalOfFunctorOfVoidFromFeedbackFrame OptionalOfFunctorOfVoidFromFeedbackFrame_to_c(OptionalOfFunctorOfVoidFromFeedbackFrame o);
#endif

#ifndef __EASYAR_LISTOFOUTPUTFRAME__
#define __EASYAR_LISTOFOUTPUTFRAME__
class ListOfOutputFrame
{
private:
    easyar_ListOfOutputFrame * cdata_;
    virtual ListOfOutputFrame & operator=(const ListOfOutputFrame & data) { return *this; } //deleted
public:
    ListOfOutputFrame(easyar_ListOfOutputFrame * cdata);
    virtual ~ListOfOutputFrame();

    ListOfOutputFrame(const ListOfOutputFrame & data);
    const easyar_ListOfOutputFrame * get_cdata() const;
    easyar_ListOfOutputFrame * get_cdata();

    ListOfOutputFrame(easyar_OutputFrame * * begin, easyar_OutputFrame * * end);
    int size() const;
    OutputFrame * at(int index) const;
};
#endif

#ifndef __EASYAR_FUNCTOROFOUTPUTFRAMEFROMLISTOFOUTPUTFRAME__
#define __EASYAR_FUNCTOROFOUTPUTFRAMEFROMLISTOFOUTPUTFRAME__
struct FunctorOfOutputFrameFromListOfOutputFrame
{
    void * _state;
    void (* func)(void * _state, ListOfOutputFrame *, /* OUT */ OutputFrame * *);
    void (* destroy)(void * _state);
    FunctorOfOutputFrameFromListOfOutputFrame(void * _state, void (* func)(void * _state, ListOfOutputFrame *, /* OUT */ OutputFrame * *), void (* destroy)(void * _state));
};

static void FunctorOfOutputFrameFromListOfOutputFrame_func(void * _state, easyar_ListOfOutputFrame *, /* OUT */ easyar_OutputFrame * *, /* OUT */ easyar_String * * _exception);
static void FunctorOfOutputFrameFromListOfOutputFrame_destroy(void * _state);
static inline easyar_FunctorOfOutputFrameFromListOfOutputFrame FunctorOfOutputFrameFromListOfOutputFrame_to_c(FunctorOfOutputFrameFromListOfOutputFrame f);
#endif

#ifndef __EASYAR_OPTIONALOFOUTPUTFRAME__
#define __EASYAR_OPTIONALOFOUTPUTFRAME__
struct OptionalOfOutputFrame
{
    bool has_value;
    OutputFrame * value;
};
static inline easyar_OptionalOfOutputFrame OptionalOfOutputFrame_to_c(OutputFrame * o);
#endif

}

#endif

#ifndef __IMPLEMENTATION_EASYAR_DATAFLOW_HXX__
#define __IMPLEMENTATION_EASYAR_DATAFLOW_HXX__

#include "easyar/dataflow.h"
#include "easyar/frame.hxx"
#include "easyar/image.hxx"
#include "easyar/buffer.hxx"
#include "easyar/cameraparameters.hxx"
#include "easyar/vector.hxx"
#include "easyar/matrix.hxx"

namespace easyar {

inline SignalSink::SignalSink(easyar_SignalSink * cdata)
    :
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline SignalSink::~SignalSink()
{
    if (cdata_) {
        easyar_SignalSink__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline SignalSink::SignalSink(const SignalSink & data)
    :
    cdata_(NULL)
{
    easyar_SignalSink * cdata = NULL;
    easyar_SignalSink__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_SignalSink * SignalSink::get_cdata() const
{
    return cdata_;
}
inline easyar_SignalSink * SignalSink::get_cdata()
{
    return cdata_;
}
inline void SignalSink::init_cdata(easyar_SignalSink * cdata)
{
    cdata_ = cdata;
}
inline void SignalSink::handle()
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_SignalSink_handle(cdata_);
}

inline SignalSource::SignalSource(easyar_SignalSource * cdata)
    :
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline SignalSource::~SignalSource()
{
    if (cdata_) {
        easyar_SignalSource__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline SignalSource::SignalSource(const SignalSource & data)
    :
    cdata_(NULL)
{
    easyar_SignalSource * cdata = NULL;
    easyar_SignalSource__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_SignalSource * SignalSource::get_cdata() const
{
    return cdata_;
}
inline easyar_SignalSource * SignalSource::get_cdata()
{
    return cdata_;
}
inline void SignalSource::init_cdata(easyar_SignalSource * cdata)
{
    cdata_ = cdata;
}
inline void SignalSource::setHandler(OptionalOfFunctorOfVoid arg0)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_SignalSource_setHandler(cdata_, OptionalOfFunctorOfVoid_to_c(arg0));
}
inline void SignalSource::connect(SignalSink * arg0)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_SignalSource_connect(cdata_, arg0->get_cdata());
}
inline void SignalSource::disconnect()
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_SignalSource_disconnect(cdata_);
}

inline InputFrameSink::InputFrameSink(easyar_InputFrameSink * cdata)
    :
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline InputFrameSink::~InputFrameSink()
{
    if (cdata_) {
        easyar_InputFrameSink__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline InputFrameSink::InputFrameSink(const InputFrameSink & data)
    :
    cdata_(NULL)
{
    easyar_InputFrameSink * cdata = NULL;
    easyar_InputFrameSink__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_InputFrameSink * InputFrameSink::get_cdata() const
{
    return cdata_;
}
inline easyar_InputFrameSink * InputFrameSink::get_cdata()
{
    return cdata_;
}
inline void InputFrameSink::init_cdata(easyar_InputFrameSink * cdata)
{
    cdata_ = cdata;
}
inline void InputFrameSink::handle(InputFrame * arg0)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_InputFrameSink_handle(cdata_, arg0->get_cdata());
}

inline InputFrameSource::InputFrameSource(easyar_InputFrameSource * cdata)
    :
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline InputFrameSource::~InputFrameSource()
{
    if (cdata_) {
        easyar_InputFrameSource__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline InputFrameSource::InputFrameSource(const InputFrameSource & data)
    :
    cdata_(NULL)
{
    easyar_InputFrameSource * cdata = NULL;
    easyar_InputFrameSource__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_InputFrameSource * InputFrameSource::get_cdata() const
{
    return cdata_;
}
inline easyar_InputFrameSource * InputFrameSource::get_cdata()
{
    return cdata_;
}
inline void InputFrameSource::init_cdata(easyar_InputFrameSource * cdata)
{
    cdata_ = cdata;
}
inline void InputFrameSource::setHandler(OptionalOfFunctorOfVoidFromInputFrame arg0)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_InputFrameSource_setHandler(cdata_, OptionalOfFunctorOfVoidFromInputFrame_to_c(arg0));
}
inline void InputFrameSource::connect(InputFrameSink * arg0)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_InputFrameSource_connect(cdata_, arg0->get_cdata());
}
inline void InputFrameSource::disconnect()
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_InputFrameSource_disconnect(cdata_);
}

inline OutputFrameSink::OutputFrameSink(easyar_OutputFrameSink * cdata)
    :
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline OutputFrameSink::~OutputFrameSink()
{
    if (cdata_) {
        easyar_OutputFrameSink__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline OutputFrameSink::OutputFrameSink(const OutputFrameSink & data)
    :
    cdata_(NULL)
{
    easyar_OutputFrameSink * cdata = NULL;
    easyar_OutputFrameSink__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_OutputFrameSink * OutputFrameSink::get_cdata() const
{
    return cdata_;
}
inline easyar_OutputFrameSink * OutputFrameSink::get_cdata()
{
    return cdata_;
}
inline void OutputFrameSink::init_cdata(easyar_OutputFrameSink * cdata)
{
    cdata_ = cdata;
}
inline void OutputFrameSink::handle(OutputFrame * arg0)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_OutputFrameSink_handle(cdata_, arg0->get_cdata());
}

inline OutputFrameSource::OutputFrameSource(easyar_OutputFrameSource * cdata)
    :
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline OutputFrameSource::~OutputFrameSource()
{
    if (cdata_) {
        easyar_OutputFrameSource__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline OutputFrameSource::OutputFrameSource(const OutputFrameSource & data)
    :
    cdata_(NULL)
{
    easyar_OutputFrameSource * cdata = NULL;
    easyar_OutputFrameSource__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_OutputFrameSource * OutputFrameSource::get_cdata() const
{
    return cdata_;
}
inline easyar_OutputFrameSource * OutputFrameSource::get_cdata()
{
    return cdata_;
}
inline void OutputFrameSource::init_cdata(easyar_OutputFrameSource * cdata)
{
    cdata_ = cdata;
}
inline void OutputFrameSource::setHandler(OptionalOfFunctorOfVoidFromOutputFrame arg0)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_OutputFrameSource_setHandler(cdata_, OptionalOfFunctorOfVoidFromOutputFrame_to_c(arg0));
}
inline void OutputFrameSource::connect(OutputFrameSink * arg0)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_OutputFrameSource_connect(cdata_, arg0->get_cdata());
}
inline void OutputFrameSource::disconnect()
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_OutputFrameSource_disconnect(cdata_);
}

inline FeedbackFrameSink::FeedbackFrameSink(easyar_FeedbackFrameSink * cdata)
    :
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline FeedbackFrameSink::~FeedbackFrameSink()
{
    if (cdata_) {
        easyar_FeedbackFrameSink__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline FeedbackFrameSink::FeedbackFrameSink(const FeedbackFrameSink & data)
    :
    cdata_(NULL)
{
    easyar_FeedbackFrameSink * cdata = NULL;
    easyar_FeedbackFrameSink__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_FeedbackFrameSink * FeedbackFrameSink::get_cdata() const
{
    return cdata_;
}
inline easyar_FeedbackFrameSink * FeedbackFrameSink::get_cdata()
{
    return cdata_;
}
inline void FeedbackFrameSink::init_cdata(easyar_FeedbackFrameSink * cdata)
{
    cdata_ = cdata;
}
inline void FeedbackFrameSink::handle(FeedbackFrame * arg0)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_FeedbackFrameSink_handle(cdata_, arg0->get_cdata());
}

inline FeedbackFrameSource::FeedbackFrameSource(easyar_FeedbackFrameSource * cdata)
    :
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline FeedbackFrameSource::~FeedbackFrameSource()
{
    if (cdata_) {
        easyar_FeedbackFrameSource__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline FeedbackFrameSource::FeedbackFrameSource(const FeedbackFrameSource & data)
    :
    cdata_(NULL)
{
    easyar_FeedbackFrameSource * cdata = NULL;
    easyar_FeedbackFrameSource__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_FeedbackFrameSource * FeedbackFrameSource::get_cdata() const
{
    return cdata_;
}
inline easyar_FeedbackFrameSource * FeedbackFrameSource::get_cdata()
{
    return cdata_;
}
inline void FeedbackFrameSource::init_cdata(easyar_FeedbackFrameSource * cdata)
{
    cdata_ = cdata;
}
inline void FeedbackFrameSource::setHandler(OptionalOfFunctorOfVoidFromFeedbackFrame arg0)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_FeedbackFrameSource_setHandler(cdata_, OptionalOfFunctorOfVoidFromFeedbackFrame_to_c(arg0));
}
inline void FeedbackFrameSource::connect(FeedbackFrameSink * arg0)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_FeedbackFrameSource_connect(cdata_, arg0->get_cdata());
}
inline void FeedbackFrameSource::disconnect()
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_FeedbackFrameSource_disconnect(cdata_);
}

inline InputFrameFork::InputFrameFork(easyar_InputFrameFork * cdata)
    :
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline InputFrameFork::~InputFrameFork()
{
    if (cdata_) {
        easyar_InputFrameFork__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline InputFrameFork::InputFrameFork(const InputFrameFork & data)
    :
    cdata_(NULL)
{
    easyar_InputFrameFork * cdata = NULL;
    easyar_InputFrameFork__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_InputFrameFork * InputFrameFork::get_cdata() const
{
    return cdata_;
}
inline easyar_InputFrameFork * InputFrameFork::get_cdata()
{
    return cdata_;
}
inline void InputFrameFork::init_cdata(easyar_InputFrameFork * cdata)
{
    cdata_ = cdata;
}
inline void InputFrameFork::input(/* OUT */ InputFrameSink * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_InputFrameSink * _return_value_ = NULL;
    easyar_InputFrameFork_input(cdata_, &_return_value_);
    *Return = new InputFrameSink(_return_value_);
}
inline void InputFrameFork::output(int arg0, /* OUT */ InputFrameSource * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_InputFrameSource * _return_value_ = NULL;
    easyar_InputFrameFork_output(cdata_, arg0, &_return_value_);
    *Return = new InputFrameSource(_return_value_);
}
inline int InputFrameFork::outputCount()
{
    if (cdata_ == NULL) {
        return int();
    }
    int _return_value_ = easyar_InputFrameFork_outputCount(cdata_);
    return _return_value_;
}
inline void InputFrameFork::create(int arg0, /* OUT */ InputFrameFork * * Return)
{
    easyar_InputFrameFork * _return_value_ = NULL;
    easyar_InputFrameFork_create(arg0, &_return_value_);
    *Return = new InputFrameFork(_return_value_);
}

inline OutputFrameFork::OutputFrameFork(easyar_OutputFrameFork * cdata)
    :
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline OutputFrameFork::~OutputFrameFork()
{
    if (cdata_) {
        easyar_OutputFrameFork__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline OutputFrameFork::OutputFrameFork(const OutputFrameFork & data)
    :
    cdata_(NULL)
{
    easyar_OutputFrameFork * cdata = NULL;
    easyar_OutputFrameFork__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_OutputFrameFork * OutputFrameFork::get_cdata() const
{
    return cdata_;
}
inline easyar_OutputFrameFork * OutputFrameFork::get_cdata()
{
    return cdata_;
}
inline void OutputFrameFork::init_cdata(easyar_OutputFrameFork * cdata)
{
    cdata_ = cdata;
}
inline void OutputFrameFork::input(/* OUT */ OutputFrameSink * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_OutputFrameSink * _return_value_ = NULL;
    easyar_OutputFrameFork_input(cdata_, &_return_value_);
    *Return = new OutputFrameSink(_return_value_);
}
inline void OutputFrameFork::output(int arg0, /* OUT */ OutputFrameSource * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_OutputFrameSource * _return_value_ = NULL;
    easyar_OutputFrameFork_output(cdata_, arg0, &_return_value_);
    *Return = new OutputFrameSource(_return_value_);
}
inline int OutputFrameFork::outputCount()
{
    if (cdata_ == NULL) {
        return int();
    }
    int _return_value_ = easyar_OutputFrameFork_outputCount(cdata_);
    return _return_value_;
}
inline void OutputFrameFork::create(int arg0, /* OUT */ OutputFrameFork * * Return)
{
    easyar_OutputFrameFork * _return_value_ = NULL;
    easyar_OutputFrameFork_create(arg0, &_return_value_);
    *Return = new OutputFrameFork(_return_value_);
}

inline OutputFrameJoin::OutputFrameJoin(easyar_OutputFrameJoin * cdata)
    :
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline OutputFrameJoin::~OutputFrameJoin()
{
    if (cdata_) {
        easyar_OutputFrameJoin__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline OutputFrameJoin::OutputFrameJoin(const OutputFrameJoin & data)
    :
    cdata_(NULL)
{
    easyar_OutputFrameJoin * cdata = NULL;
    easyar_OutputFrameJoin__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_OutputFrameJoin * OutputFrameJoin::get_cdata() const
{
    return cdata_;
}
inline easyar_OutputFrameJoin * OutputFrameJoin::get_cdata()
{
    return cdata_;
}
inline void OutputFrameJoin::init_cdata(easyar_OutputFrameJoin * cdata)
{
    cdata_ = cdata;
}
inline void OutputFrameJoin::input(int arg0, /* OUT */ OutputFrameSink * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_OutputFrameSink * _return_value_ = NULL;
    easyar_OutputFrameJoin_input(cdata_, arg0, &_return_value_);
    *Return = new OutputFrameSink(_return_value_);
}
inline void OutputFrameJoin::output(/* OUT */ OutputFrameSource * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_OutputFrameSource * _return_value_ = NULL;
    easyar_OutputFrameJoin_output(cdata_, &_return_value_);
    *Return = new OutputFrameSource(_return_value_);
}
inline int OutputFrameJoin::inputCount()
{
    if (cdata_ == NULL) {
        return int();
    }
    int _return_value_ = easyar_OutputFrameJoin_inputCount(cdata_);
    return _return_value_;
}
inline void OutputFrameJoin::create(int arg0, /* OUT */ OutputFrameJoin * * Return)
{
    easyar_OutputFrameJoin * _return_value_ = NULL;
    easyar_OutputFrameJoin_create(arg0, &_return_value_);
    *Return = new OutputFrameJoin(_return_value_);
}
inline void OutputFrameJoin::createWithJoiner(int arg0, FunctorOfOutputFrameFromListOfOutputFrame arg1, /* OUT */ OutputFrameJoin * * Return)
{
    easyar_OutputFrameJoin * _return_value_ = NULL;
    easyar_OutputFrameJoin_createWithJoiner(arg0, FunctorOfOutputFrameFromListOfOutputFrame_to_c(arg1), &_return_value_);
    *Return = new OutputFrameJoin(_return_value_);
}

inline FeedbackFrameFork::FeedbackFrameFork(easyar_FeedbackFrameFork * cdata)
    :
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline FeedbackFrameFork::~FeedbackFrameFork()
{
    if (cdata_) {
        easyar_FeedbackFrameFork__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline FeedbackFrameFork::FeedbackFrameFork(const FeedbackFrameFork & data)
    :
    cdata_(NULL)
{
    easyar_FeedbackFrameFork * cdata = NULL;
    easyar_FeedbackFrameFork__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_FeedbackFrameFork * FeedbackFrameFork::get_cdata() const
{
    return cdata_;
}
inline easyar_FeedbackFrameFork * FeedbackFrameFork::get_cdata()
{
    return cdata_;
}
inline void FeedbackFrameFork::init_cdata(easyar_FeedbackFrameFork * cdata)
{
    cdata_ = cdata;
}
inline void FeedbackFrameFork::input(/* OUT */ FeedbackFrameSink * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_FeedbackFrameSink * _return_value_ = NULL;
    easyar_FeedbackFrameFork_input(cdata_, &_return_value_);
    *Return = new FeedbackFrameSink(_return_value_);
}
inline void FeedbackFrameFork::output(int arg0, /* OUT */ FeedbackFrameSource * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_FeedbackFrameSource * _return_value_ = NULL;
    easyar_FeedbackFrameFork_output(cdata_, arg0, &_return_value_);
    *Return = new FeedbackFrameSource(_return_value_);
}
inline int FeedbackFrameFork::outputCount()
{
    if (cdata_ == NULL) {
        return int();
    }
    int _return_value_ = easyar_FeedbackFrameFork_outputCount(cdata_);
    return _return_value_;
}
inline void FeedbackFrameFork::create(int arg0, /* OUT */ FeedbackFrameFork * * Return)
{
    easyar_FeedbackFrameFork * _return_value_ = NULL;
    easyar_FeedbackFrameFork_create(arg0, &_return_value_);
    *Return = new FeedbackFrameFork(_return_value_);
}

inline InputFrameThrottler::InputFrameThrottler(easyar_InputFrameThrottler * cdata)
    :
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline InputFrameThrottler::~InputFrameThrottler()
{
    if (cdata_) {
        easyar_InputFrameThrottler__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline InputFrameThrottler::InputFrameThrottler(const InputFrameThrottler & data)
    :
    cdata_(NULL)
{
    easyar_InputFrameThrottler * cdata = NULL;
    easyar_InputFrameThrottler__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_InputFrameThrottler * InputFrameThrottler::get_cdata() const
{
    return cdata_;
}
inline easyar_InputFrameThrottler * InputFrameThrottler::get_cdata()
{
    return cdata_;
}
inline void InputFrameThrottler::init_cdata(easyar_InputFrameThrottler * cdata)
{
    cdata_ = cdata;
}
inline void InputFrameThrottler::input(/* OUT */ InputFrameSink * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_InputFrameSink * _return_value_ = NULL;
    easyar_InputFrameThrottler_input(cdata_, &_return_value_);
    *Return = new InputFrameSink(_return_value_);
}
inline int InputFrameThrottler::bufferRequirement()
{
    if (cdata_ == NULL) {
        return int();
    }
    int _return_value_ = easyar_InputFrameThrottler_bufferRequirement(cdata_);
    return _return_value_;
}
inline void InputFrameThrottler::output(/* OUT */ InputFrameSource * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_InputFrameSource * _return_value_ = NULL;
    easyar_InputFrameThrottler_output(cdata_, &_return_value_);
    *Return = new InputFrameSource(_return_value_);
}
inline void InputFrameThrottler::signalInput(/* OUT */ SignalSink * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_SignalSink * _return_value_ = NULL;
    easyar_InputFrameThrottler_signalInput(cdata_, &_return_value_);
    *Return = new SignalSink(_return_value_);
}
inline void InputFrameThrottler::create(/* OUT */ InputFrameThrottler * * Return)
{
    easyar_InputFrameThrottler * _return_value_ = NULL;
    easyar_InputFrameThrottler_create(&_return_value_);
    *Return = new InputFrameThrottler(_return_value_);
}

inline OutputFrameBuffer::OutputFrameBuffer(easyar_OutputFrameBuffer * cdata)
    :
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline OutputFrameBuffer::~OutputFrameBuffer()
{
    if (cdata_) {
        easyar_OutputFrameBuffer__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline OutputFrameBuffer::OutputFrameBuffer(const OutputFrameBuffer & data)
    :
    cdata_(NULL)
{
    easyar_OutputFrameBuffer * cdata = NULL;
    easyar_OutputFrameBuffer__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_OutputFrameBuffer * OutputFrameBuffer::get_cdata() const
{
    return cdata_;
}
inline easyar_OutputFrameBuffer * OutputFrameBuffer::get_cdata()
{
    return cdata_;
}
inline void OutputFrameBuffer::init_cdata(easyar_OutputFrameBuffer * cdata)
{
    cdata_ = cdata;
}
inline void OutputFrameBuffer::input(/* OUT */ OutputFrameSink * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_OutputFrameSink * _return_value_ = NULL;
    easyar_OutputFrameBuffer_input(cdata_, &_return_value_);
    *Return = new OutputFrameSink(_return_value_);
}
inline int OutputFrameBuffer::bufferRequirement()
{
    if (cdata_ == NULL) {
        return int();
    }
    int _return_value_ = easyar_OutputFrameBuffer_bufferRequirement(cdata_);
    return _return_value_;
}
inline void OutputFrameBuffer::signalOutput(/* OUT */ SignalSource * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_SignalSource * _return_value_ = NULL;
    easyar_OutputFrameBuffer_signalOutput(cdata_, &_return_value_);
    *Return = new SignalSource(_return_value_);
}
inline void OutputFrameBuffer::peek(/* OUT */ OutputFrame * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_OptionalOfOutputFrame _return_value_ = {false, NULL};
    easyar_OutputFrameBuffer_peek(cdata_, &_return_value_);
    *Return = (_return_value_.has_value ? new OutputFrame(_return_value_.value) : NULL);
}
inline void OutputFrameBuffer::create(/* OUT */ OutputFrameBuffer * * Return)
{
    easyar_OutputFrameBuffer * _return_value_ = NULL;
    easyar_OutputFrameBuffer_create(&_return_value_);
    *Return = new OutputFrameBuffer(_return_value_);
}
inline void OutputFrameBuffer::pause()
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_OutputFrameBuffer_pause(cdata_);
}
inline void OutputFrameBuffer::resume()
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_OutputFrameBuffer_resume(cdata_);
}

inline InputFrameToOutputFrameAdapter::InputFrameToOutputFrameAdapter(easyar_InputFrameToOutputFrameAdapter * cdata)
    :
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline InputFrameToOutputFrameAdapter::~InputFrameToOutputFrameAdapter()
{
    if (cdata_) {
        easyar_InputFrameToOutputFrameAdapter__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline InputFrameToOutputFrameAdapter::InputFrameToOutputFrameAdapter(const InputFrameToOutputFrameAdapter & data)
    :
    cdata_(NULL)
{
    easyar_InputFrameToOutputFrameAdapter * cdata = NULL;
    easyar_InputFrameToOutputFrameAdapter__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_InputFrameToOutputFrameAdapter * InputFrameToOutputFrameAdapter::get_cdata() const
{
    return cdata_;
}
inline easyar_InputFrameToOutputFrameAdapter * InputFrameToOutputFrameAdapter::get_cdata()
{
    return cdata_;
}
inline void InputFrameToOutputFrameAdapter::init_cdata(easyar_InputFrameToOutputFrameAdapter * cdata)
{
    cdata_ = cdata;
}
inline void InputFrameToOutputFrameAdapter::input(/* OUT */ InputFrameSink * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_InputFrameSink * _return_value_ = NULL;
    easyar_InputFrameToOutputFrameAdapter_input(cdata_, &_return_value_);
    *Return = new InputFrameSink(_return_value_);
}
inline void InputFrameToOutputFrameAdapter::output(/* OUT */ OutputFrameSource * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_OutputFrameSource * _return_value_ = NULL;
    easyar_InputFrameToOutputFrameAdapter_output(cdata_, &_return_value_);
    *Return = new OutputFrameSource(_return_value_);
}
inline void InputFrameToOutputFrameAdapter::create(/* OUT */ InputFrameToOutputFrameAdapter * * Return)
{
    easyar_InputFrameToOutputFrameAdapter * _return_value_ = NULL;
    easyar_InputFrameToOutputFrameAdapter_create(&_return_value_);
    *Return = new InputFrameToOutputFrameAdapter(_return_value_);
}

inline InputFrameToFeedbackFrameAdapter::InputFrameToFeedbackFrameAdapter(easyar_InputFrameToFeedbackFrameAdapter * cdata)
    :
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline InputFrameToFeedbackFrameAdapter::~InputFrameToFeedbackFrameAdapter()
{
    if (cdata_) {
        easyar_InputFrameToFeedbackFrameAdapter__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline InputFrameToFeedbackFrameAdapter::InputFrameToFeedbackFrameAdapter(const InputFrameToFeedbackFrameAdapter & data)
    :
    cdata_(NULL)
{
    easyar_InputFrameToFeedbackFrameAdapter * cdata = NULL;
    easyar_InputFrameToFeedbackFrameAdapter__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_InputFrameToFeedbackFrameAdapter * InputFrameToFeedbackFrameAdapter::get_cdata() const
{
    return cdata_;
}
inline easyar_InputFrameToFeedbackFrameAdapter * InputFrameToFeedbackFrameAdapter::get_cdata()
{
    return cdata_;
}
inline void InputFrameToFeedbackFrameAdapter::init_cdata(easyar_InputFrameToFeedbackFrameAdapter * cdata)
{
    cdata_ = cdata;
}
inline void InputFrameToFeedbackFrameAdapter::input(/* OUT */ InputFrameSink * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_InputFrameSink * _return_value_ = NULL;
    easyar_InputFrameToFeedbackFrameAdapter_input(cdata_, &_return_value_);
    *Return = new InputFrameSink(_return_value_);
}
inline int InputFrameToFeedbackFrameAdapter::bufferRequirement()
{
    if (cdata_ == NULL) {
        return int();
    }
    int _return_value_ = easyar_InputFrameToFeedbackFrameAdapter_bufferRequirement(cdata_);
    return _return_value_;
}
inline void InputFrameToFeedbackFrameAdapter::sideInput(/* OUT */ OutputFrameSink * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_OutputFrameSink * _return_value_ = NULL;
    easyar_InputFrameToFeedbackFrameAdapter_sideInput(cdata_, &_return_value_);
    *Return = new OutputFrameSink(_return_value_);
}
inline void InputFrameToFeedbackFrameAdapter::output(/* OUT */ FeedbackFrameSource * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_FeedbackFrameSource * _return_value_ = NULL;
    easyar_InputFrameToFeedbackFrameAdapter_output(cdata_, &_return_value_);
    *Return = new FeedbackFrameSource(_return_value_);
}
inline void InputFrameToFeedbackFrameAdapter::create(/* OUT */ InputFrameToFeedbackFrameAdapter * * Return)
{
    easyar_InputFrameToFeedbackFrameAdapter * _return_value_ = NULL;
    easyar_InputFrameToFeedbackFrameAdapter_create(&_return_value_);
    *Return = new InputFrameToFeedbackFrameAdapter(_return_value_);
}

#ifndef __IMPLEMENTATION_EASYAR_OPTIONALOFFUNCTOROFVOID__
#define __IMPLEMENTATION_EASYAR_OPTIONALOFFUNCTOROFVOID__
static inline easyar_OptionalOfFunctorOfVoid OptionalOfFunctorOfVoid_to_c(OptionalOfFunctorOfVoid o)
{
    if (o.has_value) {
        easyar_OptionalOfFunctorOfVoid _return_value_ = {true, FunctorOfVoid_to_c(o.value)};
        return _return_value_;
    } else {
        easyar_OptionalOfFunctorOfVoid _return_value_ = {false, {NULL, NULL, NULL}};
        return _return_value_;
    }
}
#endif

#ifndef __IMPLEMENTATION_EASYAR_FUNCTOROFVOID__
#define __IMPLEMENTATION_EASYAR_FUNCTOROFVOID__
inline FunctorOfVoid::FunctorOfVoid(void * _state, void (* func)(void * _state), void (* destroy)(void * _state))
{
    this->_state = _state;
    this->func = func;
    this->destroy = destroy;
}
static void FunctorOfVoid_func(void * _state, /* OUT */ easyar_String * * _exception)
{
    *_exception = NULL;
    try {
        FunctorOfVoid * f = reinterpret_cast<FunctorOfVoid *>(_state);
        f->func(f->_state);
    } catch (std::exception & ex) {
        easyar_String_from_utf8_begin(ex.what(), _exception);
    }
}
static void FunctorOfVoid_destroy(void * _state)
{
    FunctorOfVoid * f = reinterpret_cast<FunctorOfVoid *>(_state);
    if (f->destroy) {
        f->destroy(f->_state);
    }
    delete f;
}
static inline easyar_FunctorOfVoid FunctorOfVoid_to_c(FunctorOfVoid f)
{
    easyar_FunctorOfVoid _return_value_ = {NULL, NULL, NULL};
    _return_value_._state = new FunctorOfVoid(f._state, f.func, f.destroy);
    _return_value_.func = FunctorOfVoid_func;
    _return_value_.destroy = FunctorOfVoid_destroy;
    return _return_value_;
}
#endif

#ifndef __IMPLEMENTATION_EASYAR_OPTIONALOFFUNCTOROFVOIDFROMINPUTFRAME__
#define __IMPLEMENTATION_EASYAR_OPTIONALOFFUNCTOROFVOIDFROMINPUTFRAME__
static inline easyar_OptionalOfFunctorOfVoidFromInputFrame OptionalOfFunctorOfVoidFromInputFrame_to_c(OptionalOfFunctorOfVoidFromInputFrame o)
{
    if (o.has_value) {
        easyar_OptionalOfFunctorOfVoidFromInputFrame _return_value_ = {true, FunctorOfVoidFromInputFrame_to_c(o.value)};
        return _return_value_;
    } else {
        easyar_OptionalOfFunctorOfVoidFromInputFrame _return_value_ = {false, {NULL, NULL, NULL}};
        return _return_value_;
    }
}
#endif

#ifndef __IMPLEMENTATION_EASYAR_FUNCTOROFVOIDFROMINPUTFRAME__
#define __IMPLEMENTATION_EASYAR_FUNCTOROFVOIDFROMINPUTFRAME__
inline FunctorOfVoidFromInputFrame::FunctorOfVoidFromInputFrame(void * _state, void (* func)(void * _state, InputFrame *), void (* destroy)(void * _state))
{
    this->_state = _state;
    this->func = func;
    this->destroy = destroy;
}
static void FunctorOfVoidFromInputFrame_func(void * _state, easyar_InputFrame * arg0, /* OUT */ easyar_String * * _exception)
{
    *_exception = NULL;
    try {
        easyar_InputFrame__retain(arg0, &arg0);
        InputFrame * cpparg0 = new InputFrame(arg0);
        FunctorOfVoidFromInputFrame * f = reinterpret_cast<FunctorOfVoidFromInputFrame *>(_state);
        f->func(f->_state, cpparg0);
        delete cpparg0;
    } catch (std::exception & ex) {
        easyar_String_from_utf8_begin(ex.what(), _exception);
    }
}
static void FunctorOfVoidFromInputFrame_destroy(void * _state)
{
    FunctorOfVoidFromInputFrame * f = reinterpret_cast<FunctorOfVoidFromInputFrame *>(_state);
    if (f->destroy) {
        f->destroy(f->_state);
    }
    delete f;
}
static inline easyar_FunctorOfVoidFromInputFrame FunctorOfVoidFromInputFrame_to_c(FunctorOfVoidFromInputFrame f)
{
    easyar_FunctorOfVoidFromInputFrame _return_value_ = {NULL, NULL, NULL};
    _return_value_._state = new FunctorOfVoidFromInputFrame(f._state, f.func, f.destroy);
    _return_value_.func = FunctorOfVoidFromInputFrame_func;
    _return_value_.destroy = FunctorOfVoidFromInputFrame_destroy;
    return _return_value_;
}
#endif

#ifndef __IMPLEMENTATION_EASYAR_OPTIONALOFFUNCTOROFVOIDFROMOUTPUTFRAME__
#define __IMPLEMENTATION_EASYAR_OPTIONALOFFUNCTOROFVOIDFROMOUTPUTFRAME__
static inline easyar_OptionalOfFunctorOfVoidFromOutputFrame OptionalOfFunctorOfVoidFromOutputFrame_to_c(OptionalOfFunctorOfVoidFromOutputFrame o)
{
    if (o.has_value) {
        easyar_OptionalOfFunctorOfVoidFromOutputFrame _return_value_ = {true, FunctorOfVoidFromOutputFrame_to_c(o.value)};
        return _return_value_;
    } else {
        easyar_OptionalOfFunctorOfVoidFromOutputFrame _return_value_ = {false, {NULL, NULL, NULL}};
        return _return_value_;
    }
}
#endif

#ifndef __IMPLEMENTATION_EASYAR_FUNCTOROFVOIDFROMOUTPUTFRAME__
#define __IMPLEMENTATION_EASYAR_FUNCTOROFVOIDFROMOUTPUTFRAME__
inline FunctorOfVoidFromOutputFrame::FunctorOfVoidFromOutputFrame(void * _state, void (* func)(void * _state, OutputFrame *), void (* destroy)(void * _state))
{
    this->_state = _state;
    this->func = func;
    this->destroy = destroy;
}
static void FunctorOfVoidFromOutputFrame_func(void * _state, easyar_OutputFrame * arg0, /* OUT */ easyar_String * * _exception)
{
    *_exception = NULL;
    try {
        easyar_OutputFrame__retain(arg0, &arg0);
        OutputFrame * cpparg0 = new OutputFrame(arg0);
        FunctorOfVoidFromOutputFrame * f = reinterpret_cast<FunctorOfVoidFromOutputFrame *>(_state);
        f->func(f->_state, cpparg0);
        delete cpparg0;
    } catch (std::exception & ex) {
        easyar_String_from_utf8_begin(ex.what(), _exception);
    }
}
static void FunctorOfVoidFromOutputFrame_destroy(void * _state)
{
    FunctorOfVoidFromOutputFrame * f = reinterpret_cast<FunctorOfVoidFromOutputFrame *>(_state);
    if (f->destroy) {
        f->destroy(f->_state);
    }
    delete f;
}
static inline easyar_FunctorOfVoidFromOutputFrame FunctorOfVoidFromOutputFrame_to_c(FunctorOfVoidFromOutputFrame f)
{
    easyar_FunctorOfVoidFromOutputFrame _return_value_ = {NULL, NULL, NULL};
    _return_value_._state = new FunctorOfVoidFromOutputFrame(f._state, f.func, f.destroy);
    _return_value_.func = FunctorOfVoidFromOutputFrame_func;
    _return_value_.destroy = FunctorOfVoidFromOutputFrame_destroy;
    return _return_value_;
}
#endif

#ifndef __IMPLEMENTATION_EASYAR_OPTIONALOFFUNCTOROFVOIDFROMFEEDBACKFRAME__
#define __IMPLEMENTATION_EASYAR_OPTIONALOFFUNCTOROFVOIDFROMFEEDBACKFRAME__
static inline easyar_OptionalOfFunctorOfVoidFromFeedbackFrame OptionalOfFunctorOfVoidFromFeedbackFrame_to_c(OptionalOfFunctorOfVoidFromFeedbackFrame o)
{
    if (o.has_value) {
        easyar_OptionalOfFunctorOfVoidFromFeedbackFrame _return_value_ = {true, FunctorOfVoidFromFeedbackFrame_to_c(o.value)};
        return _return_value_;
    } else {
        easyar_OptionalOfFunctorOfVoidFromFeedbackFrame _return_value_ = {false, {NULL, NULL, NULL}};
        return _return_value_;
    }
}
#endif

#ifndef __IMPLEMENTATION_EASYAR_FUNCTOROFVOIDFROMFEEDBACKFRAME__
#define __IMPLEMENTATION_EASYAR_FUNCTOROFVOIDFROMFEEDBACKFRAME__
inline FunctorOfVoidFromFeedbackFrame::FunctorOfVoidFromFeedbackFrame(void * _state, void (* func)(void * _state, FeedbackFrame *), void (* destroy)(void * _state))
{
    this->_state = _state;
    this->func = func;
    this->destroy = destroy;
}
static void FunctorOfVoidFromFeedbackFrame_func(void * _state, easyar_FeedbackFrame * arg0, /* OUT */ easyar_String * * _exception)
{
    *_exception = NULL;
    try {
        easyar_FeedbackFrame__retain(arg0, &arg0);
        FeedbackFrame * cpparg0 = new FeedbackFrame(arg0);
        FunctorOfVoidFromFeedbackFrame * f = reinterpret_cast<FunctorOfVoidFromFeedbackFrame *>(_state);
        f->func(f->_state, cpparg0);
        delete cpparg0;
    } catch (std::exception & ex) {
        easyar_String_from_utf8_begin(ex.what(), _exception);
    }
}
static void FunctorOfVoidFromFeedbackFrame_destroy(void * _state)
{
    FunctorOfVoidFromFeedbackFrame * f = reinterpret_cast<FunctorOfVoidFromFeedbackFrame *>(_state);
    if (f->destroy) {
        f->destroy(f->_state);
    }
    delete f;
}
static inline easyar_FunctorOfVoidFromFeedbackFrame FunctorOfVoidFromFeedbackFrame_to_c(FunctorOfVoidFromFeedbackFrame f)
{
    easyar_FunctorOfVoidFromFeedbackFrame _return_value_ = {NULL, NULL, NULL};
    _return_value_._state = new FunctorOfVoidFromFeedbackFrame(f._state, f.func, f.destroy);
    _return_value_.func = FunctorOfVoidFromFeedbackFrame_func;
    _return_value_.destroy = FunctorOfVoidFromFeedbackFrame_destroy;
    return _return_value_;
}
#endif

#ifndef __IMPLEMENTATION_EASYAR_FUNCTOROFOUTPUTFRAMEFROMLISTOFOUTPUTFRAME__
#define __IMPLEMENTATION_EASYAR_FUNCTOROFOUTPUTFRAMEFROMLISTOFOUTPUTFRAME__
inline FunctorOfOutputFrameFromListOfOutputFrame::FunctorOfOutputFrameFromListOfOutputFrame(void * _state, void (* func)(void * _state, ListOfOutputFrame *, /* OUT */ OutputFrame * *), void (* destroy)(void * _state))
{
    this->_state = _state;
    this->func = func;
    this->destroy = destroy;
}
static void FunctorOfOutputFrameFromListOfOutputFrame_func(void * _state, easyar_ListOfOutputFrame * arg0, /* OUT */ easyar_OutputFrame * * Return, /* OUT */ easyar_String * * _exception)
{
    *_exception = NULL;
    try {
        easyar_ListOfOutputFrame_copy(arg0, &arg0);
        ListOfOutputFrame * cpparg0 = new ListOfOutputFrame(arg0);
        FunctorOfOutputFrameFromListOfOutputFrame * f = reinterpret_cast<FunctorOfOutputFrameFromListOfOutputFrame *>(_state);
        OutputFrame * _return_value_;
        f->func(f->_state, cpparg0, &_return_value_);
        easyar_OutputFrame * _return_value_c_ = _return_value_->get_cdata();
        easyar_OutputFrame__retain(_return_value_c_, &_return_value_c_);
        *Return = _return_value_c_;
        delete cpparg0;
    } catch (std::exception & ex) {
        easyar_String_from_utf8_begin(ex.what(), _exception);
    }
}
static void FunctorOfOutputFrameFromListOfOutputFrame_destroy(void * _state)
{
    FunctorOfOutputFrameFromListOfOutputFrame * f = reinterpret_cast<FunctorOfOutputFrameFromListOfOutputFrame *>(_state);
    if (f->destroy) {
        f->destroy(f->_state);
    }
    delete f;
}
static inline easyar_FunctorOfOutputFrameFromListOfOutputFrame FunctorOfOutputFrameFromListOfOutputFrame_to_c(FunctorOfOutputFrameFromListOfOutputFrame f)
{
    easyar_FunctorOfOutputFrameFromListOfOutputFrame _return_value_ = {NULL, NULL, NULL};
    _return_value_._state = new FunctorOfOutputFrameFromListOfOutputFrame(f._state, f.func, f.destroy);
    _return_value_.func = FunctorOfOutputFrameFromListOfOutputFrame_func;
    _return_value_.destroy = FunctorOfOutputFrameFromListOfOutputFrame_destroy;
    return _return_value_;
}
#endif

#ifndef __IMPLEMENTATION_EASYAR_LISTOFOUTPUTFRAME__
#define __IMPLEMENTATION_EASYAR_LISTOFOUTPUTFRAME__
inline ListOfOutputFrame::ListOfOutputFrame(easyar_ListOfOutputFrame * cdata)
    : cdata_(cdata)
{
}
inline ListOfOutputFrame::~ListOfOutputFrame()
{
    if (cdata_) {
        easyar_ListOfOutputFrame__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline ListOfOutputFrame::ListOfOutputFrame(const ListOfOutputFrame & data)
    : cdata_(static_cast<easyar_ListOfOutputFrame *>(NULL))
{
    easyar_ListOfOutputFrame_copy(data.cdata_, &cdata_);
}
inline const easyar_ListOfOutputFrame * ListOfOutputFrame::get_cdata() const
{
    return cdata_;
}
inline easyar_ListOfOutputFrame * ListOfOutputFrame::get_cdata()
{
    return cdata_;
}

inline ListOfOutputFrame::ListOfOutputFrame(easyar_OutputFrame * * begin, easyar_OutputFrame * * end)
    : cdata_(static_cast<easyar_ListOfOutputFrame *>(NULL))
{
    easyar_ListOfOutputFrame__ctor(begin, end, &cdata_);
}
inline int ListOfOutputFrame::size() const
{
    return easyar_ListOfOutputFrame_size(cdata_);
}
inline OutputFrame * ListOfOutputFrame::at(int index) const
{
    easyar_OutputFrame * _return_value_ = easyar_ListOfOutputFrame_at(cdata_, index);
    easyar_OutputFrame__retain(_return_value_, &_return_value_);
    return new OutputFrame(_return_value_);
}
#endif

#ifndef __IMPLEMENTATION_EASYAR_OPTIONALOFOUTPUTFRAME__
#define __IMPLEMENTATION_EASYAR_OPTIONALOFOUTPUTFRAME__
static inline easyar_OptionalOfOutputFrame OptionalOfOutputFrame_to_c(OutputFrame * o)
{
    if (o != NULL) {
        easyar_OptionalOfOutputFrame _return_value_ = {true, o->get_cdata()};
        return _return_value_;
    } else {
        easyar_OptionalOfOutputFrame _return_value_ = {false, NULL};
        return _return_value_;
    }
}
#endif

}

#endif
