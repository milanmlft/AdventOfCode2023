add_executable(AoC main.cpp)
target_include_directories(AoC PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_compile_features(AoC PUBLIC cxx_std_17)
set_target_properties(AoC PROPERTIES CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS OFF)

