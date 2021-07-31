# cmake最低版本
cmake_minimum_required(VERSION 3.21)

option(USE_MODULE "" ON)
option(ENABLE_ZTEST_TEST "" OFF)

# 項目名
set(project ztest)
project(${project})

# 包含模塊
include(CMakePrintHelpers)

# 啟用IDE目錄功能
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# 輸出目錄
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)

set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(common)

# 編譯器選項
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/W4;/MP;/Zc:__cplusplus;/std:c17;/experimental:module;>")

set(target ztest)

add_library(${target} INTERFACE)

include(GNUInstallDirs)

target_include_directories(${target}
  INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_sources(${target}
  INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/ztest/ztest.cppm>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/ztest/ztest.cppm>"
)

target_install(${target} 0 0 1)

if(ENABLE_ZTEST_TEST)
  # 添加可執行文件
  set(main main)
  add_executable(${main})
  target_sources(${main}
    PRIVATE
      src/main.cpp
      src/main.cppm
      include/ztest/macro.h
      include/ztest/module.h
      include/ztest/ztest.cppm
      include/ztest/ztest.hpp
  )

  # 設置C++標準
  target_compile_features(${main} PRIVATE cxx_std_20)

  # 引用目錄
  target_include_directories(${main} PRIVATE include)

  # 設置宏
  target_compile_definitions(${main} PRIVATE USE_MODULE=$<BOOL:${USE_MODULE}>)
endif()
