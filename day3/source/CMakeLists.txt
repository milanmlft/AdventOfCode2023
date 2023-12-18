add_executable(main main.cpp)
target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_compile_features(main PUBLIC cxx_std_17)
set_target_properties(main PROPERTIES CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS OFF)
add_custom_target(run_program
    ALL
    COMMAND "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/main"
    DEPENDS main
    COMMENT "Run the built executable"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

