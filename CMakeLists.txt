cmake_minimum_required(VERSION 3.14)
project(ProductManagement)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

# Fetch xlnt
FetchContent_Declare(
  xlnt
  GIT_REPOSITORY https://github.com/tfussell/xlnt.git
  GIT_TAG master
)
FetchContent_MakeAvailable(xlnt)

# Fetch tabulate
FetchContent_Declare(
  tabulate
  GIT_REPOSITORY https://github.com/p-ranav/tabulate.git
  GIT_TAG master
)
FetchContent_MakeAvailable(tabulate)

# Add your main.cpp or other source files
add_executable(ProductManagement main.cpp 
    src/auth/User.cpp
    src/auth/Admin.cpp
    src/auth/Staff.cpp
    src/auth/Auth.cpp)
# Tell the compiler where to find all the headers 
target_include_directories(ProductManagement PRIVATE include )
# Link libraries
target_link_libraries(ProductManagement PRIVATE xlnt tabulate)

add_custom_command(TARGET ProductManagement POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:xlnt>
    $<TARGET_FILE_DIR:ProductManagement>
)

