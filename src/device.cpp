#include "device.hpp"

#include <iostream>

v8::Persistent<v8::FunctionTemplate> constructor;

v8::Handle<v8::Value> Device::New(cl::Device *device) {

    v8::HandleScope scope;
    Device *d = new Device(device);
    v8::Handle<v8::Value> ext = v8::External::New(d);
    v8::Handle<v8::Object> obj = constructor->GetFunction()->NewInstance(1, &ext);
    d->Wrap(obj);
    return scope.Close(obj);

}
Device::Device(cl::Device *device) {
    _device = device;
}

Device::Device() {}

Device::~Device() {
}

v8::Handle<v8::Value> Device::GetDeviceName(const v8::Arguments& args) {
    v8::HandleScope scope;
    Device *d = ObjectWrap::Unwrap<Device>(args.This());
    std::string info;
    std::cout << d->_device << std::endl;
    d->_device->getInfo(CL_DEVICE_NAME,&info);
    return scope.Close(v8::String::New(info.data()));

}
v8::Handle<v8::Value> Device::New(const v8::Arguments& args) {
    v8::HandleScope scope;
    Device *d = new Device();
    d->Wrap(args.This());
    return args.This();
}



void Device::Initialize(v8::Handle<v8::Object> target) {
    v8::HandleScope scope;

    constructor = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(Device::New));
    constructor->InstanceTemplate()->SetInternalFieldCount(1);
    constructor->SetClassName(v8::String::NewSymbol("Device"));

    NODE_SET_PROTOTYPE_METHOD(constructor, "getDeviceName", Device::GetDeviceName);

}
