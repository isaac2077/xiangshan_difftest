FPGA_TARGET = $(BUILD_DIR)/fpga-host
FPGA_CSRC_DIR   = $(abspath ./src/test/csrc/fpga)
FPGA_CONFIG_DIR = $(abspath ./config) # Reserve storage for xdma configuration

DMA_CHANNELS ?= 1

FPGA_CXXFILES  = $(SIM_CXXFILES) $(shell find $(FPGA_CSRC_DIR) -name "*.cpp")
FPGA_CXXFLAGS  = $(subst \\\",\", $(SIM_CXXFLAGS)) -I$(FPGA_CSRC_DIR) -DCONFIG_DMA_CHANNELS=$(DMA_CHANNELS) -DNUM_CORES=$(NUM_CORES) -DFPGA_HOST
FPGA_CXXFLAGS += -std=c++11 -O3 -flto -march=native -mtune=native
FPGA_LDFLAGS   = $(SIM_LDFLAGS) -lpthread -ldl

fpga-build: fpga-clean fpga-host

ifeq ($(USE_XDMA_DDR_LOAD), 1)
FPGA_CXXFLAGS += -DUSE_XDMA_DDR_LOAD
endif

ifeq ($(USE_THREAD_MEMPOOL), 1)
FPGA_CXXFLAGS += -DUSE_THREAD_MEMPOOL
endif

$(FPGA_TARGET): $(FPGA_CXXFILES)
	$(CXX) $(FPGA_CXXFLAGS) $(FPGA_CXXFILES) -o $@ $(FPGA_LDFLAGS)

fpga-host: $(FPGA_TARGET)

fpga-clean:
	rm -f $(FPGA_TARGET)
