#include "opencl.hpp"
#include "context.hpp"
#include <iostream>

v8::Handle<v8::Value> Context::New(cl::Context context) {
    v8::HandleScope scope;
    Context *c = new Context(context);
    v8::Handle<v8::Value> ext = v8::External::New(c);
    v8::Handle<v8::Object> obj = constructor->GetFunction()->NewInstance(1, &ext);
    c->Wrap(obj);
    return scope.Close(obj);
}

Context::Context(cl::Context context) {
    _context = context;
}
Context::Context() {}
Context::~Context() {
}

v8::Handle<v8::Value> Context::New(const v8::Arguments& args) {
    v8::HandleScope scope;
    Platform *platform = ObjectWrap::Unwrap<Platform>(args[1]->ToObject());
    try {

        cl_context_properties cps[3] = { CL_CONTEXT_PLATFORM, (cl_context_properties)(platform->_platform)(), 0};
        cl::Context context(args[0]->IntegerValue(), cps);
        Context *c = new Context(context);
        c->Wrap(args.This());
        return args.This();
    }
    catch(cl::Error error) {
        return v8::ThrowException(v8::Exception::Error(v8::String::New(error.what())));
    }

}
v8::Handle<v8::Value> Context::GetDevices(const v8::Arguments& args) {
    v8::HandleScope scope;
    std::vector<cl::Device> devices;
    Context *context = ObjectWrap::Unwrap<Context>(args.This());
    context->_context.getInfo(CL_CONTEXT_DEVICES, &devices);

    std::vector<cl::Device>::iterator it;
    v8::Local<v8::Array> array = v8::Array::New(devices.size());
    int j=0;
    for(it = devices.begin(); it != devices.end(); ++it) {
        array->Set(j,Device::New(*it));
        j++;
    }
    return scope.Close(array);
}

v8::Handle<v8::Value> Context::GetInfo(const v8::Arguments& args) {
    v8::HandleScope scope;
    Context *context = ObjectWrap::Unwrap<Context>(args.This());
    std::string info;
    context->_context.getInfo(args[0]->IntegerValue(),&info);
    return scope.Close(v8::String::New(info.data()));

}

v8::Persistent<v8::FunctionTemplate> Context::constructor;

void Context::Initialize(v8::Handle<v8::Object> target) {
    v8::HandleScope scope;

    constructor = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(Context::New));
    constructor->InstanceTemplate()->SetInternalFieldCount(1);
    constructor->SetClassName(v8::String::NewSymbol("Context"));

    NODE_SET_PROTOTYPE_METHOD(constructor, "getInfo", Context::GetInfo);
    NODE_SET_PROTOTYPE_METHOD(constructor, "getDevices", Context::GetDevices);

    target->Set(v8::String::NewSymbol("Context"), constructor->GetFunction());

}
