#!/usr/bin/env coffee

vows = require "vows"
assert = require "assert"
opencl = require "../index"
Kernel = opencl.Kernel
Context = opencl.Context
source = "__kernel void hello(){}"
context = new Context opencl.CL_DEVICE_TYPE_ALL, opencl.getPlatforms()[0]
program = new opencl.Program context, source

tests = (vows.describe "Kernel").addBatch

  "A Kernel":
    topic: ->
      program.build context.getDevices()
      new Kernel program, "hello"

    "should be an instance of Kernel": (kernel) ->
      assert.instanceOf context, Context



tests.export module
