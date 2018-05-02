#!/bin/bash

# Multi-file opening script for EzC projects
#
# Copyright (c) 2018 Kirk Lange
#
# This software is provided 'as-is', without any express or implied
# warranty. In no event will the authors be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
# 1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgment in the product documentation would be
#    appreciated but is not required.
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.



# This script is really only intended to be called by `ezc.mk`, which itself
#   is only intended to be called by the root `Makefile`. The interface for
#   this script is not at all user-friendly but it doesn't have to be. The
#   root `Makefile` provides the interface for calling this script.
#
# Five Expected Arguments
# =======================
# 1: SRC_DIR
# 2: INC_DIR
# 3: PRJ_DIR
# 4: file name (without extension)
# 5: window opening mode

F="${4}.*"
W="${5}"
A=`find ${1} -name $F`
B=`find ${2} -name $F`
C=`find ${3} -name $F`

if [ "$W" == "t" ] || [ "$W" == "tb" ] || [ "$W" == "tab" ]; then
    W="-p";
elif [ "$W" == "v" ] || [ "$W" == "vs" ] || [ "$W" == "vsplit" ]; then
    W="-O";
fi

vim $W $A $B $C
