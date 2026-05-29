# Makefile for CUDA project (replaces gpu-build.sh)
# Compiles main.cu with nvcc and passes host-compiler flags via -Xcompiler.

# =============================================================================
# User-configurable variables
# =============================================================================
CUDA_ARCH ?= sm_75          # Target GPU architecture
NVCC      ?= nvcc           # CUDA compiler
TARGET    ?= skipy.out      # Output executable name
SOURCE    ?= main.cu        # Source file

# =============================================================================
# Host compiler flags (applied to .cpp files via nvcc -Xcompiler)
# =============================================================================
HOST_FLAGS := \
    -std=c++17 \
    -Wall -Wextra -Wsign-conversion \
    -Wshadow -Wnon-virtual-dtor -Wcast-align -Wunused \
    -Woverloaded-virtual -Wnull-dereference -Wdouble-promotion -Wformat=2 \
    -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches \
    -Wlogical-op -Weffc++ \
    -O2 \
    -fsanitize=undefined \
    -fstack-protector-strong

# Note: -Wpedantic is intentionally excluded because CUDA's internal code
# generation produces GCC-style #line directives that are not strictly
# ISO C++ compliant, causing -Wpedantic to fire on NVIDIA's own intermediate
# files. It remains active in CPU-only builds (e.g., build.sh).

# =============================================================================
# nvcc flags
# =============================================================================
NVCC_FLAGS := \
    -arch=$(CUDA_ARCH) \
    --diag-suppress 20012 \
    -Xcudafe "--diag_suppress=20012" \
    --expt-relaxed-constexpr \
    -isystem /usr/local/cuda/include \
    -DCOMPILE_FOR_DEVICE \
    $(foreach flag,$(HOST_FLAGS),-Xcompiler $(flag))

# =============================================================================
# Build rules
# =============================================================================
all: $(TARGET)

$(TARGET): $(SOURCE)
	$(NVCC) $(NVCC_FLAGS) $< -lcurand -o $@

.PHONY: clean
clean:
	rm -f $(TARGET)

# =============================================================================
# Help target (optional)
# =============================================================================
.PHONY: help
help:
	@echo "Available targets:"
	@echo "  all      - Build $(TARGET) (default)"
	@echo "  clean    - Remove $(TARGET)"
	@echo "  help     - Show this help"
	@echo ""
	@echo "Variables (can be set on command line):"
	@echo "  CUDA_ARCH   - GPU architecture (default: sm_75)"
	@echo "  NVCC        - CUDA compiler (default: nvcc)"
	@echo "  TARGET      - Output executable (default: skipy.out)"
	@echo "  SOURCE      - Source file (default: main.cu)"