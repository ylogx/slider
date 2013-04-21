cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

PROJECT(demo)

FIND_PACKAGE(Qt4 REQUIRED)

SET(QT_USE_QTDBUS TRUE)   #this little line almost ruined my day

SET(demo_SOURCES main.cpp mainwindow.cpp)
SET(demo_HEADERS mainwindow.h)
SET(demo_FORMS mainwindow.ui)

QT4_WRAP_CPP(demo_HEADERS_MOC ${demo_HEADERS})
QT4_WRAP_UI(demo_FORMS_HEADERS ${demo_FORMS})

INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

#add_executable (demo main.cpp mainwindow.h mainwindow.cpp mainwindow.ui)
ADD_EXECUTABLE(demo ${demo_SOURCES} 
    ${demo_HEADERS_MOC}
    ${demo_FORMS_HEADERS})
TARGET_LINK_LIBRARIES(demo ${QT_LIBRARIES})
