#CROSS_COMPILE ?= arm-none-eabi-
#CC = $(CROSS_COMPILE)gcc
#OBJCOPY = $(CROSS_COMPILE)objcopy
#LIBOPENCM3 ?= ./libopencm3

#STFLASH=../tools/stlink/bin-amd64/st-flash

#TARGET=./stm32-tx-hid
#
#APP_ADDRESS = 0x08002000
#APP_OFFSET = $(shell echo $$(($(APP_ADDRESS) - 0x08000000)))
#
#CFLAGS = -Os -std=gnu99 -Wall -pedantic -Werror -Istm32/include \
#	-mcpu=cortex-m3 -mthumb -DSTM32F1 \
#	-I$(LIBOPENCM3)/include -DAPP_ADDRESS=$(APP_ADDRESS) -ggdb3
#
#LDFLAGS = -lopencm3_stm32f1 \
#	-Wl,-Tstm32f103.ld -nostartfiles -lc -lnosys \
#	-mthumb -mcpu=cortex-m3 -L$(LIBOPENCM3)/lib/ -Wl,-gc-sections
#
#$(TARGET)-bootldr-combined.bin: $(TARGET)-bootldr.bin $(TARGET).bin
#	cp $(TARGET)-bootldr.bin $@
#	dd if=$(TARGET).bin of=$@ seek=1 bs=$(APP_OFFSET)
#
#$(TARGET).elf: $(TARGET).o | $(LIBOPENCM3)/lib/libopencm3_stm32f1.a
#	$(CC) $^ -o $@ $(LDFLAGS) -Wl,-Ttext=$(APP_ADDRESS)
#
#$(TARGET)-bootldr.elf: $(TARGET)-bootldr.o | $(LIBOPENCM3)/lib/libopencm3_stm32f1.a
#	$(CC) $^ -o $@ $(LDFLAGS)
#
#$(LIBOPENCM3)/lib/libopencm3_stm32f1.a:
#	$(MAKE) -C $(LIBOPENCM3) TARGETS=stm32/f1
#
#%.bin: %.elf
#	$(OBJCOPY) -O binary $^ $@
#
#clean:
#	-rm *.elf *.o *.bin
#
#flash:
#	$(STFLASH) --reset write stm32-tx-hid-bootldr.bin 0x8000000
#
#dfu:
#	/home/heqichen/my/project/keyboard/h4k/tools/dfu-util/bin/dfu-util -d 0483:df11 -R -s 0x8002000 -D stm32-tx-hid.bin
#


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

CFLAGS = -Os -std=gnu99 -Wall -pedantic -Werror -Istm32/include -mcpu=cortex-m3 -mthumb -DSTM32F1 -I$(LIBOPENCM3)/include -DAPP_ADDRESS=$(APP_ADDRESS) -ggdb3
LDFLAGS = -lopencm3_stm32f1 -Wl,-Tstm32f103.ld -nostartfiles -lc -lnosys -mthumb -mcpu=cortex-m3 -L$(LIBOPENCM3)/lib/ -Wl,-gc-sections


ELF = $(BUILD_DIR)/$(TARGET).elf
HEX = $(BUILD_DIR)/$(TARGET).hex
BIN = $(BUILD_DIR)/$(TARGET).bin

OBJECTS = $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(basename $(SOURCES))))

$(BIN): $(ELF)
	$(OBJCOPY) -O binary $< $@

$(HEX): $(ELF)
	$(OBJCOPY) -O ihex $< $@

$(ELF): $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $(OBJECTS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map

$(BUILD_DIR)/%.o: %.s
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) -c $(CFLAGS) $< -o $@


all: $(OBJECTS) $(ELF) $(BIN)
	$(SIZE) $(ELF)

flash:
	$(STFLASH) --reset write $(BUILD_DIR)/$(TARGET).bin 0x8000000