# cmake最低版本
cmake_minimum_required(VERSION 3.21)

option(USE_MODULE "" ON)

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

# 編譯器選項
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/W4;/MP;/Zc:__cplusplus;/std:c17;/experimental:module;>")

# 添加可執行文件
add_executable(${project})
target_sources(${project}
  PRIVATE
    src/main.cpp
    src/main.cppm
    src/macro.h
    include/ztest.cppm
    include/ztest.hpp
)

# 設置C++標準
target_compile_features(${project} PRIVATE cxx_std_20)

# 引用目錄
target_include_directories(${project} PRIVATE include)

target_compile_definitions(${project} PRIVATE USE_MODULE=$<BOOL:${USE_MODULE}>)
