#include "opencl.hpp"

#include <iostream>

v8::Persistent<v8::FunctionTemplate> Program::constructor;

Program::Program(cl::Program *program) {
    _program = program;
}

v8::Handle<v8::Value> Program::New(const v8::Arguments& args) {
    v8::HandleScope scope;
    Context *context = ObjectWrap::Unwrap<Context>(args[0]->ToObject());
    std::string code = *v8::String::Utf8Value(args[1]->ToString());
    cl::Program::Sources sources(1, std::make_pair(code.data(),code.size()));
    cl::Program *program = new cl::Program(*context->_context, sources, NULL);
    Program *p = new Program(program);
    p->Wrap(args.This());
    return args.This();
}

v8::Handle<v8::Value> Program::Build(const v8::Arguments& args) {
    v8::HandleScope scope;
    Program *program = ObjectWrap::Unwrap<Program>(args.This());
    v8::Local<v8::Array> array = v8::Local<v8::Array>::Cast(args[0]);
    std::vector<cl::Device> devices;
    for(unsigned int i; i < array->Length(); ++i) {
        v8::Local<v8::Value> t = array->Get(v8::Integer::New(i));
        Device *d = ObjectWrap::Unwrap<Device>(t->ToObject());
        devices.push_back(d->_device);
    }

    cl_int err = program->_program->build(devices);
    return scope.Close(v8::Integer::New(err));
}


void Program::Initialize(v8::Handle<v8::Object> target) {
    v8::HandleScope scope;

    constructor = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(Program::New));
    constructor->InstanceTemplate()->SetInternalFieldCount(1);
    constructor->SetClassName(v8::String::NewSymbol("Program"));

    NODE_SET_PROTOTYPE_METHOD(constructor, "build", Build);

    target->Set(v8::String::NewSymbol("Program"), constructor->GetFunction());


}
