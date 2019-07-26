mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS += runner.o \
calibration.o \
start.o \
tailcontrol.o \
balancer.o \
balancer_param.o \
linetrace.o \
touchsensor.o \
bluetooth.o \
colorsensor.o \
wheelmotor.o \
battery.o \
gyrosensor.o \
balancecontrol.o \
pidcontrol.o \
distance.o \

APPL_DIR += \
    $(mkfile_path)app/include \
    $(mkfile_path)app/lib/balancer

INCLUDES += \
    -I$(mkfile_path)app/include \
    -I$(mkfile_path)app/lib/balancer
