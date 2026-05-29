#!/bin/bash

# Flags that apply to YOUR code only
# These are passed via -Xcompiler to the host compiler for .cpp files
HOST_FLAGS=(
    -std=c++17 -Wall -Wextra -Werror -Wconversion -Wsign-conversion
    -Wshadow -Wnon-virtual-dtor -Wcast-align -Wunused
    -Woverloaded-virtual -Wnull-dereference -Wdouble-promotion -Wformat=2
    -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches
    -Wlogical-op -Wuseless-cast -Weffc++ -O2 -fsanitize=undefined
    -fstack-protector-strong
)

# Convert each host flag to an nvcc -Xcompiler flag
NVCC_ARGS=()
for flag in "${HOST_FLAGS[@]}"; do
    NVCC_ARGS+=("-Xcompiler" "$flag")
done

nvcc -arch=sm_75 \
    --diag-suppress 20012 \
    -Xcudafe "--diag_suppress=20012" \
    --expt-relaxed-constexpr \
    -isystem /usr/local/cuda/include \
    -DCOMPILE_FOR_DEVICE \
    main.cu \
    "${NVCC_ARGS[@]}" \
    -lcurand \
    -o skipy.out

# Link the executable
# -Xlinker -rdynamic is needed for backtraces to show C++ function names
# -fsanitize=address,undefined enables runtime sanitizers
# -fstack-protector-strong adds stack smashing protection
# -O2 enables optimizations
# -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wnull-dereference -Wdouble-promotion -Wformat=2 -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wuseless-cast -Weffc++ are additional compiler warnings
# -DCOMPILE_FOR_HOST tells the compiler to compile for the host CPU
# -o skipy.out specifies the output executable name

# Note: -Wpedantic is intentionally excluded from gpu-build.sh.
# CUDA's internal code generation produces GCC-style #line directives
# that are not strictly ISO C++ compliant, causing -Wpedantic to fire
# on NVIDIA's own intermediate files. It remains active in build.sh
# for CPU-only builds where it is safe to use.

# -fsanitize=address: Enable AddressSanitizer (ASan) for runtime memory error detection (heap use-after-free, buffer overflows, etc.)
# -fsanitize=undefined: Enable UndefinedBehaviorSanitizer (UBSan) for runtime detection of undefined behavior (signed integer overflow, null pointer dereference, etc.)

# -isystem /usr/local/cuda/include: Marks CUDA headers as "system headers" — GCC suppresses warnings from system headers even with `-Werror`
# --expt-relaxed-constexpr: Suppresses the `constexpr operator&&` and `operator\|\|` errors from `nv/target`
# -lcurand: Links the cuRAND library, need this once kernels are called                                
# -Xcudafe "--diag_suppress=20012": Suppresses the `20012` error code from nvcc (suppresses an additional nvcc diagnostic)                                  
# The `-isystem` flag is the critical one. It tells the compiler "warnings in these headers are not my problem", which is exactly the right attitude toward NVIDIA's own headers that violate your coding standards.
