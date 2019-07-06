
SET(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/installed)

install(DIRECTORY data
        DESTINATION .)

install(DIRECTORY shader
        DESTINATION .)