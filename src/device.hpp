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

    protected:
        static v8::Handle<v8::Value> New(const v8::Arguments& args);
    private:
        cl::Device _device;
};

#endif
