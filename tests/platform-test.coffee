#!/usr/bin/env coffee

vows = require "vows"
assert = require "assert"
opencl = require "../index"

tests = (vows.describe "Platform").addBatch

  "A Platform":
    topic: ->
      opencl.getPlatforms()[0]

    "should have a getInfo function": (platform) ->
      assert.isFunction platform.getInfo
      assert.isString platform.getInfo opencl.CL_PLATFORM_VERSION

tests.export module
