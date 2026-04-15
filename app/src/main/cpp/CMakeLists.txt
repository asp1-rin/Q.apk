cmake_minimum_required(VERSION 3.10.2)
project("admin-logic")

add_library(dobby SHARED IMPORTED)
set_target_properties(dobby PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/../jniLibs/${ANDROID_ABI}/libdobby.so)

add_library(admin-logic SHARED native-lib.cpp)
target_link_libraries(admin-logic dobby android log)
