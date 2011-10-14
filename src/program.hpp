#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "opencl.hpp"

class Program : public ObjectWrap {
    public:
        cl::Program _program;

        Program(cl::Program program);

        static v8::Persistent<v8::FunctionTemplate> constructor;

        static void Initialize(v8::Handle<v8::Object> target);

        static v8::Handle<v8::Value> Build(const v8::Arguments& args);

    protected:
        static v8::Handle<v8::Value> New(const v8::Arguments& args);
};

#endif
