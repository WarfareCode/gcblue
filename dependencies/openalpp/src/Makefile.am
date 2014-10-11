
INCLUDES = -I$(top_builddir)/include

basicfiles = \
    audioenvironment.cpp \
    listener.cpp \
    audiobase.cpp \
    sourcebase.cpp \
    source.cpp \
    sample.cpp \
    sounddata.cpp \
    audioconvert.cpp \
    error.cpp \
    groupsource.cpp \
    referenced.cpp
streamfiles = \
    streamupdater.cpp \
    stream.cpp
if WITH_OGGVORBIS
oggfiles = \
    filestream.cpp \
    filestreamupdater.cpp
else
oggfiles = nofilestream.cpp
endif
if WITH_PORTAUDIO
devicefiles = \
    deviceupdater.cpp \
    inputdevice.cpp
else
devicefiles = noinputdevice.cpp
endif
#streamfiles=nostreaming.cpp noinputdevice.cpp nofilestream.cpp

libopenalpp_la_SOURCES = $(basicfiles) $(streamfiles) $(devicefiles) $(oggfiles)


lib_LTLIBRARIES = libopenalpp.la


