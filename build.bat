@echo off

set idir=-I "C:\Libraries\SDL2~2.0.7\MinGW\x86\include"
set ldir=-L "C:\Libraries\SDL2~2.0.7\MinGW\x86\lib"
set flag=-std=c++11 -pedantic -g
set warn=-Wall -Werror -Wno-unused-variable -Wno-unused-function -Wno-unused-but-set-variable
set libs=-static-libgcc -static-libstdc++ -lmingw32 -lSDL2main -lSDL2 -lSDL2_net -luser32 -lkernel32 -ldbghelp -pthread
set name=Dasher.exe

g++ %idir% %flag% %warn% -o %name% source/main.cpp %ldir% %libs% 