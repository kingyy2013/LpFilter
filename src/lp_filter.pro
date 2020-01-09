HEADERS += \
    filter_weights.h \
    qtglrenderres.h \
    ctrlwindow.h \
    qsliderspinbox.h \
    prewindow.h

SOURCES += \
    filter_weights.cpp \
    qtglrenderres.cpp \
    main.cpp \
    ctrlwindow.cpp \
    qsliderspinbox.cpp \
    prewindow.cpp

QT           += opengl gui

LIBS+= -lopengl32 -lglu32

OTHER_FILES += \
    Basic.vsh \
    Basic.fsh

RESOURCES += \
    Shaders.qrc

DISTFILES += \
  blur.txt
