cmake_minimum_required(VERSION 3.10)

set (PROJECT_NAME eez-flow-template-sdl)

project(${PROJECT_NAME})

set (CMAKE_CXX_STANDARD 17)

if(MSVC)
  set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /W4 /wd4100 /wd4214 /wd4200 /wd4244 /wd4456 /wd4457 /wd4458 /wd4459 /wd4245 /wd4389 /wd4706 /wd4611 /wd4310")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

if(${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wunused-const-variable -Wno-nested-anon-types -Wno-dollar-in-identifier-extension -O2 -sUSE_SDL=2")
    set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_CXX_FLAGS} -s DEMANGLE_SUPPORT=1 -s FORCE_FILESYSTEM=1 -s ALLOW_MEMORY_GROWTH=1 -s INITIAL_MEMORY=83886080 -s LLD_REPORT_UNDEFINED -sUSE_SDL=2 --bind -lidbfs.js --pre-js ${PROJECT_SOURCE_DIR}/src/platform/simulator/emscripten/pre.js")
    #set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} --preload-file ../../images/eez.png")
    add_definitions(-DEMCC_DEBUG)
endif()

if(NOT(${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten"))
    set(SDL2_BUILDING_LIBRARY 1)
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    include_directories(SYSTEM ${SDL2_INCLUDE_DIRS})
    include_directories(SYSTEM ${SDL2IMAGE_INCLUDE_DIR})
endif()

if (UNIX)
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fpermissive -pedantic")
endif (UNIX)

add_definitions(-DEEZ_PLATFORM_SIMULATOR)

if(WIN32)
    ENABLE_LANGUAGE(RC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-DEEZ_PLATFORM_SIMULATOR_WIN32)
endif()

if (UNIX)
    add_definitions(-DEEZ_PLATFORM_SIMULATOR_UNIX)
endif()

if(${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
    add_definitions(-DEEZ_PLATFORM_SIMULATOR_EMSCRIPTEN)
endif()

include_directories(
    ./src
    ./eez-framework/src
    ./eez-framework/src/eez/libs/agg
    ./eez-framework/src/eez/platform/simulator
)


set(src_files)
set(header_files)


################################################################################
# EEZ Framework files
file(GLOB_RECURSE src_eez
    ./eez-framework/src/eez/*.cpp
    ./eez-framework/src/eez/*.c
)
file(GLOB_RECURSE header_eez
    ./eez-framework/src/eez/*.h
)

# exclude STM32 platform specific files
set (EXCLUDE_DIR "./eez-framework/src/eez/platform/stm32")
foreach (TMP_PATH ${src_eez})
    string (FIND ${TMP_PATH} ${EXCLUDE_DIR} EXCLUDE_DIR_FOUND)
    if (NOT ${EXCLUDE_DIR_FOUND} EQUAL -1)
        list (REMOVE_ITEM src_eez ${TMP_PATH})
    endif ()
endforeach(TMP_PATH)
foreach (TMP_PATH ${header_eez})
    string (FIND ${TMP_PATH} ${EXCLUDE_DIR} EXCLUDE_DIR_FOUND)
    if (NOT ${EXCLUDE_DIR_FOUND} EQUAL -1)
        list (REMOVE_ITEM header_eez ${TMP_PATH})
    endif ()
endforeach(TMP_PATH)

# exclude libscpi
set (EXCLUDE_DIR "./eez-framework/src/eez/libs/libscpi")
foreach (TMP_PATH ${src_eez})
    string (FIND ${TMP_PATH} ${EXCLUDE_DIR} EXCLUDE_DIR_FOUND)
    if (NOT ${EXCLUDE_DIR_FOUND} EQUAL -1)
        list (REMOVE_ITEM src_eez ${TMP_PATH})
    endif ()
endforeach(TMP_PATH)
foreach (TMP_PATH ${header_eez})
    string (FIND ${TMP_PATH} ${EXCLUDE_DIR} EXCLUDE_DIR_FOUND)
    if (NOT ${EXCLUDE_DIR_FOUND} EQUAL -1)
        list (REMOVE_ITEM header_eez ${TMP_PATH})
    endif ()
endforeach(TMP_PATH)

list (APPEND src_files ${src_eez})
list (APPEND header_files ${header_eez})

source_group(TREE "../../eez-framework/src/eez" PREFIX "eez" FILES ${src_eez} ${header_eez})

# TODO
#if(MSVC)
#    set_source_files_properties(${src_eez_libs_libscpi} PROPERTIES COMPILE_FLAGS /W0)
#endif()

################################################################################


################################################################################
# SAMPLE files
file(GLOB_RECURSE src_sample
    src/*.cpp
    src/*.c
)
file(GLOB_RECURSE header_sample
    src/*.h
)

list (APPEND src_files ${src_sample})
list (APPEND header_files ${header_sample})

source_group(TREE "../../src" PREFIX "src" FILES ${src_sample} ${header_sample})

################################################################################


if(WIN32)
    set(src_win32_specific
        ./src/platform/simulator/win32/icon.rc
    ) 
    list (APPEND src_files ${src_win32_specific})
    source_group("win32" FILES ${src_win32_specific})

    set(SOURCES src/platform/simulator/win32/icon.rc ${src_files})
endif()

add_executable(${PROJECT_NAME} ${src_files} ${header_files})

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE "/MP")
endif()

if (UNIX AND NOT(${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten"))
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
    target_link_libraries(${PROJECT_NAME} Threads::Threads bsd)
endif ()

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

if(WIN32)
    target_link_libraries(${PROJECT_NAME} wsock32 ws2_32)

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PROJECT_SOURCE_DIR}/$ENV{SDL2DIR}/lib/x86/SDL2.dll"
            $<TARGET_FILE_DIR:${PROJECT_NAME}>)

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PROJECT_SOURCE_DIR}/$ENV{SDL2IMAGEDIR}/lib/x86/libjpeg-9.dll"
            $<TARGET_FILE_DIR:${PROJECT_NAME}>)
    
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PROJECT_SOURCE_DIR}/$ENV{SDL2IMAGEDIR}/lib/x86/libpng16-16.dll"
            $<TARGET_FILE_DIR:${PROJECT_NAME}>)

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PROJECT_SOURCE_DIR}/$ENV{SDL2IMAGEDIR}/lib/x86/libtiff-5.dll"
            $<TARGET_FILE_DIR:${PROJECT_NAME}>)

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PROJECT_SOURCE_DIR}/$ENV{SDL2IMAGEDIR}/lib/x86/libwebp-7.dll"
            $<TARGET_FILE_DIR:${PROJECT_NAME}>)

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PROJECT_SOURCE_DIR}/$ENV{SDL2IMAGEDIR}/lib/x86/SDL2_image.dll"
            $<TARGET_FILE_DIR:${PROJECT_NAME}>)

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PROJECT_SOURCE_DIR}/$ENV{SDL2IMAGEDIR}/lib/x86/zlib1.dll"
            $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()


if(${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/src/platform/simulator/emscripten"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()
