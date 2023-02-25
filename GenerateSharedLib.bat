@echo off
title GenerateStaticLib
call premake5 vs2022 --lib=shared
pause