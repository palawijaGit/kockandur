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

USEGLLIB	:= 1
USEGLUT		:= 1

#CXX        := g++
#CC         := gcc
#LINK       := g++ -fPIC

#CXXWARN_FLAGS := \
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

#CWARN_FLAGS := $(CXXWARN_FLAGS) \
	-Wstrict-prototypes \
	-Wmissing-prototypes \
	-Wmissing-declarations \
	-Wnested-externs \
	-Wmain \

#CXXFLAGS  += $(COMMONFLAGS)
#CFLAGS    += $(COMMONFLAGS)

# $(OBJDIR)/%.c.o : $(SRCDIR)%.c $(C_DEPS)
#	$(VERBOSE)$(CC) $(CFLAGS) -o $@ -c $<

# $(OBJDIR)/%.cpp.o : $(SRCDIR)%.cpp $(C_DEPS)
#	$(VERBOSE)$(CXX) $(CXXFLAGS) -o $@ -c $<

#OBJS +=  $( %.cpp,$(OBJDIR)/%.cpp.o,$(notdir $(CCFILES)))
#OBJS +=  $( %.c,$(OBJDIR)/%.c.o,$(notdir $(CFILES)))

#Proba.bin: $(OBJS) Makefile
#		   $(VERBOSE) $(LINKLINE)

################################################################################
# Rules and targets

# NOTE: Assuming P4 based install until OpenCL becomes public
# Adjust P4_Root, default is ${HOME}/perforce/
# P4_ROOT=${HOME}/myperforce/



include ../../common/common_opencl.mk


