# ============================================================================
# common.mk - shared build rules for every scu example.
#
# Per-example Makefiles should set MODULE (the binary name) and SRCS (the
# source files), then `include` this fragment. A typical Makefile is:
#
#     MODULE = and_test
#     SRCS   = sc_main.cpp
#     include ../../common.mk
#
# The following variables are honoured:
#
#     SYSTEMC_HOME   Absolute path to the SystemC install prefix.
#                    Defaults to /usr/local/systemc.
#     SCU_HOME       Absolute path to the repository root. Auto-detected from
#                    the location of this file.
#     CXX            C++ compiler. Defaults to g++.
#     CXXFLAGS       Extra C++ flags. Appended to the library's defaults.
#     LDFLAGS        Extra linker flags.
#
# Targets:
#     all (default)  Build the example binary.
#     run            Build (if needed) and execute the binary.
#     view           Open tf.vcd in GTKWave (for examples that produce traces).
#     clean          Remove objects, binary and generated .vcd traces.
# ============================================================================

# Absolute directory containing this file.
SCU_COMMON_MK_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

# Repository layout assumed: <SCU_HOME>/scu/moduleTest/common.mk
SCU_HOME     ?= $(abspath $(SCU_COMMON_MK_DIR)/../..)
SYSTEMC_HOME ?= /usr/local/systemc
CXX          ?= g++

# Pick the first SystemC library directory that actually exists.
SYSTEMC_LIBDIR := $(firstword \
    $(wildcard $(SYSTEMC_HOME)/lib-linux64) \
    $(wildcard $(SYSTEMC_HOME)/lib-linux) \
    $(wildcard $(SYSTEMC_HOME)/lib-macos) \
    $(wildcard $(SYSTEMC_HOME)/lib))

ifeq ($(strip $(SYSTEMC_LIBDIR)),)
$(warning Could not locate SystemC libraries under $(SYSTEMC_HOME). \
Set SYSTEMC_HOME to your SystemC install prefix.)
endif

MODULE ?= sim
SRCS   ?= $(wildcard *.cpp) $(wildcard *.C)
OBJS   := $(addsuffix .o,$(basename $(SRCS)))

INCDIRS  := -I. -I.. -I$(SYSTEMC_HOME)/include -I$(SCU_HOME)/scu
LIBDIRS  := -L$(SYSTEMC_LIBDIR)
LIBS     := -lsystemc -lm

# Library-provided defaults. User-provided CXXFLAGS/LDFLAGS are appended so
# they can override or extend these.
SCU_CXXFLAGS := -g -O2 -Wall -Wno-deprecated $(INCDIRS)
SCU_LDFLAGS  := $(LIBDIRS)

EXE := $(MODULE)

.PHONY: all run view clean
.SUFFIXES: .cpp .C .o

all: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(SCU_CXXFLAGS) $(CXXFLAGS) $(SCU_LDFLAGS) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

%.o: %.cpp
	$(CXX) $(SCU_CXXFLAGS) $(CXXFLAGS) -c -o $@ $<

%.o: %.C
	$(CXX) $(SCU_CXXFLAGS) $(CXXFLAGS) -c -o $@ $<

run: $(EXE)
	./$(EXE)

view: tf.vcd
	gtkwave tf.vcd

clean:
	rm -f $(OBJS) $(EXE) *~ core *.vcd
