cmake_minimum_required(VERSION 3.16)
project(Crafterra-Linux CXX)

# ----- custom -----
set(OPENSIV3D_SOURCE_DIRECTORY "${CMAKE_SOURCE_DIR}/../../../../OpenSiv3D")
set(CRAFTERRA_SOURCE_DIRECTORY "${CMAKE_SOURCE_DIR}/../../../../Crafterra")
# ------------------

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/App)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
add_compile_options (-fdiagnostics-color=always)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
add_compile_options (-fcolor-diagnostics)
endif ()

add_executable(Source Source.cpp)

target_include_directories(Source PRIVATE
    "${CRAFTERRA_SOURCE_DIRECTORY}/include"
    "${OPENSIV3D_SOURCE_DIRECTORY}/Siv3D/include"
    "${OPENSIV3D_SOURCE_DIRECTORY}/Siv3D/include/ThirdParty"
)

target_link_libraries(Source PRIVATE
    ${OPENSIV3D_SOURCE_DIRECTORY}/Linux/build/libSiv3D.a
    -lasound
    -lavcodec
    -lavformat
    -lavutil
    -lcurl
    -ldl
    -lfreetype
    -lGL
    -lglib-2.0
    -lgobject-2.0
    -lgif
    -lgio-2.0
    -lgdk-3
    -lgtk-3
    -lharfbuzz
    -logg
    -lopencv_core
    -lopencv_imgcodecs
    -lopencv_imgproc
    -lopencv_objdetect
    -lopencv_photo
    -lopencv_videoio
    -lopus
    -lopusfile
    -lpthread
    -lpng
    -lSoundTouch
    -lswresample
    -ltiff
    -lturbojpeg
    -luuid
    -lvorbis
    -lvorbisenc
    -lvorbisfile
    -lwebp
    -lX11
    -lXft
)

