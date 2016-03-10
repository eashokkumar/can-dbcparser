# VariantDir('build', 'src', duplicate=0)
env = Environment()

debug = ARGUMENTS.get('debug', 0)

env.Append(CCFLAGS = ['--std=c++11'])

if debug:
	env.Append(CCFLAGS = ['-O0', '-g3'])
	
include_dirs = Dir('..')

include_files = Glob('header/*.hpp')

dbcparserlib = env.SharedLibrary('dbcparser', Glob('src/*.cpp'), CPPPATH=include_dirs)

parser = env.Program('dbcparser', Glob('examples/*.cpp'), CPPPATH=include_dirs, LIBS=[dbcparserlib])

env.Install('/usr/local/lib/', dbcparserlib)
env.Install('/usr/local/include/dbcparser', include_files)

env.Alias('install', '/usr/local/')