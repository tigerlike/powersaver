cmake_minimum_required(VERSION 3.11)

project(powersave-ai)

# Nvidia Cuda
find_package(CUDA REQUIRED)
include_directories(${CUDA_INCLUDE_DIRS})
# TODO  for linux
link_directories(${CUDA_TOOLKIT_ROOT_DIR}/lib/x64)
message("Using CUDA: ${CUDA_VERSION} @ ${CUDA_TOOLKIT_ROOT_DIR}")
message("Cuda Libraries: ${CUDA_LIBRARIES}")
message("Cuda Include dir: ${CUDA_INCLUDE_DIRS}")

# NVCC Choose which cards to compile for
# 52 Maxwell (GTX 9x)
# 61 Pascal (GTX 10x)
# 75 Turing (RTX 20x)
# More here: http://arnon.dk/matching-sm-architectures-arch-and-gencode-for-various-nvidia-cards/

set(CUDA_ARCH CACHE STRING "Set GPU architecture (semicolon separated list, e.g. '-DCUDA_ARCH=20;35;60')")

foreach(CUDA_ARCH_ELEM ${CUDA_ARCH})
    # set flags to create device code for the given architecture
    set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS}
            "--generate-code arch=compute_${CUDA_ARCH_ELEM},code=sm_${CUDA_ARCH_ELEM} --generate-code arch=compute_${CUDA_ARCH_ELEM},code=compute_${CUDA_ARCH_ELEM}")
endforeach()

option(CUDA_SHOW_CODELINES "Show kernel lines in cuda-gdb and cuda-memcheck" OFF)

if(CUDA_SHOW_CODELINES)
    set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS}" --source-in-ptx -lineinfo)
    set(CUDA_KEEP_FILES ON CACHE BOOL "activate keep files" FORCE)
endif(CUDA_SHOW_CODELINES)

# NVCC profiling / debug
# https://docs.nvidia.com/cuda/cuda-compiler-driver-nvcc/index.html#ptxas-options
option(CUDA_SHOW_REGISTER "Show registers used for each kernel and compute architecture" OFF)
if(CUDA_SHOW_REGISTER)
    set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS}" -Xptxas=-v)
endif(CUDA_SHOW_REGISTER)

# Source Files
set(SRC main.cpp)
set(CUDA_SRC
#        cudnn/conv_sample.cpp
        cudnn/error_util.h
        cudnn/fp16_dev.cu
        cudnn/fp16_dev.h
        cudnn/fp16_emu.cpp
        cudnn/fp16_emu.h
        cudnn/float32.h
        cudnn/test.cu
        )

add_executable(${PROJECT_NAME} main.cpp Benchmark.hpp Benchmark.cpp)
cuda_add_library(CUDA_KERNELS_LIB ${CUDA_SRC})

target_link_libraries(${PROJECT_NAME} cudart_static cudnn CUDA_KERNELS_LIB)