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
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/W4;/MP;/Zc:__cplusplus;/std:c++latest;/std:c17;/experimental:module;>")

## 庫開始
set(target ztest)

add_library(${target} INTERFACE)

add_library(${target}_MODULE INTERFACE)

set_target_properties(${target} PROPERTIES
  INTERFACE_SOURCES "$<INSTALL_INTERFACE:include/ztest/ztest.cppm>"
)

# install the target and create export-set
install(TARGETS ${target} ${target}_MODULE
  EXPORT ${target}Targets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

# install header file
install(DIRECTORY include/ztest DESTINATION include)

# generate and install export file
install(EXPORT ${target}Targets
  FILE ${target}Targets.cmake
  NAMESPACE ${target}::
  DESTINATION lib/cmake/${target}
)

# include CMakePackageConfigHelpers macro
include(CMakePackageConfigHelpers)

# set version
set(version 0.0.1)

set_property(TARGET ${target} PROPERTY VERSION ${version})
set_property(TARGET ${target} PROPERTY SOVERSION 0)
set_property(TARGET ${target} PROPERTY
  INTERFACE_${target}_MAJOR_VERSION 0)
set_property(TARGET ${target} APPEND PROPERTY
  COMPATIBLE_INTERFACE_STRING ${target}_MAJOR_VERSION
)

# generate the version file for the config file
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${target}ConfigVersion.cmake"
  VERSION "${version}"
  COMPATIBILITY AnyNewerVersion
)

# create config file
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/${target}Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/${target}Config.cmake"
  INSTALL_DESTINATION lib/cmake/${target}
)

# install config files
install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/${target}Config.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/${target}ConfigVersion.cmake"
  DESTINATION lib/cmake/${target}
)

# generate the export targets for the build tree
export(EXPORT ${target}Targets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/${target}Targets.cmake"
  NAMESPACE ${target}::
)
## 庫結束

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
