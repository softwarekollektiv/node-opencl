opencl = require "../index"
console.log opencl

console.log opencl.getPlatforms()

platforms = opencl.getPlatforms()
console.log platforms[0]

console.log platforms[0].getDevices()
