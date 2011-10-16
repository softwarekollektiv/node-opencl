#!/usr/bin/env coffee

vows = require "vows"
assert = require "assert"
opencl = require "../index"
Kernel = opencl.Kernel
Context = opencl.Context
CommandQueue = opencl.CommandQueue
[platform] = opencl.getPlatforms()
context = new Context opencl.CL_DEVICE_TYPE_CPU, platform

source = "__kernel void hello(){}"
program = new opencl.Program context, source

program.build context.getDevices()

kernel = new Kernel program, "hello"

#console.log context.getDevices()[0].getDeviceName()

tests = (vows.describe "CommandQueue").addBatch

  "A CommandQueue":
    topic: ->
      new CommandQueue context, context.getDevices()[0]

    "should be an instance of CommandQueue": (queue) ->
      assert.instanceOf queue, CommandQueue

    "should have a enqueueNDRangeKernel function": (queue) ->
      assert.isFunction queue.enqueueNDRangeKernel
      assert.equal (queue.enqueueNDRangeKernel kernel), 0

    "should have a finish function": (queue) ->
      assert.isFunction queue.finish
      assert.equal queue.finish(), 0


tests.export module
