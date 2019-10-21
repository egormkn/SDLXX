echo "Building for Linux"

export PATH=/usr/local/bin:/usr/bin:$PATH
echo $PATH
gcc --version
cmake --version
git clone https://github.com/Microsoft/vcpkg.git vcpkg
cd vcpkg
CC=gcc-7 && CXX=g++-7 ./bootstrap-vcpkg.sh -useSystemBinaries -disableMetrics
./vcpkg integrate install
./vcpkg install sdl2 sdl2-image[libjpeg-turbo] sdl2-mixer sdl2-net sdl2-ttf tinyxml2 box2d nuklear
cd ..
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build .
# ctest --output-on-failure
