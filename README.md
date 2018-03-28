# Tethys
Document permission of dbxml 2.5.16  on Tethys system

Steps:
1) Build dbxml using visual studio 2008
2) Open Visual Studio 2008, create new empty C++ Project (say Tethys_dbxml), import header and source code files
3) Locate where dbxml is built, include path, lib into Tethys_dbxml project
  project -> properties -> c++ -> additional include directories
    for example:
    "C:\Users\tchau\Desktop\dbxml-2.5.16\xerces-c-src\src"
    "C:\Users\tchau\Desktop\dbxml-2.5.16\db-4.8.26\build_windows"
    "C:\Users\tchau\Desktop\dbxml-2.5.16\dbxml\include";
    "C:\Users\tchau\Desktop\dbxml-2.5.16\include"
  project -> properties -> Linker -> additional library directories
    "C:\Users\tchau\Desktop\dbxml-2.5.16\dbxml\build_windows\Win32\Debug"
    "C:\Users\tchau\Desktop\dbxml-2.5.16\lib"
  project -> properties -> Linker -> Input -> additional dependencies
    dbxml.lib libdb48d.lib libdbxml25d.lib xerces-c_3D.lib xqilla22d.lib
