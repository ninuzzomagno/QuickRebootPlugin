cmake_minimum_required(VERSION 3.2)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

set(CMAKE_C_STANDARD 99)

include("$ENV{VITASDK}/share/vita.cmake" REQUIRED)
project(QuickReboot)

add_executable(${PROJECT_NAME}
  src/main.c
)

target_link_libraries(
  ${PROJECT_NAME}
  SceLibc_stub_weak
  SceSysmem_stub_weak
  SceSysmodule_stub_weak
  SceLibKernel_stub_weak
  SceKernelThreadMgr_stub_weak
  SceKernelModulemgr_stub_weak
  QuickMenuReborn_stub_weak
  ScePower_stub 
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -nostdlib")
vita_create_self(${PROJECT_NAME}.suprx ${PROJECT_NAME} UNSAFE CONFIG src/main.yml)
