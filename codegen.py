#!/usr/bin/env python

# Copyright (c) 2012 Jasson Casey

# Permission is hereby granted, free of charge, to any person
# obtaining a copy of this software and associated documentation
# files (the "Software"), to deal in the Software without
# restriction, including without limitation the rights to use,
# copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following
# conditions:
#
# The above copyright notice and this permission
# notice shall be included in all copies or substantial portions of
# the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT
# WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
# LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
# PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
# OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
# OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.'

import sys, os, datetime, string

gpl  = [ 'This program is free software; you can redistribute it and/or\n' ]
gpl += [ 'modify it under the terms of the GNU General Public License as\n' ]
gpl += [ 'published by the Free Software Foundation; either version 2 of\n' ]
gpl += [ 'the License, or (at your option) any later version.\n' ]
gpl += [ '\n' ]
gpl += [ 'This program is distributed in the hope that it will be useful,\n' ]
gpl += [ 'but WITHOUT ANY WARRANTY; without even the implied warranty of\n' ]
gpl += [ 'MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU\n' ]
gpl += [ 'General Public License for more details at\n' ]
gpl += [ 'http://www.gnu.org/copyleft/gpl.html\n' ]
                        
mit  = [ 'Permission is hereby granted, free of charge, to any person \n' ]
mit += [ 'obtaining a copy of this software and associated documentation\n' ]
mit += [ 'files (the "Software"), to deal in the Software without\n' ]
mit += [ 'restriction, including without limitation the rights to use,\n' ]
mit += [ 'copy, modify, merge, publish, distribute, sublicense, and/or sell\n']
mit += [ 'copies of the Software, and to permit persons to whom the\n' ]
mit += [ 'Software is furnished to do so, subject to the following\n' ]
mit += [ 'conditions:\n' ]
mit += [ '\n' ]
mit += [ 'The above copyright notice and this permission\n' ]
mit += [ 'notice shall be included in all copies or substantial portions of\n' ]
mit += [ 'the Software.\n' ]
mit += [ '\n' ]
mit += [ 'THE SOFTWARE IS PROVIDED "AS IS", WITHOUT\n' ]
mit += [ 'WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT\n' ]
mit += [ 'LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A\n' ]
mit += [ 'PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n' ]
mit += [ 'AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR\n' ]
mit += [ 'OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR\n' ]
mit += [ 'OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE\n' ]
mit += [ 'SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.\n' ]

# Common strings for arguments

description = 'Gens code files with base info: author, licence, etc...'

usage_string  = './codegen <language> <module name> <licence> <copyright holder>'
usage_string += ' <authors ...> '

languages = [ 'c++', 'python', 'make', 'c', 'shell', 'bash' ]
licenses  = { 'gpl':gpl, 'gpl2':'', 'lgpl':'', 'mit':mit }

# Basic items for the shell file
year = datetime.datetime.now().year
version = '0.1'

def make_comma_list( list ):
   first = True
   line = ''
   for item in list:
      if first == True:
         first = False
      else:
         line += ', '
      line += item
   return line

def make_python_shell( config ):
   file  = "#!/usr/bin/env python\n\n"
   file += "# Copyright (c) " + str(year) + " " + config[2] + '\n\n'
   file += "\"\"\"\n"
   file += "@package\t" + config[0] + '.py\n'
   file += "@authors\t" + make_comma_list( config[3] ) + '\n'
   file += "@version\t" + version + '\n\n'
   file += "@section LICENSE\n\n"
   file += string.join( licenses[ config[1] ], '' ) 
   file += "\"\"\"\n\n"
   return file

def make_c_shell( config, trailer ):
   file  = "/**\n"
   file += " * Copyright (c) " + str(year) + " " + config[2] + '\n'
   file += ' *\n'
   file += " * @file\t" + config[0] + trailer + "\n"
   file += " * @author\t" + make_comma_list( config[3] ) + '\n'
   file += " * @version\t" + version + '\n'
   file += " *\n"
   file += " * @section LICENSE\n"
   file += " *\n"
   file += " * " + string.join( licenses[ config[1] ], ' * ' )
   file += " *\n */\n\n"
   file += " #include \"" + config[0] + '.h\"\n'
   return file

def make_h_includes( config ):
   file  = "#ifndef " + string.upper( config[0] ) + "_H\n"
   file += "#define " + string.upper( config[0] ) + "_H\n"
   file += "\n// Your code goes here ...\n\n"
   file += "#endif\n"
   return file

def usage_error():
   print 'Description: ' + description
   print 'Usage: ' + usage_string
   print 'Languages: ' + make_comma_list( languages )
   print 'Licenses: ' + make_comma_list( licenses.keys() )

def interactive():

   # Provide some information
   print 'Code Generation Utility: interactive mode  ...\n'
   lang_select = 'Select a language from: ' + make_comma_list( languages )
   lic_select = 'Select a license from: ' + make_comma_list( licenses.keys() )

   # Choose the language
   lang = ''
   while not lang in languages:
      lang = raw_input( lang_select + ': ' )

   # Enter the module name
   mod = ''
   while len(mod) == 0:
      mod = raw_input( 'Enter the module name: ' )

   # Choose the license type
   lic = ''
   while not lic in licenses.keys():
      lic = raw_input( lic_select + ': ' )

   # Enter the copyright holder's name
   copyhold = ''
   while len(copyhold) == 0:
      copyhold = raw_input( 'Copyright holder: ' )

   # Enter the authors' names
   done = False
   authors = []
   while not done:
      author = ''
      while len(author) == 0:
         author = raw_input( 'Author\'s name: ' )
      authors += [ author ]
      more = ''
      while not ( more == 'y' or more == 'n' ) :
         more = raw_input( 'More authors y or n: ' )
      if more == 'n':
         done = True

   # Return the configuration string
   return [ lang, mod, lic, copyhold, authors ]

def parse( input ):
   config = input[:4]

   # Check the language choice
   if not input[0] in languages: 
      print 'Language error: ' + input[0]
      sys.exit(-1)
   # Check the license choice
   if not input[2] in licenses.keys():
      print 'License error: ' + input[2]
      sys.exit(-1)
   config += [ input[4:] ]

   return config

def gen_c_files( config ):
   c_file = ( config[0] + '.c', make_c_shell( config, '.c' ) )
   h_content = make_c_shell( config, '.h' ) + make_h_includes( config )
   h_file = ( config[0] + '.h',  h_content )
   return [ c_file, h_file ]

def gen_cpp_files( config ):
   c_file = ( config[0] + '.cc', make_c_shell( config, '.cc' ) )
   h_content = make_c_shell( config, '.h' ) + make_h_includes( config )
   h_file = ( config[0] + '.h',  h_content )
   return [ c_file, h_file ]

def gen_python_files( config ):
   py_file = make_python_shell( config )
   return [ ( config[0] + '.py', py_file ) ]

def write_files( results ):

   # Check to make sure we are not going to clobber any existing files
   fail = False
   for ( filename, file ) in results:
      if os.path.exists( filename ):
         print "Error cannot overwrite: " + filename
         fail = True
   if fail == True:
      sys.exit( -1 )

   # Write the results
   for ( filename, file ) in results:
      f = open( filename, 'w' )
      f.write( file )
      f.close()

def gen_files( config ):

   results = []
   if config[0] == 'c':
      results = gen_c_files( config[1:] )
   elif config[0] == 'c++':
      results = gen_cpp_files( config[1:] )
   elif config[0] == 'python':
      results = gen_python_files( config[1:] )
   else:
      print 'Error Unimplemented Language: ' + config[0]
      sys.exit(-1)

   write_files( results )

if __name__ == '__main__':

   config = []

   # Handle an interactive session
   if len( sys.argv ) == 1:
      config = interactive()

   # Handle erronious arguments
   elif len( sys.argv ) < 6:
      usage_error()
      sys.exit( -1 )

   # Handle command line arguments
   else:
      config = parse( sys.argv[1:] )

   gen_files( config )
   


