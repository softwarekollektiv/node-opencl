#include "opencl.hpp"

#include <iostream>

v8::Persistent<v8::FunctionTemplate> CommandQueue::constructor;

CommandQueue::CommandQueue(cl::CommandQueue commandQueue) {
    _commandQueue = commandQueue;
}

v8::Handle<v8::Value> CommandQueue::New(const v8::Arguments& args) {
    v8::HandleScope scope;
    Context *context = ObjectWrap::Unwrap<Context>(args[0]->ToObject());
    Device *device = ObjectWrap::Unwrap<Device>(args[1]->ToObject());
    cl::CommandQueue queue(context->_context, device->_device);
    CommandQueue *k = new CommandQueue(queue);
    k->Wrap(args.This());
    return args.This();
}

void CommandQueue::Initialize(v8::Handle<v8::Object> target) {
    v8::HandleScope scope;

    constructor = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(CommandQueue::New));
    constructor->InstanceTemplate()->SetInternalFieldCount(1);
    constructor->SetClassName(v8::String::NewSymbol("CommandQueue"));

    target->Set(v8::String::NewSymbol("CommandQueue"), constructor->GetFunction());

}
