set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(window)
add_subdirectory(events)
add_executable(oinkoinkrun main.cpp game.cpp)
target_link_libraries(oinkoinkrun oinkoinkrun_events oinkoinkrun_window)