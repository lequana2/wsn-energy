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
    -Icore/mac \
    -Icore/net \
    -Icore/net/rpl \
    -Imote \
    -Ipacket \
    -Iplatform \
    -Iplatform/battery \
    -Iplatform/radio \
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
    $O/apps/app.o \
    $O/apps/client/client.o \
    $O/apps/server/server.o \
    $O/core/core.o \
    $O/core/net/rpl/rpl.o \
    $O/platform/battery/battery.o \
    $O/platform/radio/radio.o \
    $O/platform/radio/transmission.o \
    $O/world/statistic.o \
    $O/world/world.o \
    $O/packet/packet_m.o

# Message files
MSGFILES = \
    packet/packet.msg

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
	$(Q)-rm -f core/mac/*_m.cc core/mac/*_m.h
	$(Q)-rm -f core/net/*_m.cc core/net/*_m.h
	$(Q)-rm -f core/net/rpl/*_m.cc core/net/rpl/*_m.h
	$(Q)-rm -f mote/*_m.cc mote/*_m.h
	$(Q)-rm -f packet/*_m.cc packet/*_m.h
	$(Q)-rm -f platform/*_m.cc platform/*_m.h
	$(Q)-rm -f platform/battery/*_m.cc platform/battery/*_m.h
	$(Q)-rm -f platform/radio/*_m.cc platform/radio/*_m.h
	$(Q)-rm -f world/*_m.cc world/*_m.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc apps/*.cc apps/client/*.cc apps/server/*.cc core/*.cc core/mac/*.cc core/net/*.cc core/net/rpl/*.cc mote/*.cc packet/*.cc platform/*.cc platform/battery/*.cc platform/radio/*.cc world/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/apps/app.o: apps/app.cc \
	apps/app.h
$O/apps/client/client.o: apps/client/client.cc \
	apps/app.h \
	apps/client/client.h
$O/apps/server/server.o: apps/server/server.cc \
	apps/app.h \
	apps/server/server.h \
	core/core.h \
	core/net/rpl/rpl.h \
	packet/packet_m.h
$O/core/core.o: core/core.cc \
	apps/app.h \
	core/core.h \
	core/net/rpl/rpl.h \
	packet/packet_m.h \
	platform/radio/radio.h \
	platform/radio/transmission.h \
	world/statistic.h \
	world/world.h
$O/core/net/rpl/rpl.o: core/net/rpl/rpl.cc \
	core/core.h \
	core/net/rpl/rpl.h \
	packet/packet_m.h
$O/packet/packet_m.o: packet/packet_m.cc \
	packet/packet_m.h
$O/platform/battery/battery.o: platform/battery/battery.cc \
	platform/battery/battery.h
$O/platform/radio/radio.o: platform/radio/radio.cc \
	packet/packet_m.h \
	platform/radio/radio.h \
	platform/radio/transmission.h \
	world/statistic.h \
	world/world.h
$O/platform/radio/transmission.o: platform/radio/transmission.cc \
	packet/packet_m.h \
	platform/radio/radio.h \
	platform/radio/transmission.h
$O/world/statistic.o: world/statistic.cc \
	world/statistic.h
$O/world/world.o: world/world.cc \
	packet/packet_m.h \
	platform/radio/radio.h \
	platform/radio/transmission.h \
	world/world.h

