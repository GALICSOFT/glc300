
APP_PLATFORM := android-16
APP_ABI      := armeabi armeabi-v7a
APP_STL      := gnustl_static
APP_CPPFLAGS += -fexceptions -frtti
APP_CPPFLAGS += -w -fno-common -march=armv5te -mtune=arm9tdmi -mapcs -msoft-float -fno-short-enums
