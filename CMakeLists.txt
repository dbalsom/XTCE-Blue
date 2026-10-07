cmake_minimum_required(VERSION 3.16)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# prevent installing to system directories. 
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}" CACHE INTERNAL "")

# Declare the project
project(xtce-blue)

if (APPLE OR EMSCRIPTEN)
    set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "")    # Disable shared builds on platforms where it does not make sense to use them
endif()

if(MSVC)
    if(NOT CMAKE_GENERATOR STREQUAL "Ninja")
        add_compile_options(/MP)				# parallelize each target, unless Ninja is the generator
        add_compile_options(/std:c++latest)
    endif()
endif()

# Set the name of the executable
set(EXECUTABLE_NAME ${PROJECT_NAME})

add_executable(${EXECUTABLE_NAME}
        src/core/cpu_types.h
        src/frontend/Composite.h)

target_include_directories(${EXECUTABLE_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src/core
        ${CMAKE_SOURCE_DIR}/src/moo
        ${CMAKE_SOURCE_DIR}/src/third_party/blip_buffer
        ${CMAKE_SOURCE_DIR}/src/third_party/CLI11)

# Add your sources to the target
target_sources(${EXECUTABLE_NAME} 
    PRIVATE
        src/main.cpp
        src/benchmark.cpp
        src/benchmark.h
        src/core/Machine.cpp
        src/core/Machine.h
        src/xtce_blue.h
        src/core/bios.h
        src/core/font.h
        src/core/Dmac.h
        src/core/Pic.h
        src/core/Pit.h
        src/core/Ppi.h
        src/core/Disassembler.h
        src/core/Cga.cpp
        src/core/Cga.h
        src/core/Crtc.cpp
        src/core/Crtc.h
        src/frontend/DisplayRenderer.cpp
        src/frontend/DisplayRenderer.h
        src/gui/imgui_memory_editor.h
        src/gui/DebuggerManager.h
        src/gui/DebuggerManager.cpp
        src/gui/DisassemblyWindow.h
        src/gui/DisassemblyWindow.cpp
        src/gui/CpuStatusWindow.h
        src/gui/CpuStatusWindow.cpp
        src/gui/MemoryViewerWindow.cpp
        src/gui/MemoryViewerWindow.h
        src/gui/CycleLogWindow.cpp
        src/gui/CycleLogWindow.h
        src/gui/StackViewerWindow.cpp
        src/gui/StackViewerWindow.h
        src/gui/VideoCardStatusWindow.cpp
        src/gui/VideoCardStatusWindow.h
        src/gui/PicStatusWindow.cpp
        src/gui/DmacStatusWindow.cpp
        src/gui/DisplayDebugWindow.cpp
        src/gui/InstructionHistoryWindow.h
        src/gui/InstructionHistoryWindow.cpp
        src/third_party/blip_buffer/Blip_Buffer.cpp
        src/frontend/TestRunner.cpp
)

# Set C++ version
target_compile_features(${EXECUTABLE_NAME} PUBLIC cxx_std_20)

# Keep Blip's phase table layout consistent in the caller and library.
target_compile_definitions(${EXECUTABLE_NAME} PRIVATE BLIP_PHASE_BITS=8)

# on Web targets, we need CMake to generate a HTML webpage. 
if(EMSCRIPTEN)
	set(CMAKE_EXECUTABLE_SUFFIX ".html" CACHE INTERNAL "")
endif()

# Helper to silence dev warnings inside a subdirectory's CMakeLists.txt
macro(add_subdirectory_quiet dir)
    # Backup current setting
    set(_no_dev_backup "$CACHE{CMAKE_SUPPRESS_DEVELOPER_WARNINGS}")
    # Turn off dev warnings
    set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS ON CACHE INTERNAL "" FORCE)
    # Please for the love of God just shut up about CMake deprecations
    set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)
    # Add the subdirectory as usual
    add_subdirectory(${dir} ${ARGN})
    # Restore previous setting
    set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS ${_no_dev_backup} CACHE INTERNAL "" FORCE)
endmacro()

# Configure SDL by calling its CMake file.
# we use EXCLUDE_FROM_ALL so that its install targets and configs don't
# pollute upwards into our configuration.
add_subdirectory_quiet(SDL EXCLUDE_FROM_ALL)

# Add ImGui
add_library(imgui STATIC
        imgui/imgui.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        imgui/imgui_demo.cpp
        imgui/backends/imgui_impl_sdl3.cpp
        imgui/backends/imgui_impl_sdlrenderer3.cpp
)

target_compile_features(imgui PRIVATE cxx_std_20)

target_include_directories(imgui
        PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                ${CMAKE_CURRENT_SOURCE_DIR}/imgui
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/imgui
                ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends
)

# Link ImGui to SDL
target_link_libraries(imgui PUBLIC SDL3::SDL3)

# Keep SDL_mixer for additional sound sources, with only PCM/WAV support.
set(SDLMIXER_VENDORED ON)
set(SDLMIXER_WAVE ON CACHE BOOL "Enable WAVE audio" FORCE)
foreach(decoder IN ITEMS
        AIFF AU VOC
        FLAC FLAC_LIBFLAC FLAC_DRFLAC
        GME MOD MOD_XMP
        MP3 MP3_DRMP3 MP3_MPG123
        MIDI MIDI_FLUIDSYNTH MIDI_TIMIDITY
        OPUS VORBIS_STB VORBIS_VORBISFILE VORBIS_TREMOR
        WAVPACK)
    set(SDLMIXER_${decoder} OFF CACHE BOOL "Unused SDL_mixer decoder" FORCE)
endforeach()
add_subdirectory_quiet(SDL_mixer EXCLUDE_FROM_ALL)

# Only zlib is needed from the SDL_image tree, for compressed SST files.
add_subdirectory_quiet(SDL_image/external/zlib EXCLUDE_FROM_ALL)

# Create a canonical ZLIB::ZLIB alias from whatever target zlib’s CMake defines
if (TARGET zlibstatic)
    add_library(ZLIB::ZLIB ALIAS zlibstatic)
elseif (TARGET zlib)
    add_library(ZLIB::ZLIB ALIAS zlib)
else()
    message(FATAL_ERROR "Could not find zlib or zlibstatic target in SDL_image/external/zlib")
endif()

target_compile_definitions(${EXECUTABLE_NAME} PRIVATE MOO_USE_ZLIB)

# Link SDL to our executable. This also makes its include directory available to us.
target_link_libraries(${EXECUTABLE_NAME} PUBLIC
    imgui
    SDL3_mixer::SDL3_mixer
    SDL3::SDL3
    ZLIB::ZLIB
)

target_compile_definitions(${EXECUTABLE_NAME} PUBLIC SDL_MAIN_USE_CALLBACKS)

# set some extra configs for each platform
set_target_properties(${EXECUTABLE_NAME} PROPERTIES 
    # Launch without a console window when opened from Explorer.
    WIN32_EXECUTABLE TRUE
    # On macOS, make a proper .app bundle instead of a bare executable
    MACOSX_BUNDLE TRUE
    # Set the Info.plist file for Apple Mobile platforms. Without this file, your app
    # will not launch. 
    MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/src/Info.plist.in"

    # in Xcode, create a Scheme in the schemes dropdown for the app.
    XCODE_GENERATE_SCHEME TRUE
    # Identification for Xcode
    XCODE_ATTRIBUTE_BUNDLE_IDENTIFIER "com.ravbug.sdl3-sample"
	XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER "com.ravbug.sdl3-sample"
	XCODE_ATTRIBUTE_CURRENTYEAR "${CURRENTYEAR}"
)

# on Visual Studio, set our app as the default project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT "${EXECUTABLE_NAME}")

# Stage the macOS app where the DMG workflow expects it.
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    install(TARGETS ${EXECUTABLE_NAME}
        BUNDLE DESTINATION release COMPONENT Runtime
    )

    # Fix dependencies in the installed app that will actually go into the DMG.
    install(CODE "
        include(BundleUtilities)
        fixup_bundle(
            \"\$ENV{DESTDIR}\${CMAKE_INSTALL_PREFIX}/release/${EXECUTABLE_NAME}.app\"
            \"\"
            \"${CMAKE_BINARY_DIR}/$<CONFIG>;${CMAKE_BINARY_DIR}\")
    " COMPONENT Runtime)
    set(CPACK_GENERATOR "DragNDrop")
    include(CPack)
endif()
