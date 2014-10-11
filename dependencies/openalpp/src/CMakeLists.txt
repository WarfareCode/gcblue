SET(SOURCEFILES audiobase audioconvert audioenvironment error groupsource listener sample sounddata source sourcebase referenced)

IF(CCGNU_FOUND)
  SET(SOURCEFILES ${SOURCEFILES} stream netstream streamupdater netupdater)
  IF(PORTAUDIO_FOUND)
    SET(SOURCEFILES ${SOURCEFILES} inputdevice deviceupdater)
  ELSE(PORTAUDIO_FOUND)
    SET(SOURCEFILES ${SOURCEFILES} noinputdevice)
  ENDIF(PORTAUDIO_FOUND)
  IF(VORBIS_FOUND)
    SET(SOURCEFILES ${SOURCEFILES} filestream filestreamupdater)
  ELSE(VORBIS_FOUND)
    SET(SOURCEFILES ${SOURCEFILES} nofilestream)
  ENDIF(VORBIS_FOUND)
ELSE(CCGNU_FOUND)
  SET(SOURCEFILES ${SOURCEFILES} nostreaming noinputdevice nofilestream)
ENDIF(CCGNU_FOUND)

ADD_LIBRARY(openalpp SOURCEFILES)
