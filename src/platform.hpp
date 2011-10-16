#ifndef PLATTFORM_HPP
#define PLATTFORM_HPP

#include "opencl.hpp" //common headers
#include "device.hpp"

class Platform : public ObjectWrap {
    public:
        cl::Platform _platform;

        Platform();
        Platform(cl::Platform &platform);
        ~Platform();

        static v8::Persistent<v8::FunctionTemplate> constructor;

        static void Initialize(v8::Handle<v8::Object> target);

        static v8::Handle<v8::Value> New(cl::Platform &platform);

    protected:
        static v8::Handle<v8::Value> New(const v8::Arguments& args);
        static v8::Handle<v8::Value> GetInfo(const v8::Arguments& args);
        static v8::Handle<v8::Value> GetDevices(const v8::Arguments& args);
};

#endif
