#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include "opencl.hpp"

class Context : public ObjectWrap {
    public:
        static void Initialize(v8::Handle<v8::Object> target);
        Context(cl::Context context);
        ~Context();
        Context();
        static v8::Handle<v8::Value> New(cl::Context context);
        static v8::Persistent<v8::FunctionTemplate> constructor;
        cl::Context _context;

    protected:
        static v8::Handle<v8::Value> New(const v8::Arguments& args);
        static v8::Handle<v8::Value> GetInfo(const v8::Arguments& args);
};

#endif
