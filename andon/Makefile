BUILD_DIR=./build
SRC_DIR=./src
PWD=.
DEFS=-D STM32F10X_MD -D USE_STDPERIPH_DRIVER

TARGET=SHUIO

ELF = $(BUILD_DIR)/$(TARGET).elf
HEX = $(BUILD_DIR)/$(TARGET).hex
BIN = $(BUILD_DIR)/$(TARGET).bin

CC = arm-none-eabi-gcc
CXX = arm-none-eabi-g++
LD = arm-none-eabi-g++
AR = arm-none-eabi-ar
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size
STFLASH = ../tools/stlink/bin-amd64/st-flash

COOOBOC_DIR = $(SRC_DIR)/cooboc

USER_SRC += $(SRC_DIR)/main.cpp
USER_SRC += $(SRC_DIR)/keyboard.cpp
USER_SRC += $(SRC_DIR)/key.cpp
USER_SRC += $(SRC_DIR)/event_loop.cpp
USER_SRC += $(SRC_DIR)/fifo.cpp
USER_SRC += $(SRC_DIR)/keymap.cpp

#DEVICE_SRC += $(SRC_DIR)/devices/a7/aia7.cpp
#DEVICE_SRC += $(SRC_DIR)/devices/a7/at_decoder.cpp
#DEVICE_SRC += $(SRC_DIR)/devices/gps/gps.cpp


COOBOC_SRC += $(COOOBOC_DIR)/cooboc.cpp
COOBOC_SRC += $(COOOBOC_DIR)/gpio.cpp
COOBOC_SRC += $(COOOBOC_DIR)/hardware_serial.cpp
# COOBOC_SRC += $(COOOBOC_DIR)/hardware_can.cpp
COOBOC_SRC += $(COOOBOC_DIR)/hardware_iic.cpp
COOBOC_SRC += $(COOOBOC_DIR)/block_slave_iic.cpp

USER_LIB_SRC += $(SRC_DIR)/lib/system_stm32f10x.c
USER_LIB_SRC += $(SRC_DIR)/lib/stm32f10x_it.c
USER_LIB_SRC += $(SRC_DIR)/lib/newlib_stubs.c
USER_LIB_SRC += $(SRC_DIR)/lib/core_cm3.c

#USB
COOBOC_SRC += $(SRC_DIR)/usb/hw_config.c
COOBOC_SRC += $(SRC_DIR)/usb/usb_desc.c
COOBOC_SRC += $(SRC_DIR)/usb/usb_endp.c
COOBOC_SRC += $(SRC_DIR)/usb/usb_istr.c
COOBOC_SRC += $(SRC_DIR)/usb/usb_prop.c
COOBOC_SRC += $(SRC_DIR)/usb/usb_pwr.c

UTILS_SRC += $(SRC_DIR)/utils/line_parser.cpp

CORE_DIR = $(PWD)/lib/cmsis



#CORE_SRC +=	./STM32_USB-FS-Device_Lib_V4.1.0/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/gcc_ride7/startup_stm32f10x_md.s
CORE_SRC +=	./STM32_USB-FS-Device_Lib_V4.1.0/Libraries/CMSIS/Device/ST/STM32F10x/Source/Templates/gcc/startup_stm32f10x_md.s


DRIVER_SRC += ./STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_adc.c
#DRIVER_SRC += ./STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_bkp.c
DRIVER_SRC += ./STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_can.c
#DRIVER_SRC += ./STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_cec.c
#DRIVER_SRC += ./STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_crc.c
#DRIVER_SRC += ./STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_dac.c
#DRIVER_SRC += ./STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_dbgmcu.c
#DRIVER_SRC += ./STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_dma.c
DRIVER_SRC += ./STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_exti.c
DRIVER_SRC += ./STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_flash.c
#DRIVER_SRC += ./STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_fsmc.c
DRIVER_SRC += ./STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.c
DRIVER_SRC += ./STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_i2c.c
#DRIVER_SRC += ./STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_iwdg.c
#DRIVER_SRC += ./STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_pwr.c
DRIVER_SRC += ./STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.c
#DRIVER_SRC += ./STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_rtc.c
#DRIVER_SRC += ./STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_sdio.c
#DRIVER_SRC += ./STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_spi.c
DRIVER_SRC += ./STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_tim.c
DRIVER_SRC += ./STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_usart.c
#DRIVER_SRC += ./STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_wwdg.c
DRIVER_SRC += ./STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32F10x_StdPeriph_Driver/src/misc.c
DRIVER_SRC += ./STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32_USB-FS-Device_Driver/src/usb_init.c
DRIVER_SRC += ./STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32_USB-FS-Device_Driver/src/usb_core.c
DRIVER_SRC += ./STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32_USB-FS-Device_Driver/src/usb_regs.c
DRIVER_SRC += ./STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32_USB-FS-Device_Driver/src/usb_sil.c
DRIVER_SRC += ./STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32_USB-FS-Device_Driver/src/usb_mem.c
DRIVER_SRC += ./STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32_USB-FS-Device_Driver/src/usb_int.c

SOURCES = $(USER_LIB_SRC) $(CORE_SRC) $(DRIVER_SRC) $(UTILS_SRC) $(DEVICE_SRC) $(COOBOC_SRC) $(USER_SRC)
OBJECTS = $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(basename $(SOURCES))))

INCLUDES += -I$(SRC_DIR)
INCLUDES += -I$(SRC_DIR)/usb
INCLUDES += -I$(COOOBOC_DIR)
INCLUDES += -I$(SRC_DIR)/lib
# INCLUDES += -I./STM32_USB-FS-Device_Lib_V4.1.0/Libraries/CMSIS/CM3/CoreSupport/
INCLUDES += -I./STM32_USB-FS-Device_Lib_V4.1.0/Libraries/CMSIS/Device/ST/STM32F10x/Include/
INCLUDES += -I./STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32F10x_StdPeriph_Driver/inc/
INCLUDES += -I./STM32_USB-FS-Device_Lib_V4.1.0/Libraries/CMSIS/Include/
INCLUDES += -I./STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32_USB-FS-Device_Driver/inc/
INCLUDES += -I./STM32_USB-FS-Device_Lib_V4.1.0/Libraries/CMSIS/Device/ST/STM32F10x/Include/
INCLUDES += -I$(SRC_DIR)/utils

LDSCRIPT=./src/lib/stm32f103c8t6_cooboc.ld

CFLAGS = -std=c99 -Os -g -mcpu=cortex-m3 -mthumb -march=armv7-m  -nostartfiles -ffunction-sections -fdata-sections -Wl,--gc-sections $(INCLUDES) $(DEFS)
CXXFLAGS = $(CFLAGS)
LDFLAGS = -T$(LDSCRIPT) -mcpu=cortex-m3 -mthumb -nostartfiles

all: $(OBJECTS) $(ELF) $(BIN)
	$(SIZE) $(ELF)

test:
	echo $(SOURCES)

$(BIN): $(ELF)
	$(OBJCOPY) -O binary $< $@

$(HEX): $(ELF)
	$(OBJCOPY) -O ihex $< $@

$(ELF): $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) -o $@ -Wl,-Map=$(BUILD_DIR)/$(TARGET).map

$(BUILD_DIR)/%.o: %.s
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) -c $(CXXFLAGS) $< -o $@

clean:
	rm -rf $(BUILD_DIR)/*

flash: $(BIN)
	$(STFLASH) --reset write $(BIN) 0x8000000

reset:
	$(STFLASH) --reset

debug: $(BIN)
	$(STUTIL) > /dev/null 2>&1 &
	gdb --eval-command "target remote localhost:4242" $(BUILD_DIR)/$(PROJECT).elf -ex 'load'
	pkill -f $(STUTIL)

