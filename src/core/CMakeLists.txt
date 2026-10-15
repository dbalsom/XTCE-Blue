add_library(cycle_log STATIC
    Logger.cpp
    Logger.h
    CycleLogMicrocode.cpp
    CycleLogMicrocode.h
)
target_compile_features(cycle_log PUBLIC cxx_std_20)

add_library(generated_808X STATIC
    cpu_types.h
    generated_808X/Cpu.h
    generated_808X/GeneratedCpu.h
    generated_808X/microcode_tables.cpp
    generated_808X/microcode_dispatch.inc
)
target_include_directories(generated_808X PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/generated_808X
)
target_compile_features(generated_808X PUBLIC cxx_std_17)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(generated_808X PRIVATE -fno-exceptions)
    if(XTCE_DEBUG_SYMBOLS)
        target_compile_options(generated_808X PRIVATE -g)
    endif()
endif()
target_link_libraries(cycle_log PRIVATE generated_808X)

add_library(generated_VX0 STATIC
    cpu_types.h
    generated_VX0/Cpu.h
    generated_VX0/GeneratedCpu.h
    generated_VX0/GeneratedCpu.cpp
    generated_VX0/microcode_tables.cpp
    generated_VX0/microcode_dispatch.inc
    generated_VX0/microcode_conditions.inc
)
target_include_directories(generated_VX0 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(generated_VX0 PUBLIC cxx_std_17)
if(XTCE_DEBUG_SYMBOLS AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(generated_VX0 PRIVATE -g)
endif()

add_library(interpreted_808X INTERFACE)
target_link_libraries(interpreted_808X INTERFACE cycle_log)
target_compile_features(interpreted_808X INTERFACE cxx_std_20)

add_library(xtce_core STATIC
    bios.h
    Bus.h
    Cga.cpp
    Cga.h
    cpu_types.h
    CpuSelection.h
    Crtc.cpp
    Crtc.h
    Disassembler.h
    Dmac.h
    execution_control.h
    Fdc.h
    font.h
    Keyboard.h
    Log.h
    Machine.cpp
    Machine.h
    Pic.h
    Pit.h
    Ppi.h
    PrefetchQueue.h
    StubBus.h
    interpreted_808X/Cpu.h
    interpreted_808X/microcode.h
    test_support/FlatBus.h
    test_support/SstBus.h
)
target_include_directories(xtce_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../SDL/include
)
target_link_libraries(xtce_core PUBLIC generated_808X generated_VX0 interpreted_808X)
target_compile_features(xtce_core PUBLIC cxx_std_20)
# Blip_Buffer's phase table must have the same layout in every user.
target_compile_definitions(xtce_core PUBLIC BLIP_PHASE_BITS=8)
