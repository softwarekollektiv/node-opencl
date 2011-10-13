#ifndef PLATTFORM_HPP
#define PLATTFORM_HPP

#include "opencl.hpp"

class Platform : public ObjectWrap {
    public:
        static void Initialize(v8::Handle<v8::Object> target);
        Platform(cl::Platform platform);
        ~Platform();
        Platform();
        static v8::Handle<v8::Value> New(cl::Platform platform);
        static v8::Persistent<v8::FunctionTemplate> constructor;

    protected:
        static v8::Handle<v8::Value> New(const v8::Arguments& args);
        static v8::Handle<v8::Value> GetInfo(const v8::Arguments& args);
        static v8::Handle<v8::Value> GetDevices(const v8::Arguments& args);
    private:
        cl::Platform _platform;
};

#endif
