#!/bin/make
SHELL=/bin/bash

#Define the virtual paths
vpath %.cpp src/
vpath %.hpp inc/
vpath %.o obj/

#Set some of the compile options
CXX = g++
CINCLUDEDIRS = -Iinc
CXXFLAGS = -fPIC -g -std=c++11 -Wall $(CINCLUDEDIRS)
LDLIBS = -ldl -lpthread
c++SrcSuf = cpp

#Add the root information to the compilation
CXXFLAGS     += $(shell root-config --cflags)
LDFLAGS      += $(shell root-config --ldflags)
LDLIBS       += $(shell root-config --libs)


#Set the name of the program to be compiled
PROGRAM = test

#Define Objects
MAINO = main.o
VANDLETIMINGO = VandleTimingFunction.o
EMCALTIMINGO  = EmCalTimingFunction.o
TRACEO = Trace.o

#Make the object list and prefix the object directory
OBJS = $(MAINO) $(VANDLETIMINGO) $(TRACEO) $(EMCALTIMINGO)
OBJDIR = obj
OBJS_W_DIR = $(addprefix $(OBJDIR)/,$(OBJS))

.SUFFIXES: .$(c++SrcSuf)

all: $(OBJS_W_DIR) $(PROGRAM)

$(OBJS_W_DIR): | $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

$(PROGRAM): $(OBJS_W_DIR)
	$(CXX) $(CXXFLAGS) $(LDLIBS) $^ -o $@

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean so
clean:
	@echo "Cleaning..."
	@rm -f $(OBJDIR)/*.o $(PROGRAM) *~ src/*~ include/*~
