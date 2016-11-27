# makefile for the XMC2GO with XMC1100-64

XMCPL=./XMC_Peripheral_Library_v2.1.8
CMSIS=$(XMCPL)/CMSIS
XMCLIB=$(XMCPL)/XMCLib
NEWLIB=$(XMCPL)/Newlib

PROJ_NAME=nerfcontrol

LIBSPEC=-L /usr/arm-none-eabi/lib/armv6-m
JLINKEXE = /home/daniel/dev/JLink_Linux_V612_x86_64/JLinkExe
INC=-I$(XMCLIB)/inc -I./XMC_Peripheral_Library_v2.1.8/CMSIS/Include -I$(CMSIS)/Infineon/XMC1100_series/Include

CC=arm-none-eabi-gcc
AS=arm-none-eabi-as
LD=arm-none-eabi-ld
OBJCOPY=arm-none-eabi-objcopy
STRIP=arm-none-eabi-strip
JLINKOPT = -device xmc1100-64 -if SWD -speed 400
DEVICE=-DXMC1100_Q024x0064

CCFLAGS=-mcpu=cortex-m0 -mthumb -g --specs=nosys.specs -nostartfiles -T$(CMSIS)/Infineon/XMC1100_series/Source/GCC/XMC1100x0064.ld 
	
SRCS = main.c pwm.c
SRCS += $(CMSIS)/Infineon/XMC1100_series/Source/GCC/startup_XMC1100.S
SRCS += $(CMSIS)/Infineon/XMC1100_series/Source/system_XMC1100.c
SRCS += $(XMCLIB)/src/xmc_gpio.c
SRCS += $(XMCLIB)/src/xmc_ccu4.c
SRCS += $(XMCLIB)/src/xmc1_scu.c
SRCS += $(XMCLIB)/src/xmc1_gpio.c
SRCS += $(XMCLIB)/src/xmc_vadc.c

.PHONY: proj

all: proj

proj: $(PROJ_NAME).elf

$(PROJ_NAME).elf: $(SRCS)
	$(CC) $(INC) $(DEVICE) $(CCFLAGS) $^ -o $@
	$(STRIP) $@
	$(OBJCOPY) -O ihex $(PROJ_NAME).elf $(PROJ_NAME).hex
	$(OBJCOPY) -O binary $(PROJ_NAME).elf $(PROJ_NAME).bin


define SEGGER_FLASH_SOFTDEVICE_CMD
r
loadbin $(PROJ_NAME).bin 0x10001000
r
g
exit
endef

export SEGGER_FLASH_SOFTDEVICE_CMD

flash: $(PROJ_NAME).bin
	@echo "$$SEGGER_FLASH_SOFTDEVICE_CMD" | $(JLINKEXE) $(JLINKOPT)

clean: 
	rm -f *.o $(TARGET).map $(PROJ_NAME).bin $(PROJ_NAME).hex $(PROJ_NAME).elf