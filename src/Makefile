#
# OMNeT++/OMNEST Makefile for wsn-energy
#
# This file was generated with the command:
#  opp_makemake -f --deep
#

# Name of target to be created (-o option)
TARGET = wsn-energy$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I. \
    -Iapps \
    -Iapps/client \
    -Iapps/server \
    -Icore \
    -Icore/net \
    -Icore/net/ip \
    -Icore/rpl \
    -Iworld

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS =

# Output directory
PROJECT_OUTPUT_DIR = ../out
PROJECTRELATIVE_PATH = src
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/apps/client/client.o \
    $O/apps/server/server.o \
    $O/core/core.o \
    $O/world/tranmission.o \
    $O/world/enviroment.o \
    $O/core/net/ip/ipPacket_m.o

# Message files
MSGFILES = \
    core/net/ip/ipPacket.msg

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppmain$D $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS)  $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ($(MAKECMDGOALS),depend)
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $O/$(TARGET)
	$(Q)$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	@echo Creating executable: $@
	$(Q)$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY: all clean cleanall depend msgheaders

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(CXXFLAGS) $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	$(qecho) Cleaning...
	$(Q)-rm -rf $O
	$(Q)-rm -f wsn-energy wsn-energy.exe libwsn-energy.so libwsn-energy.a libwsn-energy.dll libwsn-energy.dylib
	$(Q)-rm -f ./*_m.cc ./*_m.h
	$(Q)-rm -f apps/*_m.cc apps/*_m.h
	$(Q)-rm -f apps/client/*_m.cc apps/client/*_m.h
	$(Q)-rm -f apps/server/*_m.cc apps/server/*_m.h
	$(Q)-rm -f core/*_m.cc core/*_m.h
	$(Q)-rm -f core/net/*_m.cc core/net/*_m.h
	$(Q)-rm -f core/net/ip/*_m.cc core/net/ip/*_m.h
	$(Q)-rm -f core/rpl/*_m.cc core/rpl/*_m.h
	$(Q)-rm -f world/*_m.cc world/*_m.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc apps/*.cc apps/client/*.cc apps/server/*.cc core/*.cc core/net/*.cc core/net/ip/*.cc core/rpl/*.cc world/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/apps/client/client.o: apps/client/client.cc \
	apps/client/client.h \
	core/core.h
$O/apps/server/server.o: apps/server/server.cc \
	apps/server/server.h \
	core/core.h
$O/core/core.o: core/core.cc \
	core/core.h \
	world/enviroment.h \
	world/tranmission.h
$O/core/net/ip/ipPacket_m.o: core/net/ip/ipPacket_m.cc \
	core/net/ip/ipPacket_m.h
$O/world/enviroment.o: world/enviroment.cc \
	core/core.h \
	world/enviroment.h \
	world/tranmission.h
$O/world/tranmission.o: world/tranmission.cc \
	core/core.h \
	world/tranmission.h

