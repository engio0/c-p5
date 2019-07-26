CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
PROJECT (minimal)

FIND_PACKAGE(wxWidgets COMPONENTS base core base adv REQUIRED) # other components can be added
INCLUDE(${wxWidgets_USE_FILE})

ADD_EXECUTABLE(minimal WIN32 minimal.cpp message.cpp)
TARGET_LINK_LIBRARIES(minimal ${wxWidgets_LIBRARIES})
