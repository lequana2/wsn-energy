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
    -Icore/battery \
    -Icore/mac \
    -Icore/mac/csma \
    -Icore/mac/nullmac \
    -Icore/net \
    -Icore/net/ipv6 \
    -Icore/net/rpl \
    -Icore/radio \
    -Icore/radio/cc2420 \
    -Icore/radio/nullradio \
    -Icore/rdc \
    -Icore/rdc/contikiMac \
    -Icore/rdc/nullrdc \
    -Imote \
    -Ipacket \
    -Iutil \
    -Iutil/statistic \
    -Iutil/transmission \
    -Iutil/world

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
    $O/core/battery/battery.o \
    $O/core/mac/mac.o \
    $O/core/mac/nullmac/nullMAC.o \
    $O/core/net/ipv6/ipv6.o \
    $O/core/net/rpl/rpl.o \
    $O/core/radio/radio.o \
    $O/core/radio/cc2420/cc2420.o \
    $O/core/radio/nullradio/nullRadio.o \
    $O/core/rdc/rdc.o \
    $O/core/rdc/nullrdc/nullRDC.o \
    $O/util/statistic/statistic.o \
    $O/util/transmission/transmission.o \
    $O/util/world/world.o \
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
	$(Q)-rm -f core/battery/*_m.cc core/battery/*_m.h
	$(Q)-rm -f core/mac/*_m.cc core/mac/*_m.h
	$(Q)-rm -f core/mac/csma/*_m.cc core/mac/csma/*_m.h
	$(Q)-rm -f core/mac/nullmac/*_m.cc core/mac/nullmac/*_m.h
	$(Q)-rm -f core/net/*_m.cc core/net/*_m.h
	$(Q)-rm -f core/net/ipv6/*_m.cc core/net/ipv6/*_m.h
	$(Q)-rm -f core/net/rpl/*_m.cc core/net/rpl/*_m.h
	$(Q)-rm -f core/radio/*_m.cc core/radio/*_m.h
	$(Q)-rm -f core/radio/cc2420/*_m.cc core/radio/cc2420/*_m.h
	$(Q)-rm -f core/radio/nullradio/*_m.cc core/radio/nullradio/*_m.h
	$(Q)-rm -f core/rdc/*_m.cc core/rdc/*_m.h
	$(Q)-rm -f core/rdc/contikiMac/*_m.cc core/rdc/contikiMac/*_m.h
	$(Q)-rm -f core/rdc/nullrdc/*_m.cc core/rdc/nullrdc/*_m.h
	$(Q)-rm -f mote/*_m.cc mote/*_m.h
	$(Q)-rm -f packet/*_m.cc packet/*_m.h
	$(Q)-rm -f util/*_m.cc util/*_m.h
	$(Q)-rm -f util/statistic/*_m.cc util/statistic/*_m.h
	$(Q)-rm -f util/transmission/*_m.cc util/transmission/*_m.h
	$(Q)-rm -f util/world/*_m.cc util/world/*_m.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc apps/*.cc apps/client/*.cc apps/server/*.cc core/*.cc core/battery/*.cc core/mac/*.cc core/mac/csma/*.cc core/mac/nullmac/*.cc core/net/*.cc core/net/ipv6/*.cc core/net/rpl/*.cc core/radio/*.cc core/radio/cc2420/*.cc core/radio/nullradio/*.cc core/rdc/*.cc core/rdc/contikiMac/*.cc core/rdc/nullrdc/*.cc mote/*.cc packet/*.cc util/*.cc util/statistic/*.cc util/transmission/*.cc util/world/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/apps/client/client.o: apps/client/client.cc \
	apps/app.h \
	apps/client/client.h \
	packet/packet_m.h
$O/apps/server/server.o: apps/server/server.cc \
	apps/app.h \
	apps/server/server.h
$O/core/battery/battery.o: core/battery/battery.cc \
	core/battery/battery.h \
	packet/packet_m.h
$O/core/mac/mac.o: core/mac/mac.cc \
	core/mac/mac.h \
	packet/packet_m.h
$O/core/mac/nullmac/nullMAC.o: core/mac/nullmac/nullMAC.cc \
	core/mac/mac.h \
	core/mac/nullmac/nullMAC.h \
	packet/packet_m.h
$O/core/net/ipv6/ipv6.o: core/net/ipv6/ipv6.cc \
	apps/app.h \
	core/net/ipv6/ipv6.h \
	core/net/rpl/rpl.h \
	core/radio/radio.h \
	packet/packet_m.h \
	util/statistic/statistic.h \
	util/transmission/transmission.h \
	util/world/world.h
$O/core/net/rpl/rpl.o: core/net/rpl/rpl.cc \
	core/net/ipv6/ipv6.h \
	core/net/rpl/rpl.h \
	packet/packet_m.h
$O/core/radio/radio.o: core/radio/radio.cc \
	core/battery/battery.h \
	core/radio/radio.h \
	packet/packet_m.h \
	util/statistic/statistic.h \
	util/transmission/transmission.h \
	util/world/world.h
$O/core/radio/cc2420/cc2420.o: core/radio/cc2420/cc2420.cc \
	core/battery/battery.h \
	core/radio/cc2420/cc2420-const.h \
	core/radio/cc2420/cc2420.h \
	core/radio/radio.h \
	packet/packet_m.h \
	util/statistic/statistic.h \
	util/transmission/transmission.h \
	util/world/world.h
$O/core/radio/nullradio/nullRadio.o: core/radio/nullradio/nullRadio.cc \
	core/battery/battery.h \
	core/radio/nullradio/nullRadio.h \
	core/radio/radio.h \
	packet/packet_m.h \
	util/statistic/statistic.h \
	util/transmission/transmission.h \
	util/world/world.h
$O/core/rdc/rdc.o: core/rdc/rdc.cc \
	core/rdc/rdc.h \
	packet/packet_m.h
$O/core/rdc/nullrdc/nullRDC.o: core/rdc/nullrdc/nullRDC.cc \
	core/rdc/nullrdc/nullRDC.h \
	core/rdc/rdc.h \
	packet/packet_m.h
$O/packet/packet_m.o: packet/packet_m.cc \
	packet/packet_m.h
$O/util/statistic/statistic.o: util/statistic/statistic.cc \
	core/battery/battery.h \
	packet/packet_m.h \
	util/statistic/statistic.h
$O/util/transmission/transmission.o: util/transmission/transmission.cc \
	core/radio/radio.h \
	packet/packet_m.h \
	util/transmission/transmission.h
$O/util/world/world.o: util/world/world.cc \
	core/radio/radio.h \
	packet/packet_m.h \
	util/transmission/transmission.h \
	util/world/world.h

