#!/usr/bin/env coffee

vows = require "vows"
assert = require "assert"

tests = (vows.describe "Module").addBatch

  "A opencl Module":
    topic: ->
      require "../index"

    "should have a getPlatforms function": (opencl) ->
      assert.isFunction opencl.getPlatforms
      assert.isArray opencl.getPlatforms()

tests.export module
