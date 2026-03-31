cmake_minimum_required(VERSION 3.14)
project(calculator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
file(GLOB_RECURSE SRC_FILES "${SRC_DIR}/*.cpp")

add_executable(${PROJECT_NAME} ${SRC_FILES})

include(FetchContent)

FetchContent_Declare(
    math
    GIT_REPOSITORY https://github.com/montegost/math.git
    GIT_TAG        main
)

FetchContent_MakeAvailable(math)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${math_SOURCE_DIR}/include
)


# install
include(GNUInstallDirs)
 
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)


# clang-format
find_program(CLANG_FORMAT_EXE NAMES clang-format)
 
if(CLANG_FORMAT_EXE)
    file(GLOB_RECURSE ALL_SOURCE_FILES
        "${SRC_DIR}/*.cpp"
        "${SRC_DIR}/*.h"
        "${SRC_DIR}/*.hpp"
    )
 
    add_custom_target(format
        COMMAND ${CLANG_FORMAT_EXE}
            -i
            -style=file:${CMAKE_SOURCE_DIR}/clang-format
            ${ALL_SOURCE_FILES}
        COMMENT "Running clang-format..."
        VERBATIM
    )
 
    add_dependencies(${PROJECT_NAME} format)
else()
    message(WARNING "clang-format not found — target 'format' unavailable")
endif()

# clang-tidy
find_program(CLANG_TIDY_EXE NAMES clang-tidy)
 
if(CLANG_TIDY_EXE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_CLANG_TIDY "${CLANG_TIDY_EXE};--config-file=${CMAKE_SOURCE_DIR}/clang-tidy"
    )
else()
    message(WARNING "clang-tidy not found — static analysis disabled")
endif()
