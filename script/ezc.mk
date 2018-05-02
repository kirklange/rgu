# Base Makefile for EzC-based Projects
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



# Root directory
# Should be set by "includer" Makefile
#ROOT = ../

# Binaries
BIN_DIR = $(ROOT)/bin
# Build
BLD_DIR = $(ROOT)/build
# Documentation
DOC_DIR = $(ROOT)/docs
# External (git submodule) directory
# Should be set by "includer" Makefile
#EXT_DIR = $(ROOT)/ext
# Include
INC_DIR = $(ROOT)/include
# Libraries
LIB_DIR = $(ROOT)/lib
# Projects
PRJ_DIR = $(ROOT)/project
# Resources (config, textures, etc)
RES_DIR = $(ROOT)/res
# Source
SRC_DIR = $(ROOT)/src



# Add source directory to source file names
OBJS = $(foreach OBJ,$(EXT_SRC_FILES),$(EXT_DIR)/$(OBJ)) \
	   $(foreach DIR,$(EXT_SUBDIRS),$(wildcard $(EXT_DIR)/$(DIR)/*.c)) \
	   $(foreach DIR,$(SRC_SUBDIRS),$(wildcard $(SRC_DIR)/$(DIR)/*.c)) \
	   $(foreach DIR,$(PRJ_SUBDIR),$(wildcard $(PRJ_DIR)/$(DIR)/*.c)) \

# Include and library flags
INC = -I$(INC_DIR) $(foreach DIR,$(EXT_INC_DIRS),-I$(EXT_DIR)/$(DIR))
LIB =

# Find what OS we're on so we can better configure all the compiler options
# Linux->"Linux" | MacOS->"Darwin" | Windows->"*_NT-*"

# All compiler flags can be customized on a per-platform basis
ifneq (, $(shell uname -s | grep -E _NT))
	CULT = windows
	# Uncomment to remove console window
	#CF += -Wl,-subsystem,windows
	# -lmingw32 must come before everything else
	LF_TEMP := $(LF)
	LF = -lmingw32 $(LF_TEMP)
	INC += $(foreach DIR,$(GCC_I_DIRS_WIN),-I$(DIR))
	LIB += $(foreach DIR,$(GCC_L_DIRS_WIN),-L$(DIR))
	OPEN = cmd //c start "${@//&/^&}"
endif
ifneq (, $(shell uname -s | grep -E Linux))
	CULT = linux
	CF +=
	LF +=
	INC += $(foreach DIR,$(GCC_I_DIRS_LIN),-I$(DIR))
	LIB += $(foreach DIR,$(GCC_L_DIRS_LIN),-L$(DIR))
	OPEN = xdg-open
endif
ifneq (, $(shell uname -s | grep -E Darwin))
	CULT = macos
	# TODO: test on MacOS
endif



# TODO: version check python and doxygen
#ifeq(, $(shell where python3))
#endif

PYV_FULL = $(wordlist 2,4,$(subst ., ,$(shell python3 --version 2>&1)))
PYV_MAJOR = $(word 1,${PYV_FULL})
PYV_MINOR = $(word 2,${PYV_FULL})
PYV_PATCH = $(word 3,${PYV_FULL})

MAKE = make --no-print-directory



.PHONY : all $(BLD_DIR) run dirs deps $(EXT_DIR) $(DOC_DIR) rtd
.PHONY : compile help clean clean-$(BLD_DIR) clean-$(EXT_DIR)

all :
	$(MAKE) $(DOC_DIR)
	$(MAKE) $(BLD_DIR)
	$(MAKE) run

help :
	@echo
	@echo "TODO: describe make targets"
	@echo

$(DOC_DIR) :
	mkdir -p $(DOC_DIR)
	$(MAKE) clean-$(DOC_DIR)
	$(MAKE) $(EXT_DIR)
	@# TODO: version check, m.css requires python 3.6+ and doxygen 1.8.14+
	python3 $(EXT_DIR)/m.css/doxygen/dox2html5.py .doxyfile-mcss
	cp $(EXT_DIR)/m.css/css/m-dark+doxygen.compiled.css \
		$(DOC_DIR)/m-dark+doxygen.compiled.css
	find docs/m-dark+doxygen.compiled.css -type f -exec \
		sed -i 's/text-indent: 1\.5rem/text-indent: 0rem/g' {} \;	
	cd $(DOC_DIR) && rm -rf xml/
	@# To be honest the default latex/pdf style is pretty ugly.
	@# TODO: make latex/pdf output look more like sphinx/readthedocs
	@#cd $(DOC_DIR)/latex/ && make && mv refman.pdf ../refman.pdf && \
		cd ../ && rm -rf latex/
	cd $(DOC_DIR) && rm -rf latex/

rtd :
	$(OPEN) docs/index.html
	@#$(OPEN) docs/refman.pdf

$(BLD_DIR) :
	mkdir -p $(BIN_DIR)
	mkdir -p $(BLD_DIR)
	mkdir -p $(RES_DIR)
	cp -R $(BIN_DIR)/. $(BLD_DIR)/$(OUT)/
	cp -R $(RES_DIR) $(BLD_DIR)/$(OUT)/
	$(MAKE) $(EXT_DIR)
	$(MAKE) compile

$(EXT_DIR) :
	git submodule init
	git submodule update

compile : $(OBJS)
	$(CC) $(OBJS) $(INC) $(LIB) $(CF) $(LF) -o $(BLD_DIR)/$(OUT)/$(OUT)

run :
	@echo
	$(BLD_DIR)/$(OUT)/$(OUT)
	@echo

clean :
	$(MAKE) clean-$(BLD_DIR)

clean-all :
	$(MAKE) clean-$(BLD_DIR)
	$(MAKE) clean-$(DOC_DIR)
	$(MAKE) clean-$(EXT_DIR)

clean-$(BLD_DIR) :
	rm -rf $(BLD_DIR)/*

clean-$(DOC_DIR) :
	rm -rf $(DOC_DIR)/*

clean-$(EXT_DIR) :
	rm -rf $(EXT_DIR)/*

