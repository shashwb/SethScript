cmake_minimum_required(VERSION 3.5)
project(VTSCRIPT CXX)

# EDIT
# add any files you create related to the interpreter here
# excluding unit tests
set(interpreter_src
  tokenize.hpp tokenize.cpp
  expression.hpp expression.cpp
  environment.hpp environment.cpp
  interpreter.hpp interpreter.cpp
  )

# EDIT
# add any files you create related to unit testing here
set(test_src
  catch.hpp
  unittests.cpp
  test_interpreter.cpp
)

# EDIT
# add any files you create related to the vtscript program here
set(vtscript_src
  ${interpreter_src}
  vtscript.cpp
  )cd ~

# ------------------------------------------------
# You should not need to edit any files below here
# ------------------------------------------------

# create the vtscript executable
add_executable(vtscript ${vtscript_src})
set_property(TARGET vtscript PROPERTY CXX_STANDARD 11)

# setup testing
set(TEST_FILE_DIR "${CMAKE_SOURCE_DIR}/tests")

configure_file(${CMAKE_SOURCE_DIR}/test_config.hpp.in 
  ${CMAKE_BINARY_DIR}/test_config.hpp)

include_directories(${CMAKE_BINARY_DIR})

add_executable(unittests ${interpreter_src} ${test_src})
set_property(TARGET unittests PROPERTY CXX_STANDARD 11)

enable_testing()
add_test(unittests unittests)
