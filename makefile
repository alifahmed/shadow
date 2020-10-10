##############################################################
#
#                   DO NOT EDIT THIS FILE!
#
##############################################################

# If the tool is built out of the kit, PIN_ROOT must be specified in the make invocation and point to the kit root.
PIN_ROOT=/home/alif/_tools/pin
ALIF_ROOTDIR=$(PWD)

ALIF_IDIR=$(ALIF_ROOTDIR)/include
ALIF_HEADERS:=$(shell find $(ALIF_IDIR) -name '*.h')

DEBUG=1
ifdef PIN_ROOT
CONFIG_ROOT := $(PIN_ROOT)/source/tools/Config
else
CONFIG_ROOT := ../Config
endif
include $(CONFIG_ROOT)/makefile.config
include makefile.rules
include $(TOOLS_ROOT)/Config/makefile.default.rules

##############################################################
#
#                   DO NOT EDIT THIS FILE!
#
##############################################################
