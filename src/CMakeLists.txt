set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(input)
add_executable(oinkoinkrun main.cpp)
target_link_libraries(oinkoinkrun oinkoinkrun_input)