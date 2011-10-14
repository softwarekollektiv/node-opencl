#ifndef COMMANDQUEUE_HPP
#define COMMANDQUEUE_HPP

#include "opencl.hpp"

class CommandQueue : public ObjectWrap {
    public:
        cl::CommandQueue _commandQueue;

        CommandQueue(cl::CommandQueue commandQueue);

        static v8::Persistent<v8::FunctionTemplate> constructor;
        static void Initialize(v8::Handle<v8::Object> target);

    protected:
        static v8::Handle<v8::Value> New(const v8::Arguments& args);
};

#endif
