#!/usr/bin/env python
import os.path
from glob import glob

prog_target = 'colladatest'
sources = glob('src/*.cpp')
sources += glob('src/*/*.cpp')

env = Environment(build_dir='build')
win32 = ARGUMENTS.get('win32', 0)
debug_flag = ARGUMENTS.get('debug', 0)
clang_flag = ARGUMENTS.get('clang', 0)
boost_flag = ARGUMENTS.get('boost', 0)

env.Tool('colourful', toolpath=['scons-tools'])
#env.AppendUnique(LIBS=['m', 'IL', 'mxml', 'rcbc', 'luabind'])
env.Tool('qt')
env.AppendUnique(LIBS=['xerces-c', 'GL', 'GLU', 'IL'])#, 'boost_thread', 'libboost_system'])
env.AppendUnique(CCFLAGS=['-llibboost_system', '-llibboost_thread'])
env['QTDIR'] = '/usr'
env['QT_LIB'] = 'QtGui'
env.ParseConfig('pkg-config --libs --cflags QtGui QtOpenGL')
#if int(win32):
#	env.Tool('crossmingw', toolpath = ['scons-tools'])
#	env['MINGWROOT'] = '/usr/$MINGWPREFIX'
#	env['MINGWLIBS'] = '$MINGWROOT/lib'
#	env['MINGWINC'] = '$MINGWROOT/include'
#	env.AppendUnique(LIBS=['opengl32', 'glu32'])
#	env.ParseConfig('/usr/$MINGWPREFIX/bin/sdl-config --cflags --libs')
#	env.AppendUnique(LIBS=['lua'])
#	env.AppendUnique(LIBS=['bulletdynamics', 'bulletcollision', 'bulletmath'])
#	env.MergeFlags(env.subst('-I$MINGWINC/bullet/'))
#	env.MergeFlags(env.subst("$MINGWLIBS/libopengl32.a"))
#	env.MergeFlags(env.subst("$MINGWLIBS/libmxml.a"))
#	env.MergeFlags(env.subst("$MINGWLIBS/DevIL.lib"))
#	env['QTDIR'] = '$MINGWROOT'
#	env['QT_LIB'] = 'QtGui4'
#	env.MergeFlags(env.subst("-DQT_SHARED -I$MINGWINC/qt4 -I$MINGWINC/qt4/QtGui -I$MINGWINC/qt4/QtCore  -lQtGui4 -lQtCore4"))
#else:
#	env.AppendUnique(LIBS=['GL', 'GLU'])
#	env.ParseConfig('sdl-config --cflags --libs')
#	env.ParseConfig('pkg-config --cflags --libs lua5.1')
#	env.ParseConfig('pkg-config --cflags --libs bullet')
#	env['QTDIR'] = '/usr'
#	env['QT_LIB'] = 'QtGui'
#	env.ParseConfig('pkg-config --libs --cflags QtGui')

#env.ParseConfig('pkg-config --libs --cflags xerces-c')
env.ParseConfig('sdl-config --cflags --libs')

if int(debug_flag):
	env.Append(CCFLAGS = ['-g'])
	env.Append(CPPDEFINES=['_DEBUG'])

# clang also needs boost as it doesn't seem to work with c++0x
if int(clang_flag):
	env['CXX'] = 'clang++'
	env.Append(CCFLAGS = ['-fcolor-diagnostics'])

env.Append(CCFLAGS = ['-Wall'])

# Also there's untested D_TR1PTR 
if int(boost_flag):
	env.Append(CCFLAGS = ['-D_BOOSTPTR'])
else:
	env.Append(CCFLAGS = ['-std=c++0x'])

objects = env.Object(sources)
target = env.Program(target = prog_target, source=objects)

Default(target)
