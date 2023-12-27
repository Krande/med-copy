set -ex

export FCFLAGS="-fdefault-integer-8 ${FCFLAGS}"
export FFLAGS="-fdefault-integer-8 ${FFLAGS}"
export MED_MEDINT_TYPE=int
mkdir -p build
pushd build

# we specify both old style (all capital PYTHON)
# and new style (Python) variables
cmake \
  ${CMAKE_ARGS} \
  -D Python_FIND_VIRTUALENV=FIRST \
  -D Python_FIND_STRATEGY=LOCATION \
  -D Python_ROOT_DIR="${PREFIX}" \
  -D Python_EXECUTABLE="${PYTHON}" \
  -D PYTHON_EXECUTABLE="${PYTHON}" \
  -D HDF5_ROOT_DIR=${PREFIX} \
  -D MEDFILE_INSTALL_DOC=OFF \
  -D MEDFILE_BUILD_TESTS=OFF \
  -D MEDFILE_BUILD_PYTHON=ON \
  -D MEDFILE_BUILD_SHARED_LIBS=ON \
  -D MEDFILE_BUILD_STATIC_LIBS=OFF \
  -D DMEDCOUPLING_USE_64BIT_IDS=ON \
  -D MEDFILE_USE_UNICODE=OFF \
  -D MED_MEDINT_TYPE=long \
  -D SIZEOF_LONG_LONG=8 \
  ..

make -j${CPU_COUNT}
make install

popd