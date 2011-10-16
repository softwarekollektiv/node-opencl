#include "commandqueue.hpp"

#include <iostream>

v8::Persistent<v8::FunctionTemplate> CommandQueue::constructor;

CommandQueue::CommandQueue(cl::CommandQueue *commandQueue) {
    _commandQueue = commandQueue;
}

v8::Handle<v8::Value> CommandQueue::New(const v8::Arguments& args) {
    v8::HandleScope scope;
    Context *context = ObjectWrap::Unwrap<Context>(args[0]->ToObject());
    Device *device = ObjectWrap::Unwrap<Device>(args[1]->ToObject());
    cl_int err;
    cl::CommandQueue *queue = new cl::CommandQueue(*context->_context, *device->_device, 0, &err);
    if(err != CL_SUCCESS) {
        //std::cout << "commandQueue error: " << err << std::endl;
        return v8::ThrowException(v8::Exception::Error(v8::String::New("Error in CommandQueue() constructor")));
    }
    CommandQueue *k = new CommandQueue(queue);
    k->Wrap(args.This());
    return args.This();
}

v8::Handle<v8::Value> CommandQueue::Finish(const v8::Arguments& args) {
    v8::HandleScope scope;
    CommandQueue *queue = ObjectWrap::Unwrap<CommandQueue>(args.This());
    cl_int err = queue->_commandQueue->finish();
    return scope.Close(v8::Integer::New(err));
}

static cl::NDRange arrayToNDRange(v8::Local<v8::Array> array) {
    if(array->Length() == 0) {
        return cl::NullRange;
    } else if(array->Length() == 1) {
        return cl::NDRange(array->Get(v8::Integer::New(0))->IntegerValue());
    } else if(array->Length() == 2) {
        return cl::NDRange(array->Get(v8::Integer::New(0))->IntegerValue(),array->Get(v8::Integer::New(1))->IntegerValue());
    } else {
        return cl::NDRange(array->Get(v8::Integer::New(0))->IntegerValue(),array->Get(v8::Integer::New(1))->IntegerValue(),array->Get(v8::Integer::New(2))->IntegerValue());
    }
}

v8::Handle<v8::Value> CommandQueue::EnqueueNDRangeKernel(const v8::Arguments& args) {
    v8::HandleScope scope;
    CommandQueue *queue = ObjectWrap::Unwrap<CommandQueue>(args.This());
    Kernel *kernel = ObjectWrap::Unwrap<Kernel>(args[0]->ToObject());
    v8::Local<v8::Array> offset = v8::Local<v8::Array>::Cast(args[1]);
    v8::Local<v8::Array> global = v8::Local<v8::Array>::Cast(args[2]);
    v8::Local<v8::Array> local = v8::Local<v8::Array>::Cast(args[3]);
    cl_int err = queue->_commandQueue->enqueueNDRangeKernel(*kernel->_kernel, arrayToNDRange(offset), arrayToNDRange(global), arrayToNDRange(local));
    return scope.Close(v8::Integer::New(err));

}
void CommandQueue::Initialize(v8::Handle<v8::Object> target) {
    v8::HandleScope scope;

    constructor = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(CommandQueue::New));
    constructor->InstanceTemplate()->SetInternalFieldCount(1);
    constructor->SetClassName(v8::String::NewSymbol("CommandQueue"));

    NODE_SET_PROTOTYPE_METHOD(constructor, "enqueueNDRangeKernel", CommandQueue::EnqueueNDRangeKernel);
    NODE_SET_PROTOTYPE_METHOD(constructor, "finish", CommandQueue::Finish);

    target->Set(v8::String::NewSymbol("CommandQueue"), constructor->GetFunction());

}
