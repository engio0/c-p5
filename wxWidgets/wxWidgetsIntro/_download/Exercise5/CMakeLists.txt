CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
PROJECT (DrawingFrame)

FIND_PACKAGE(wxWidgets COMPONENTS base core base adv REQUIRED) # other components can be added
INCLUDE(${wxWidgets_USE_FILE})

ADD_EXECUTABLE(DrawingFrame WIN32 main.cpp DrawingGenerated.cpp DrawingFrame.cpp)
TARGET_LINK_LIBRARIES(DrawingFrame ${wxWidgets_LIBRARIES})
