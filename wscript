import Options, Utils
from os import unlink, symlink, popen
from os.path import exists

srcdir = '.'
blddir = 'build'
VERSION = '0.0.1'

def set_options(opt):
  opt.tool_options('compiler_cxx')

def configure(conf):
  conf.check_tool('compiler_cxx')
  conf.check_tool('node_addon')

  conf.env.append_value("LIBPATH_OPENCL", "/opt/AMDAPP/lib/x86/")
  conf.env.append_value("LIB_OPENCL", "OpenCL")
  conf.env.append_value("CPPPATH_OPENCL", "/opt/AMDAPP/include/")

def build(bld):
  obj = bld.new_task_gen('cxx', 'shlib', 'node_addon')
  obj.cxxflags = ["-g", "-D_LARGEFILE_SOURCE", "-Wall","-fpermissive"]
  obj.target = 'opencl'
  obj.source = "src/opencl.cpp src/platform.cpp src/device.cpp src/context.cpp"
  obj.uselib = "OPENCL"
