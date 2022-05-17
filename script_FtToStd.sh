#!bin/bash

cd srcs
echo "#include <vector>" > main_std.cpp
echo "#include <stack>" >> main_std.cpp
echo "#include <map>" >> main_std.cpp
echo "#include <exception>" >> main_std.cpp
echo "#include <iostream>" >> main_std.cpp

tail -n 604 main_ft.cpp | sed "s/ft/std/g" >> main_std.cpp