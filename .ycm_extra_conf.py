import os
import ycm_core

flags = [
  '-Wall',
  '-Wextra',
  '-Werror',
  '-fexceptions',
  '-DNDEBUG',
  '-std=c++11',
  '-xc++',
  '-isystem/usr/include/',
  '-isystem/usr/local/include',
  '-isystemd:/lib/mingw/x86_64-w64-mingw32/include/SDL2/'
  ]


#  compilation_database_folder = ''
#  
#  if os.path.exists( compilation_database_folder ):
#    database = ycm_core.CompilationDatabase( compilation_database_folder )
#  else:
#    database = None


SOURCE_EXTENSIONS = [ '.cpp', '.cxx', '.cc', '.c', '.m', '.mm' ]

def FlagsForFile( filename, **kwargs ):
  return {
  'flags': flags,
  'do_cache': True
  }
