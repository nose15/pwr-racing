add_library(convex_hull convex_hull.cpp)
target_link_libraries(convex_hull PRIVATE point utils)
target_include_directories(convex_hull PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)