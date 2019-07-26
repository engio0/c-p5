CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
PROJECT (mySample)

FIND_PACKAGE(wxWidgets COMPONENTS base core base adv REQUIRED) # other components can be added
INCLUDE(${wxWidgets_USE_FILE})

ADD_EXECUTABLE(mySample WIN32 main.cpp MyProject.cpp MyDerivedFrame.cpp)
TARGET_LINK_LIBRARIES(mySample ${wxWidgets_LIBRARIES})
