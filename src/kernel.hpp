#ifndef KERNEL_HPP
#define KERNEL_HPP

#include "opencl.hpp"

class Kernel : public ObjectWrap {
    public:
        cl::Kernel *_kernel;

        Kernel(cl::Kernel *kernel);

        static v8::Persistent<v8::FunctionTemplate> constructor;
        static void Initialize(v8::Handle<v8::Object> target);

    protected:
        static v8::Handle<v8::Value> New(const v8::Arguments& args);
};

#endif
