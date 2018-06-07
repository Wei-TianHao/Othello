SOURCES += \
    $$PWD/BackEnd/othello/eva.cc \
    $$PWD/BackEnd/othello/naive.cc \
    $$PWD/BackEnd/othello/OthelloState.cc \
    $$PWD/BackEnd/main.cpp \
    $$PWD/BackEnd/Piece.cpp \
    $$PWD/BackEnd/SuperWindow.cpp

HEADERS  += \
    $$PWD/BackEnd/othello/eva.hpp \
    $$PWD/BackEnd/othello/naive.hpp \
    $$PWD/BackEnd/othello/OthelloState.hpp \
    $$PWD/BackEnd/AIControl.hpp \
    $$PWD/BackEnd/Piece.h \
    $$PWD/BackEnd/SuperWindow.h \
    $$PWD/../../../../Downloads/RNG-master/rng.h \
    $$PWD/BackEnd/othello/rng.h

FORMS    += FrontEnd/SuperWindow.ui

RESOURCES += Images/image.qrc
