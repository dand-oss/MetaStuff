cmake_minimum_required( VERSION 2.8 )
project( MetaStuff )

###############
# ASI default settings
list(APPEND CMAKE_MODULE_PATH "$ENV{ASV_CMAKE}")
include(asv_cmake_defaults)
asv_cmake_defaults( )
###############

option(WITH_EXAMPLES "Build examples" ON)

include(GNUInstallDirs)

# copy the h files
install(
    DIRECTORY include
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${CMAKE_PROJECT_NAME}
    ) 

if(WITH_EXAMPLES)
    add_subdirectory(example)
endif(WITH_EXAMPLES)
