
#################################################
SOURCES=main.cpp
TARGET=h4k
BUILD_DIR=./bin
LIBOPENCM3 = ./libopencm3
#################################################
CC = arm-none-eabi-gcc
CXX = arm-none-eabi-g++
LD = arm-none-eabi-g++
AR = arm-none-eabi-ar
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size
STFLASH = ../tools/stlink/bin-amd64/st-flash

APP_ADDRESS = 0x08002000
APP_OFFSET = $(shell echo $$(($(APP_ADDRESS) - 0x08000000)))

CFLAGS = -Os -std=gnu99 -Wall -pedantic -Werror -mcpu=cortex-m3 -mthumb -DSTM32F1 -I$(LIBOPENCM3)/include -ggdb3
LDFLAGS = -lopencm3_stm32f1 -Wl,-Tstm32f103.ld -nostartfiles -lc -lnosys -mthumb -mcpu=cortex-m3 -L$(LIBOPENCM3)/lib/ -Wl,-gc-sections


ELF = $(BUILD_DIR)/$(TARGET).elf
HEX = $(BUILD_DIR)/$(TARGET).hex
BIN = $(BUILD_DIR)/$(TARGET).bin

OBJECTS = $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(basename $(SOURCES))))

$(BIN): $(ELF)
	$(OBJCOPY) -O binary $< $@

$(HEX): $(ELF)
	$(OBJCOPY) -O ihex $< $@

$(ELF): $(OBJECTS) | $(LIBOPENCM3)/lib/libopencm3_stm32f1.a
	echo $(OBJECTS)
	$(LD) $(OBJECTS) -o $@ $(LDFLAGS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map

$(BUILD_DIR)/%.o: %.s
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CFLAGS) -c -o $@ $<

$(LIBOPENCM3)/lib/libopencm3_stm32f1.a:
	$(MAKE) -C $(LIBOPENCM3) TARGETS=stm32/f1

all: $(OBJECTS) $(ELF) $(BIN)
	$(SIZE) $(ELF)

flash: $(BUILD_DIR)/$(TARGET).bin
	$(STFLASH) --reset write $(BUILD_DIR)/$(TARGET).bin 0x8000000

clean:
	rm -rf $(BUILD_DIR)/*