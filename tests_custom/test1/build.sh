#!/bin/bash

# Set the include and library directories
INCLUDE_DIRS="-I$CONDA_PREFIX/include"
LIB_DIRS="-L$CONDA_PREFIX/lib -L$CONDA_PREFIX/bin"
# Add the paths for the C++ standard library

echo "LD_LIBRARY_PATH: $LD_LIBRARY_PATH"
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$CONDA_PREFIX/lib
# Set the shared flags
SHARED_FLAGS="-cpp -fdefault-real-8 -fdefault-double-8 -fdefault-integer-8 -DMKL_ILP64 -g"

# Compile the Fortran file
gfortran ./test1.f90 $SHARED_FLAGS $INCLUDE_DIRS -o test1 $LIB_DIRS -lmedfwrap -lmedC -lmed -lhdf5 -lhdf5_hl -lhdf5_cpp -lhdf5_hl_cpp -lhdf5_fortran -lhdf5_hl_fortran

# Run the executable
./test1
