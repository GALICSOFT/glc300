# Copyright (C) 2012 GALICSOFT
#

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)


###############################################################################
# path
DEV_SDK   = E:/_Document/_Afew_work/glc300
EABISYS   = D:/android-ndk-r10/platforms/android-14/arch-arm/usr
STL_INC   = D:/android-ndk-r10/sources/cxx-stl/gnu-libstdc++/4.6


###############################################################################
#module name
LOCAL_MODULE    := g_pack_app


###############################################################################
#source file

LOCAL_SRC_FILES := g_pack.cpp
LOCAL_SRC_FILES += galic_app.cpp
LOCAL_SRC_FILES += GameObject.cpp GpApp3.cpp GpApp2.cpp GpApp.cpp

###############################################################################
#library linking
LOCAL_LDLIBS    := -lgpan_i30 -lgpan_d30 -lgpan_t30 -lgpan_c30 -lgpan_b30
LOCAL_LDLIBS    += -lgpan_jpg -lgpan_png -lgpan_zlib -lgpan_ftf -lgpan_lua
LOCAL_LDLIBS    += -lgpan_oggvorbis -lgpan_ogg
LOCAL_LDLIBS    += -lgpan_sqlite -lgpan_tinyxml

LOCAL_LDLIBS    += -lGLESv2 -llog -lstdc++
LOCAL_LDLIBS    += -lOpenSLES
LOCAL_LDLIBS    += -lEGL -landroid

LOCAL_LDLIBS    += -L$(DEV_SDK)/lib


###############################################################################
#define, flag and header file include
LOCAL_CPPFLAGS  += -D__ANDROID__ -D__OPENSL_ES__ -std=c++11
LOCAL_CPPFLAGS  += -w -fno-common -march=armv5te -mtune=arm9tdmi
LOCAL_CPPFLAGS  += -mapcs -msoft-float -fno-short-enums
LOCAL_CPPFLAGS  += -fexceptions -frtti

LOCAL_CPPFLAGS  += -I./
LOCAL_CPPFLAGS  += -I./lsc
LOCAL_CPPFLAGS  += -I$(DEV_SDK)/include
LOCAL_CPPFLAGS  += -I$(STL_INC)/include
LOCAL_CPPFLAGS  += -I$(STL_INC)/libs/armeabi/include


include $(BUILD_SHARED_LIBRARY)
