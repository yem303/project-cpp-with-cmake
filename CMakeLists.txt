cmake_minimum_required(VERSION 3.14)
project(ProductManagement)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 🔥 Fix MSVC Windows SDK "byte" ambiguity issue
add_compile_definitions(_HAS_STD_BYTE=0)

include(FetchContent)

# -------------------------
# Fetch xlnt
# -------------------------
FetchContent_Declare(
  xlnt
  GIT_REPOSITORY https://github.com/tfussell/xlnt.git
  GIT_TAG master
)
FetchContent_MakeAvailable(xlnt)

# -------------------------
# Fetch tabulate
# -------------------------
FetchContent_Declare(
  tabulate
  GIT_REPOSITORY https://github.com/p-ranav/tabulate.git
  GIT_TAG master
)
FetchContent_MakeAvailable(tabulate)

# -------------------------
# Your executable
# -------------------------
add_executable(ProductManagement 
    main.cpp 
    src/auth/User.cpp
    src/auth/Admin.cpp
    src/auth/Auth.cpp
    src/menu/Menu.cpp
    src/products/Product.cpp
    src/products/ProductManager.cpp
    src/auth/IncryptPass.cpp
)

# -------------------------
# Include directories
# -------------------------
target_include_directories(ProductManagement PRIVATE include)

# -------------------------
# Link libraries
# -------------------------
target_link_libraries(ProductManagement PRIVATE xlnt tabulate)

# -------------------------
# Copy xlnt DLL (Windows fix)
# -------------------------
add_custom_command(TARGET ProductManagement POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:xlnt>
    $<TARGET_FILE_DIR:ProductManagement>
)