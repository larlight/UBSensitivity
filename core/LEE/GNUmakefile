#
# This is an example GNUmakefile for my packages
#

# specific names for this package
DICT  = LEECint
SHLIB = libLEE.so
SOURCES = $(wildcard *.cc)
HEADERS = $(wildcard *.hh)
OBJECTS = $(SOURCES:.cc=.o)

# include options for this package
INCFLAGS  = -I$(LITE_FMWK_COREDIR)
INCFLAGS += -I./                       #Include itself

# platform-specific options
OSNAME          = $(shell uname -s)
HOST            = $(shell uname -n)
OSNAMEMODE      = $(OSNAME)

include $(LITE_FMWK_BASEDIR)/Makefile/Makefile.${OSNAME}

# set compiler options for ROOT
CXXFLAGS +=  `root-config --cflags`

# call the common GNUmakefile
include $(LITE_FMWK_BASEDIR)/Makefile/GNUmakefile.CORE



