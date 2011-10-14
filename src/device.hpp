#ifndef DEVICE_HPP
#define DEVICE_HPP

#include "opencl.hpp"

class Device : public ObjectWrap {
    public:
        static void Initialize(v8::Handle<v8::Object> target);
        Device(cl::Device device);
        ~Device();
        Device();
        static v8::Handle<v8::Value> New(cl::Device device);
        cl::Device _device;

    protected:
        static v8::Handle<v8::Value> New(const v8::Arguments& args);
};

#endif
