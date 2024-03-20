# Attention for editors: You have to use tab-characters for command indentation!
# vim: set noexpandtab:

DEVICE_IP       ?= 192.168.1.121
DEVICE_TTY      ?= /dev/ttyHotWireEsp32

BAUDRATE        := 115200
ESP             := esp32:esp32:esp32da

BUILD_DIR_ARD   := build/arduino
BUILD_DIR_X86   := build/x86

.PHONY: default
default: deployToIp

.PHONY: help
help:
	@echo "Help:"
	@echo ""
	@echo "$(MAKE) build        - just build"
	@echo "$(MAKE) deployToIp   - build and upload to $(DEVICE_IP)"
	@echo "$(MAKE) deployToTty  - build and upload to $(DEVICE_TTY)"
	@echo "$(MAKE) monitor      - monitor $(DEVICE_TTY)"

.PHONY: build
build:
	arduino-cli compile --build-path $(BUILD_DIR_ARD) --fqbn $(ESP) . 

.PHONY: deployToIp
deployToIp: build
	arduino-cli upload -p $(DEVICE_IP) --fqbn $(ESP) --input-dir $(BUILD_DIR_ARD) .

.PHONY: deployToTty
deployToTty: build
	arduino-cli upload -p $(DEVICE_TTY) --fqbn $(ESP) --input-dir $(BUILD_DIR_ARD) .

.PHONY: monitor
monitor:
	arduino-cli monitor help -p $(DEVICE_TTY) -c "baudrate=$(BAUDRATE)"

.PHONY: testSetup
testSetup:
	@echo -n "Testing for arduino-cli: " && (which arduino-cli) || (echo "FAILED - Please install arduino-cli" && exit 1)
	@echo "Testing for ESP platform " && (arduino-cli core list | grep -q "esp32") || (echo "FAILED - Please run arduino-cli core install esp32:esp32" && exit 1)
	@echo "Testing for DebugLog " && (arduino-cli lib list | grep -q "DebugLog") || (echo "FAILED - Please run arduino-cli lib install DEBUGLOG" && exit 1)
	@echo "Setup seems to be ok."

.PHONY: configure_x86
configure_x86:
	install -d $(BUILD_DIR_X86)
	cmake -S . -B $(BUILD_DIR_X86) -G "Ninja" 

.PHONY: build_x86
build_x86: $(BUILD_DIR_X86)/CMakeCache.txt
	cmake --build $(BUILD_DIR_X86) -- -j 4

.PHONY: run
run: build_x86
	./$(BUILD_DIR_X86)/console
