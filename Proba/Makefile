################################################################################
#
# Copyright 1993-2009 NVIDIA Corporation.  All rights reserved.
#
# NOTICE TO USER:   
#
# This source code is subject to NVIDIA ownership rights under U.S. and 
# international Copyright laws.  
#
# NVIDIA MAKES NO REPRESENTATION ABOUT THE SUITABILITY OF THIS SOURCE 
# CODE FOR ANY PURPOSE.  IT IS PROVIDED "AS IS" WITHOUT EXPRESS OR 
# IMPLIED WARRANTY OF ANY KIND.  NVIDIA DISCLAIMS ALL WARRANTIES WITH 
# REGARD TO THIS SOURCE CODE, INCLUDING ALL IMPLIED WARRANTIES OF 
# MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE.   
# IN NO EVENT SHALL NVIDIA BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL, 
# OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS 
# OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE 
# OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE 
# OR PERFORMANCE OF THIS SOURCE CODE.  
#
# U.S. Government End Users.  This source code is a "commercial item" as 
# that term is defined at 48 C.F.R. 2.101 (OCT 1995), consisting  of 
# "commercial computer software" and "commercial computer software 
# documentation" as such terms are used in 48 C.F.R. 12.212 (SEPT 1995) 
# and is provided to the U.S. Government only as a commercial end item.  
# Consistent with 48 C.F.R.12.212 and 48 C.F.R. 227.7202-1 through 
# 227.7202-4 (JUNE 1995), all U.S. Government End Users acquire the 
# source code with only those rights set forth herein.
#
################################################################################
#
# Build script for project
#
################################################################################

# Add source files here
EXECUTABLE	:= Proba
# C/C++ source files (compiled with gcc / c++)
CCFILES		:= Proba.cpp

.SUFFIXES : .cu .cu_dbg.o .c_dbg.o .cpp_dbg.o .cu_rel.o .c_rel.o .cpp_rel.o .cubin .ptx

# Add new SM Versions here as devices with new Compute Capability are released
SM_VERSIONS   := sm_10 sm_11 sm_12 sm_13 sm_20

CUDA_INSTALL_PATH ?= /usr/local/cuda

ifdef cuda-install
	CUDA_INSTALL_PATH := $(cuda-install)
endif

OSUPPER = $(shell uname -s 2>/dev/null | tr [:lower:] [:upper:])
OSLOWER = $(shell uname -s 2>/dev/null | tr [:upper:] [:lower:])
INCCC   = $(shell pkg-config --cflags --libs opencv) 

HP_64 = $(shell uname -m | grep 64)
OSARCH= $(shell uname -m)

ROOTDIR      ?= ..
LIBDIR       := $(ROOTDIR)/shared/lib
SHAREDDIR    := $(ROOTDIR)/shared
OCLROOTDIR   := $(ROOTDIR)/OpenCL
OCLCOMMONDIR ?= $(OCLROOTDIR)/common
OCLBINDIR    ?= $(OCLROOTDIR)/bin/
BINDIR       ?= ./
OCLLIBDIR    := $(OCLCOMMONDIR)/lib
INCDIR       ?= .
OBJDIR       ?= obj

CXX        := g++
CC         := gcc
LINK       := g++ -fPIC

INCLUDES  += -I$(INCDIR) -I$(OCLCOMMONDIR)/inc/ -I$(SHAREDDIR)/inc/ -I../common/inc #$(INCCC)
INCLUDES  += $(INCCC)

CXXWARN_FLAGS := \
	-W -Wall \
	-Wimplicit \
	-Wswitch \
	-Wformat \
	-Wchar-subscripts \
	-Wparentheses \
	-Wmultichar \
	-Wtrigraphs \
	-Wpointer-arith \
	-Wcast-align \
	-Wreturn-type \
	-Wno-unused-function \
	$(SPACE)

CWARN_FLAGS := $(CXXWARN_FLAGS) \
	-Wstrict-prototypes \
	-Wmissing-prototypes \
	-Wmissing-declarations \
	-Wnested-externs \
	-Wmain \

LIB_ARCH        := $(OSARCH)

CXXFLAGS  := $(CXXWARN_FLAGS) $(CXX_ARCH_FLAGS)
CFLAGS    := $(CWARN_FLAGS) $(CXX_ARCH_FLAGS)
LINK      += $(CXX_ARCH_FLAGS)


COMMONFLAGS += $(INCLUDES) -g
LIBSUFFIX   := D

NVCCFLAGS       += -m32
LIB_ARCH         = i386
CUDPPLIB_SUFFIX  = i386

OPENGLLIB := -lGL -lGLU -lX11 -lXi -lXmu
OPENGLLIB += -lGLEW -L/usr/X11R6/lib
OPENGLLIB += -lglut -L/usr/lib 
OPENGLLIB += $(INCCC)

LIB       := ${USRLIBDIR} -L${OCLLIBDIR} -L$(LIBDIR) -L$(SHAREDDIR)/lib/$(OSLOWER) 
LIB += -lOpenCL ${OPENGLLIB} ${LIB} 

ifneq ($(STATIC_LIB),)
	TARGETDIR := $(OCLLIBDIR)
	TARGET   := $(subst .a,_$(LIB_ARCH)$(LIBSUFFIX).a,$(OCLLIBDIR)/$(STATIC_LIB))
	LINKLINE  = ar qv $(TARGET) $(OBJS) 
else
	LIB += -loclUtil_$(LIB_ARCH)$(LIBSUFFIX) -lshrutil_$(LIB_ARCH)$(LIBSUFFIX)
	TARGETDIR := $(BINDIR)/$(BINSUBDIR)
	TARGET    := $(TARGETDIR)/$(EXECUTABLE)
	LINKLINE  = $(LINK) -o $(TARGET) $(OBJS) $(LIB)
endif

CXXFLAGS  += $(COMMONFLAGS)
CFLAGS    += $(COMMONFLAGS)
#OBJDIR := $(ROOTOBJDIR)/$(BINSUBDIR)
OBJS +=  $(patsubst %.cpp,$(OBJDIR)/%.cpp.o,$(notdir $(CCFILES)))
OBJS +=  $(patsubst %.c,$(OBJDIR)/%.c.o,$(notdir $(CFILES)))

$(OBJDIR)/%.c.o : $(SRCDIR)%.c $(C_DEPS)
	$(VERBOSE)$(CC) $(CFLAGS) -o $@ -c $<

$(OBJDIR)/%.cpp.o : $(SRCDIR)%.cpp $(C_DEPS)
	$(VERBOSE)$(CXX) $(CXXFLAGS) -o $@ -c $<

$(TARGET): makedirectories $(OBJS) Makefile
	$(VERBOSE)$(LINKLINE)

makedirectories:
	$(VERBOSE)mkdir -p $(LIBDIR)
	$(VERBOSE)mkdir -p $(OBJDIR)
	$(VERBOSE)mkdir -p $(TARGETDIR)


tidy :
	$(VERBOSE)find . | egrep "#" | xargs rm -f
	$(VERBOSE)find . | egrep "\~" | xargs rm -f

clean : tidy
	$(VERBOSE)rm -f $(OBJS)
	$(VERBOSE)rm -f $(TARGET)

clobber : clean
	$(VERBOSE)rm -rf $(ROOTOBJDIR)
	$(VERBOSE)find $(TARGETDIR) | egrep "ptx" | xargs rm -f
	$(VERBOSE)find $(TARGETDIR) | egrep "txt" | xargs rm -f
	$(VERBOSE)rm -f $(TARGETDIR)/samples.list

################################################################################
# Rules and targets

# NOTE: Assuming P4 based install until OpenCL becomes public
# Adjust P4_Root, default is ${HOME}/perforce/
# P4_ROOT=${HOME}/myperforce/

# include ../../common/common_opencl.mk


