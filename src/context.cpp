#include "opencl.hpp"
#include "context.hpp"

v8::Handle<v8::Value> Context::New(cl::Context context) {
    v8::HandleScope scope;
    Context *c = new Context(context);
    v8::Handle<v8::Value> ext = v8::External::New(c);
    v8::Handle<v8::Object> obj = constructor->GetFunction()->NewInstance(1, &ext);
    c->Wrap(obj);
    return scope.Close(obj);
}

Context::Context(cl::Context context) {
    _context = context;
}
Context::Context() {}
Context::~Context() {
}

v8::Handle<v8::Value> Context::New(const v8::Arguments& args) {
    v8::HandleScope scope;
    Context *c = new Context();
    c->Wrap(args.This());
    return args.This();
}

v8::Persistent<v8::FunctionTemplate> Context::constructor;

void Context::Initialize(v8::Handle<v8::Object> target) {
    v8::HandleScope scope;

    constructor = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(Context::New));
    constructor->InstanceTemplate()->SetInternalFieldCount(1);
    constructor->SetClassName(v8::String::NewSymbol("Context"));
}
