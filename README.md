# file2cpp
Simple C/C++ compilation unit generator.

This allows a simple and cross-platform embedding of external resources directly in the program. 

USAGE EXAMPLE

file2cpp any_file.txt

This generates a C++ compile unit (a .hpp and a .cpp pair) exposing two global variables:

any_file_data 
any_file_size

By default, they are located in the same folder as the input file.

DEPENDENCIES
For compilation, this program requires CMake and the Boost libraries

INSTALLATION

Go to the root directory and simply do:

$ cd file2cpp
$ mkdir build
$ cd build 
$ cmake ../
$ make
$ sudo make install

BUGS, SUGGESTIONS, ETC.
Simply contact me. Constructuve criticism are always welcome.
