# ChessGame
This is an example of how to use OpenGL/glut library in C++ to create a game.

> **Attention:** This game is not fully working, and prepared for educational purposes to show how to easily use glut library.

# Requirements
OpenGL/glut library needs to be installed. There are two ways to do this;

**First and better way**
If you are using Visual Studio, then you can go to 'Project > Manage NuGet Packages...' and browse for 'nupengl.core'. When you install 'nupengl.core', it will be ready to compile.

**Second way**
Download the library files [here](http://www.opengl.org/resources/libraries/glut/glutdlls37beta.zip "Glut Download Link").
There are totally five files, which includes one header file (glut.h), two link library files (glut.lib, glut32.lib) and two dynamic link library files (glut.dll, glut32.dll).
You need to copy files as following:
- glut.h  ---> C:\Program Files (x86)\Microsoft SDKs\Windows\vXA\Include\gl (X can be different according to Visual Studio version)
- glut.dll, glut32.dll  ---> C:\Windows\SysWOW64 (windows 64 bit)
- glut.dll, glut32.dll  ---> C:\Windows\System32   (windows 32 bit)
- glut.lib, glut32.lib ---> X:\Program Files (x86)\Microsoft Visual Studio XX\VC\lib (X is Visual Studio install disk / XX Visual Studio version)

**Attention:** For those who wonder which IDE did I use, I used Visual Studio 2015 Community Edition [download](https://www.visualstudio.com/downloads/ "Visual Studio Downloads"), and installed nupengl.core via NuGet.

