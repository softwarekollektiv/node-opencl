#!/usr/bin/env coffee

vows = require "vows"
assert = require "assert"
opencl = require "../index"
Context = opencl.Context

tests = (vows.describe "Context").addBatch

  "A Context":
    topic: ->
      new Context opencl.CL_DEVICE_TYPE_CPU, opencl.getPlatforms()[0]

    "should be an instance of Context": (context) ->
      assert.instanceOf context, Context

    "should have a getDevices function": (context) ->
      assert.isFunction context.getDevices
      assert.isArray context.getDevices()


tests.export module
