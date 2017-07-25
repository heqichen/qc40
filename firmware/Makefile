CROSS_COMPILE ?= arm-none-eabi-
CC = $(CROSS_COMPILE)gcc
OBJCOPY = $(CROSS_COMPILE)objcopy
LIBOPENCM3 ?= ./libopencm3

STFLASH=../tools/stlink/bin-amd64/st-flash

TARGET=./stm32-tx-hid

APP_ADDRESS = 0x08002000
APP_OFFSET = $(shell echo $$(($(APP_ADDRESS) - 0x08000000)))

CFLAGS = -Os -std=gnu99 -Wall -pedantic -Werror -Istm32/include \
	-mcpu=cortex-m3 -mthumb -DSTM32F1 \
	-I$(LIBOPENCM3)/include -DAPP_ADDRESS=$(APP_ADDRESS) -ggdb3

LDFLAGS = -lopencm3_stm32f1 \
	-Wl,-Tstm32f103.ld -nostartfiles -lc -lnosys \
	-mthumb -mcpu=cortex-m3 -L$(LIBOPENCM3)/lib/ -Wl,-gc-sections

$(TARGET)-bootldr-combined.bin: $(TARGET)-bootldr.bin $(TARGET).bin
	cp $(TARGET)-bootldr.bin $@
	dd if=$(TARGET).bin of=$@ seek=1 bs=$(APP_OFFSET)

$(TARGET).elf: $(TARGET).o | $(LIBOPENCM3)/lib/libopencm3_stm32f1.a
	$(CC) $^ -o $@ $(LDFLAGS) -Wl,-Ttext=$(APP_ADDRESS)

$(TARGET)-bootldr.elf: $(TARGET)-bootldr.o | $(LIBOPENCM3)/lib/libopencm3_stm32f1.a
	$(CC) $^ -o $@ $(LDFLAGS)

$(LIBOPENCM3)/lib/libopencm3_stm32f1.a:
	$(MAKE) -C $(LIBOPENCM3) TARGETS=stm32/f1

%.bin: %.elf
	$(OBJCOPY) -O binary $^ $@

clean:
	-rm *.elf *.o *.bin

flash:
	$(STFLASH) --reset write $(TARGET)-bootldr-combined.bin 0x8000000

dfu:
	dfu-util -d 0483:df11 -R -s 0x8002000 -D stm32-tx-hid.bin