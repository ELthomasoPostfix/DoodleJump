# DoodleJump
A project for the course Advanced Programming for the University of Antwerp during the academic year of 2021-2022.

# How to run
The file resources.h, compiled as a part of the DoodleView static library, contains the paths of the sprites used in
creating the different entities. As this file is used in compilation, it defines from where the executable should be run
at compile time. This location cannot currently be redefined without recompiling (at least I do not know how).
The unmodified resources.h file as found on this github repository requires the executable to be run from a folder
that contains the Resources directory found on this github page. Otherwise, an error reporting an incorrect file path
will be printed.