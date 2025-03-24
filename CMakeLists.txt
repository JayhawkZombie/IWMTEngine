cmake_minimum_required(VERSION 3.30)
include(FetchContent)
project(IWMTEngine)

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed")
set(CMAKE_FRAMEWORK_PATH "")
set(CMAKE_OSX_DEPLOYMENT_TARGET "14.0")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE DEBUG)

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "/path/to/vcpkg/installed/x64-osx/debug/lib")

find_package(SFML COMPONENTS system window graphics network audio CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)
find_package(cereal CONFIG REQUIRED)
find_package(sol2 CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

file(GLOB_RECURSE HEADER_FILES ${PROJECT_SOURCE_DIR}/src/*.h ${PROJECT_SOURCE_DIR}/src/*.hpp)
file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
set(SRC_START ${CMAKE_CURRENT_SOURCE_DIR}/src)
list(APPEND SRC_FILES ${HEADER_FILES})

set(CODEGEN_SCRIPT ${PROJECT_SOURCE_DIR}/src/scripts/codegen/gen-all.py)
set(CODEGEN_OUTPUT_REFL ${PROJECT_SOURCE_DIR}/src/GeneratedReflectionData.cpp)
set(CODEGEN_OUTPUT_SERIAL ${PROJECT_SOURCE_DIR}/src/GeneratedSerializationData.h)
list(APPEND SRC_FILES ${CODEGEN_OUTPUT_REFL})
list(APPEND SRC_FILES ${CODEGEN_OUTPUT_SERIAL})

add_custom_command(
        OUTPUT ${CODEGEN_OUTPUT_REFL} ${CODEGEN_OUTPUT_SERIAL}
        COMMAND python3 ${CODEGEN_SCRIPT}
        --input ${SRC_START} #,${LEVELS_DIR}
        --output ${CODEGEN_OUTPUT_REFL},${CODEGEN_OUTPUT_SERIAL}
        -v
        DEPENDS ${SRC_START} ${CODEGEN_SCRIPT}
        COMMENT "Generating reflection data from header files"
        VERBATIM
)

# Custom target to ensure generation happens before build
add_custom_target(GenerateReflectionData ALL
        DEPENDS ${PROJECT_SOURCE_DIR}/src/GeneratedReflectionData.cpp ${PROJECT_SOURCE_DIR}/src/GeneratedSerializationData.h ${SRC_FILES}
        COMMENT "Running reflection generation script"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(IWMTEngine ${SRC_FILES})
add_dependencies(IWMTEngine GenerateReflectionData)

target_include_directories(IWMTEngine PRIVATE ${PROJECT_SOURCE_DIR}/src)
target_include_directories(IWMTEngine PRIVATE ${PROJECT_SOURCE_DIR}/src/ThirdParty)
target_link_libraries(IWMTEngine PRIVATE EnTT::EnTT)
target_link_libraries(IWMTEngine PRIVATE fmt::fmt)
target_link_libraries(IWMTEngine PRIVATE sol2)
target_link_libraries(IWMTEngine PRIVATE ImGui-SFML::ImGui-SFML cereal::cereal)
target_link_libraries(IWMTEngine PRIVATE spdlog::spdlog)
target_link_libraries(IWMTEngine PRIVATE sfml-system sfml-window sfml-network sfml-graphics sfml-audio)
target_link_libraries(IWMTEngine PRIVATE "-framework OpenGL" "-framework CoreFoundation")
