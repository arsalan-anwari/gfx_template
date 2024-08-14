# Declare the library as an interface library
add_library(types)

target_sources(types
  PUBLIC
    FILE_SET CXX_MODULES 
    FILES
      types.cppm
)
