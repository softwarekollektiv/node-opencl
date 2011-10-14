#include <v8.h>
#include <node.h>

#include <stdlib.h>

#define __CL_ENABLE_EXCEPTIONS
#include <CL/cl.hpp>

#include "platform.hpp"
#include "device.hpp"
#include "context.hpp"
#include "program.hpp"

using namespace node;

static v8::Handle<v8::Value> GetPlatforms(const v8::Arguments& args);
