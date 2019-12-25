################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/tasks/WATCHDOG/subdir.mk
-include src/tasks/HEARTBEAT/subdir.mk
-include src/tasks/GPIOS/subdir.mk
-include src/tasks/DSP/subdir.mk
-include src/tasks/DISPLAY/subdir.mk
-include src/tasks/CONTROL/subdir.mk
-include src/tasks/ADC_DAC/subdir.mk
-include src/main/subdir.mk
-include src/c-tds/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: ej12_i2s_mixto.axf

# Tool invocations
ej12_i2s_mixto.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\nicol\OneDrive\Documentos\td2_ultimaV\lpc_board_nxp_lpcxpresso_1769\Debug" -L"C:\Users\nicol\OneDrive\Documentos\td2_ultimaV\CMSIS_DSPLIB_CM3\lib" -L"C:\Users\nicol\OneDrive\Documentos\td2_ultimaV\lpc_chip_175x_6x\Debug" -Xlinker -Map="ej12_i2s_mixto.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m3 -mthumb -T "ej12_i2s_mixto_Debug.ld" -o "ej12_i2s_mixto.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) ej12_i2s_mixto.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "ej12_i2s_mixto.axf"; # arm-none-eabi-objcopy -v -O binary "ej12_i2s_mixto.axf" "ej12_i2s_mixto.bin" ; # checksum -p LPC1769 -d "ej12_i2s_mixto.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
