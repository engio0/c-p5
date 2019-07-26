CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
PROJECT (MyEventFrame)

FIND_PACKAGE(wxWidgets COMPONENTS base core base adv REQUIRED) # other components can be added
INCLUDE(${wxWidgets_USE_FILE})

ADD_EXECUTABLE(MyEventFrame WIN32 main.cpp MyEventFrame.cpp FrameProject.cpp)
TARGET_LINK_LIBRARIES(MyEventFrame ${wxWidgets_LIBRARIES})
