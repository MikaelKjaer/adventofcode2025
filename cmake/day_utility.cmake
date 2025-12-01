function(setup_day_build day_name)
configure_file("${day_name}.txt" "${day_name}.txt" COPYONLY)

add_executable(${day_name} "main.cpp")
target_include_directories(${day_name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/.)
target_compile_options(${day_name} PRIVATE ${WARNING_FLAGS})
target_link_libraries(${day_name} adventofcode_utility_library fmt::fmt scn::scn)
endfunction()
