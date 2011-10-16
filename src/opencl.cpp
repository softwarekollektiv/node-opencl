#include <iostream>

#include "opencl.hpp" //common headers

#include "platform.hpp"
#include "device.hpp"
#include "context.hpp"
#include "program.hpp"
#include "kernel.hpp"
#include "commandqueue.hpp"


v8::Handle<v8::Value> GetPlatforms(const v8::Arguments& args) {
    v8::HandleScope scope;
    cl_int err;
    std::vector<cl::Platform> platforms;
    err = cl::Platform::get(&platforms);

    if(err != CL_SUCCESS) {
        //TODO throw exception
        return v8::Undefined();
    }

    std::vector<cl::Platform>::iterator it;
    v8::Local<v8::Array> array = v8::Array::New(platforms.size());
    int j=0;
    for(it = platforms.begin(); it != platforms.end(); ++it) {
        array->Set(j,Platform::New(*it));
        j++;
    }
    //return an array of plattform objects
    return scope.Close(array);
}

void Initialize(v8::Handle<v8::Object> target) {
    v8::HandleScope scope;
    NODE_SET_METHOD(target, "getPlatforms", GetPlatforms);
}

extern "C" {
    void init(v8::Handle<v8::Object> target) {
        v8::HandleScope scope;
        Initialize(target);
        Platform::Initialize(target);
        Device::Initialize(target);
        Context::Initialize(target);
        Program::Initialize(target);
        Kernel::Initialize(target);
        CommandQueue::Initialize(target);
    }

    NODE_MODULE(opencl, init);
}
