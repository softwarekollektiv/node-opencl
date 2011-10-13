
#include "opencl.hpp"
#include "platform.hpp"
#include <iostream>



v8::Handle<v8::Value> Platform::New(cl::Platform platform) {
    using namespace v8;
    v8::HandleScope scope;
    Platform *p = new Platform(platform);
    v8::Handle<v8::Value> ext = v8::External::New(p);
    v8::Handle<v8::Object> obj = constructor->GetFunction()->NewInstance(1, &ext);
    p->Wrap(obj);

    /* CL_PLATFORM_PROFILE
     * CL_PLATFORM_VERSION
     * CL_PLATFORM_NAME
     * CL_PLATFORM_VENDOR
     * CL_PLATFORM_EXTENSIONS
     */

    std::string info;
    p->_platform.getInfo(CL_PLATFORM_PROFILE,&info);
    obj->Set(v8::String::NewSymbol("platformProfile"),v8::String::New(info.data()));
    p->_platform.getInfo(CL_PLATFORM_VERSION,&info);
    obj->Set(v8::String::NewSymbol("platformVersion"),v8::String::New(info.data()));
    p->_platform.getInfo(CL_PLATFORM_NAME,&info);
    obj->Set(v8::String::NewSymbol("platformName"),v8::String::New(info.data()));
    p->_platform.getInfo(CL_PLATFORM_VENDOR,&info);
    obj->Set(v8::String::NewSymbol("platformVendor"),v8::String::New(info.data()));
    p->_platform.getInfo(CL_PLATFORM_EXTENSIONS,&info);
    obj->Set(v8::String::NewSymbol("platformExtensions"),v8::String::New(info.data()));


    return scope.Close(obj);

}

Platform::Platform(cl::Platform platform) {
    _platform = platform;
}
Platform::Platform() {}
Platform::~Platform() {
}

v8::Handle<v8::Value> Platform::New(const v8::Arguments& args) {
    v8::HandleScope scope;
    Platform *p = new Platform();
    p->Wrap(args.This());
    return args.This();
}

v8::Handle<v8::Value> Platform::GetInfo(const v8::Arguments& args) {
    v8::HandleScope scope;
    Platform *p = ObjectWrap::Unwrap<Platform>(args.This());
    std::string info;
    p->_platform.getInfo(CL_PLATFORM_NAME,&info);
    return scope.Close(v8::String::New(info.data()));

}

v8::Handle<v8::Value> Platform::GetDevices(const v8::Arguments& args) {
    using namespace v8;
    HandleScope scope;
    Platform *p = ObjectWrap::Unwrap<Platform>(args.This());
    std::vector<cl::Device> devices;
    p->_platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);
    std::vector<cl::Device>::iterator it;
    v8::Local<Array> array = v8::Array::New(devices.size());
    int j=0;
    for(it = devices.begin(); it != devices.end(); ++it) {
        array->Set(j,Device::New(*it));
        j++;
    }
    return scope.Close(array);
}

v8::Persistent<v8::FunctionTemplate> Platform::constructor;

void Platform::Initialize(v8::Handle<v8::Object> target) {
    using namespace v8;
    v8::HandleScope scope;

    constructor = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(Platform::New));
    constructor->InstanceTemplate()->SetInternalFieldCount(1);
    constructor->SetClassName(v8::String::NewSymbol("Platform"));

    NODE_SET_PROTOTYPE_METHOD(constructor, "getInfo", Platform::GetInfo);
    NODE_SET_PROTOTYPE_METHOD(constructor, "getDevices", Platform::GetDevices);

}
