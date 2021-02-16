//=============================================================================================================================
//
// EasyAR Sense 4.1.0.7750-f1413084f
// Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#import "easyar/types.oc.h"

/// <summary>
/// Signal input port.
/// It is used to expose input port for a component.
/// All members of this class is thread-safe.
/// </summary>
@interface easyar_SignalSink : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// <summary>
/// Input data.
/// </summary>
- (void)handle;

@end

/// <summary>
/// Signal output port.
/// It is used to expose output port for a component.
/// All members of this class is thread-safe.
/// </summary>
@interface easyar_SignalSource : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// <summary>
/// Sets data handler.
/// </summary>
- (void)setHandler:(void (^)())handler;
/// <summary>
/// Connects to input port.
/// </summary>
- (void)connect:(easyar_SignalSink *)sink;
/// <summary>
/// Disconnects.
/// </summary>
- (void)disconnect;

@end

/// <summary>
/// Input frame input port.
/// It is used to expose input port for a component.
/// All members of this class is thread-safe.
/// </summary>
@interface easyar_InputFrameSink : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// <summary>
/// Input data.
/// </summary>
- (void)handle:(easyar_InputFrame *)inputData;

@end

/// <summary>
/// Input frame output port.
/// It is used to expose output port for a component.
/// All members of this class is thread-safe.
/// </summary>
@interface easyar_InputFrameSource : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// <summary>
/// Sets data handler.
/// </summary>
- (void)setHandler:(void (^)(easyar_InputFrame *))handler;
/// <summary>
/// Connects to input port.
/// </summary>
- (void)connect:(easyar_InputFrameSink *)sink;
/// <summary>
/// Disconnects.
/// </summary>
- (void)disconnect;

@end

/// <summary>
/// Output frame input port.
/// It is used to expose input port for a component.
/// All members of this class is thread-safe.
/// </summary>
@interface easyar_OutputFrameSink : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// <summary>
/// Input data.
/// </summary>
- (void)handle:(easyar_OutputFrame *)inputData;

@end

/// <summary>
/// Output frame output port.
/// It is used to expose output port for a component.
/// All members of this class is thread-safe.
/// </summary>
@interface easyar_OutputFrameSource : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// <summary>
/// Sets data handler.
/// </summary>
- (void)setHandler:(void (^)(easyar_OutputFrame *))handler;
/// <summary>
/// Connects to input port.
/// </summary>
- (void)connect:(easyar_OutputFrameSink *)sink;
/// <summary>
/// Disconnects.
/// </summary>
- (void)disconnect;

@end

/// <summary>
/// Feedback frame input port.
/// It is used to expose input port for a component.
/// All members of this class is thread-safe.
/// </summary>
@interface easyar_FeedbackFrameSink : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// <summary>
/// Input data.
/// </summary>
- (void)handle:(easyar_FeedbackFrame *)inputData;

@end

/// <summary>
/// Feedback frame output port.
/// It is used to expose output port for a component.
/// All members of this class is thread-safe.
/// </summary>
@interface easyar_FeedbackFrameSource : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// <summary>
/// Sets data handler.
/// </summary>
- (void)setHandler:(void (^)(easyar_FeedbackFrame *))handler;
/// <summary>
/// Connects to input port.
/// </summary>
- (void)connect:(easyar_FeedbackFrameSink *)sink;
/// <summary>
/// Disconnects.
/// </summary>
- (void)disconnect;

@end

/// <summary>
/// Input frame fork.
/// It is used to branch and transfer input frame to multiple components in parallel.
/// All members of this class is thread-safe.
/// </summary>
@interface easyar_InputFrameFork : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// <summary>
/// Input port.
/// </summary>
- (easyar_InputFrameSink *)input;
/// <summary>
/// Output port.
/// </summary>
- (easyar_InputFrameSource *)output:(int)index;
/// <summary>
/// Output count.
/// </summary>
- (int)outputCount;
/// <summary>
/// Creates an instance.
/// </summary>
+ (easyar_InputFrameFork *)create:(int)outputCount;

@end

/// <summary>
/// Output frame fork.
/// It is used to branch and transfer output frame to multiple components in parallel.
/// All members of this class is thread-safe.
/// </summary>
@interface easyar_OutputFrameFork : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// <summary>
/// Input port.
/// </summary>
- (easyar_OutputFrameSink *)input;
/// <summary>
/// Output port.
/// </summary>
- (easyar_OutputFrameSource *)output:(int)index;
/// <summary>
/// Output count.
/// </summary>
- (int)outputCount;
/// <summary>
/// Creates an instance.
/// </summary>
+ (easyar_OutputFrameFork *)create:(int)outputCount;

@end

/// <summary>
/// Output frame join.
/// It is used to aggregate output frame from multiple components in parallel.
/// All members of this class is thread-safe.
/// It shall be noticed that connections and disconnections to the inputs shall not be performed during the flowing of data, or it may stuck in a state that no frame can be output. (It is recommended to complete dataflow connection before start a camera.)
/// </summary>
@interface easyar_OutputFrameJoin : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// <summary>
/// Input port.
/// </summary>
- (easyar_OutputFrameSink *)input:(int)index;
/// <summary>
/// Output port.
/// </summary>
- (easyar_OutputFrameSource *)output;
/// <summary>
/// Input count.
/// </summary>
- (int)inputCount;
/// <summary>
/// Creates an instance. The default joiner will be used, which takes input frame from the first input and first result or null of each input. The first result of every input will be placed at the corresponding input index of results of the final output frame.
/// </summary>
+ (easyar_OutputFrameJoin *)create:(int)inputCount;
/// <summary>
/// Creates an instance. A custom joiner is specified.
/// </summary>
+ (easyar_OutputFrameJoin *)createWithJoiner:(int)inputCount joiner:(easyar_OutputFrame * (^)(NSArray<easyar_OutputFrame *> *))joiner;

@end

/// <summary>
/// Feedback frame fork.
/// It is used to branch and transfer feedback frame to multiple components in parallel.
/// All members of this class is thread-safe.
/// </summary>
@interface easyar_FeedbackFrameFork : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// <summary>
/// Input port.
/// </summary>
- (easyar_FeedbackFrameSink *)input;
/// <summary>
/// Output port.
/// </summary>
- (easyar_FeedbackFrameSource *)output:(int)index;
/// <summary>
/// Output count.
/// </summary>
- (int)outputCount;
/// <summary>
/// Creates an instance.
/// </summary>
+ (easyar_FeedbackFrameFork *)create:(int)outputCount;

@end

/// <summary>
/// Input frame throttler.
/// There is a input frame input port and a input frame output port. It can be used to prevent incoming frames from entering algorithm components when they have not finished handling previous workload.
/// InputFrameThrottler occupies one buffer of camera. Use setBufferCapacity of camera to set an amount of buffers that is not less than the sum of amount of buffers occupied by all components. Refer to `Overview &lt;Overview.html&gt;`__ .
/// All members of this class is thread-safe.
/// It shall be noticed that connections and disconnections to signalInput shall not be performed during the flowing of data, or it may stuck in a state that no frame can be output. (It is recommended to complete dataflow connection before start a camera.)
/// </summary>
@interface easyar_InputFrameThrottler : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// <summary>
/// Input port.
/// </summary>
- (easyar_InputFrameSink *)input;
/// <summary>
/// Camera buffers occupied in this component.
/// </summary>
- (int)bufferRequirement;
/// <summary>
/// Output port.
/// </summary>
- (easyar_InputFrameSource *)output;
/// <summary>
/// Input port for clearance signal.
/// </summary>
- (easyar_SignalSink *)signalInput;
/// <summary>
/// Creates an instance.
/// </summary>
+ (easyar_InputFrameThrottler *)create;

@end

/// <summary>
/// Output frame buffer.
/// There is an output frame input port and output frame fetching function. It can be used to convert output frame fetching from asynchronous pattern to synchronous polling pattern, which fits frame by frame rendering.
/// OutputFrameBuffer occupies one buffer of camera. Use setBufferCapacity of camera to set an amount of buffers that is not less than the sum of amount of buffers occupied by all components. Refer to `Overview &lt;Overview.html&gt;`__ .
/// All members of this class is thread-safe.
/// </summary>
@interface easyar_OutputFrameBuffer : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// <summary>
/// Input port.
/// </summary>
- (easyar_OutputFrameSink *)input;
/// <summary>
/// Camera buffers occupied in this component.
/// </summary>
- (int)bufferRequirement;
/// <summary>
/// Output port for frame arrival. It can be connected to `InputFrameThrottler.signalInput`_ .
/// </summary>
- (easyar_SignalSource *)signalOutput;
/// <summary>
/// Fetches the most recent `OutputFrame`_ .
/// </summary>
- (easyar_OutputFrame *)peek;
/// <summary>
/// Creates an instance.
/// </summary>
+ (easyar_OutputFrameBuffer *)create;
/// <summary>
/// Pauses output of `OutputFrame`_ . After execution, all results of `OutputFrameBuffer.peek`_ will be empty. `OutputFrameBuffer.signalOutput`_  is not affected.
/// </summary>
- (void)pause;
/// <summary>
/// Resumes output of `OutputFrame`_ .
/// </summary>
- (void)resume;

@end

/// <summary>
/// Input frame to output frame adapter.
/// There is an input frame input port and an output frame output port. It can be used to wrap an input frame into an output frame, which can be used for rendering without an algorithm component. Refer to `Overview &lt;Overview.html&gt;`__ .
/// All members of this class is thread-safe.
/// </summary>
@interface easyar_InputFrameToOutputFrameAdapter : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// <summary>
/// Input port.
/// </summary>
- (easyar_InputFrameSink *)input;
/// <summary>
/// Output port.
/// </summary>
- (easyar_OutputFrameSource *)output;
/// <summary>
/// Creates an instance.
/// </summary>
+ (easyar_InputFrameToOutputFrameAdapter *)create;

@end

/// <summary>
/// Input frame to feedback frame adapter.
/// There is an input frame input port, a historic output frame input port and a feedback frame output port. It can be used to combine an input frame and a historic output frame into a feedback frame, which is required by algorithm components such as `ImageTracker`_ .
/// On every input of an input frame, a feedback frame is generated with a previously input historic feedback frame. If there is no previously input historic feedback frame, it is null in the feedback frame.
/// InputFrameToFeedbackFrameAdapter occupies one buffer of camera. Use setBufferCapacity of camera to set an amount of buffers that is not less than the sum of amount of buffers occupied by all components. Refer to `Overview &lt;Overview.html&gt;`__ .
/// All members of this class is thread-safe.
/// </summary>
@interface easyar_InputFrameToFeedbackFrameAdapter : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// <summary>
/// Input port.
/// </summary>
- (easyar_InputFrameSink *)input;
/// <summary>
/// Camera buffers occupied in this component.
/// </summary>
- (int)bufferRequirement;
/// <summary>
/// Side input port for historic output frame input.
/// </summary>
- (easyar_OutputFrameSink *)sideInput;
/// <summary>
/// Output port.
/// </summary>
- (easyar_FeedbackFrameSource *)output;
/// <summary>
/// Creates an instance.
/// </summary>
+ (easyar_InputFrameToFeedbackFrameAdapter *)create;

@end
