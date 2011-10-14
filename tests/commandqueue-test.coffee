#!/usr/bin/env coffee

vows = require "vows"
assert = require "assert"
opencl = require "../index"
Kernel = opencl.Kernel
Context = opencl.Context
CommandQueue = opencl.CommandQueue

#program = new opencl.Program context, source
#source = "__kernel void hello(){}"

tests = (vows.describe "CommandQueue").addBatch

  "A CommandQueue":
    topic: ->
      context = new Context opencl.CL_DEVICE_TYPE_ALL, opencl.getPlatforms()[0]
      new CommandQueue context, context.getDevices()[0]

    "should be an instance of CommandQueue": (kernel) ->
      assert.instanceOf context, CommandQueue


tests.export module
