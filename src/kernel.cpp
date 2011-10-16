#include "kernel.hpp"

#include <iostream>

v8::Persistent<v8::FunctionTemplate> Kernel::constructor;

Kernel::Kernel(cl::Kernel *kernel) {
    _kernel = kernel;
}

v8::Handle<v8::Value> Kernel::New(const v8::Arguments& args) {
    v8::HandleScope scope;
    Program *program = ObjectWrap::Unwrap<Program>(args[0]->ToObject());
    cl_int err;
    cl::Kernel *kernel = new cl::Kernel(*program->_program, *v8::String::Utf8Value(args[1]->ToString()), &err);

    if(err != CL_SUCCESS) {
        //std::cout << "kernel error: " << err << std::endl;
        return v8::ThrowException(v8::Exception::Error(v8::String::New("Error in Kernel() constructor")));
    }

    Kernel *k = new Kernel(kernel);
    k->Wrap(args.This());
    return args.This();
}

void Kernel::Initialize(v8::Handle<v8::Object> target) {
    v8::HandleScope scope;

    constructor = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(Kernel::New));
    constructor->InstanceTemplate()->SetInternalFieldCount(1);
    constructor->SetClassName(v8::String::NewSymbol("Kernel"));

    target->Set(v8::String::NewSymbol("Kernel"), constructor->GetFunction());

}
