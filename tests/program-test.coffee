#!/usr/bin/env coffee

vows = require "vows"
assert = require "assert"
opencl = require "../index"
Context = opencl.Context
source = "__kernel void hello(){}"
context = new Context opencl.CL_DEVICE_TYPE_ALL, opencl.getPlatforms()[0]

tests = (vows.describe "Program").addBatch

  "A Program":
    topic: ->
      new opencl.Program context, source

    "should be an instace of Program": (program) ->
      assert.instanceOf program, opencl.Program

    "should have a build function": (program) ->
      assert.isFunction program.build
      assert.isTrue program.build context.getDevices()


tests.export module
