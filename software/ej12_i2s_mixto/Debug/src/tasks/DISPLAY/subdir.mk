################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/tasks/DISPLAY/DisplayTASK.c \
../src/tasks/DISPLAY/display_func.c \
../src/tasks/DISPLAY/display_globales.c \
../src/tasks/DISPLAY/display_int.c \
../src/tasks/DISPLAY/fonts.c 

OBJS += \
./src/tasks/DISPLAY/DisplayTASK.o \
./src/tasks/DISPLAY/display_func.o \
./src/tasks/DISPLAY/display_globales.o \
./src/tasks/DISPLAY/display_int.o \
./src/tasks/DISPLAY/fonts.o 

C_DEPS += \
./src/tasks/DISPLAY/DisplayTASK.d \
./src/tasks/DISPLAY/display_func.d \
./src/tasks/DISPLAY/display_globales.d \
./src/tasks/DISPLAY/display_int.d \
./src/tasks/DISPLAY/fonts.d 


# Each subdirectory must supply rules for building sources it contributes
src/tasks/DISPLAY/%.o: ../src/tasks/DISPLAY/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -D__LPC17XX__ -D__REDLIB__ -I"C:\Users\nicol\OneDrive\Documentos\td2_ultimaV\CMSIS_DSPLIB_CM3\inc" -I"C:\Users\nicol\OneDrive\Documentos\td2_ultimaV\CMSIS_DSPLIB_CM3\inc\arm" -I"C:\Users\nicol\OneDrive\Documentos\td2_ultimaV\lpc_board_nxp_lpcxpresso_1769\inc" -I"C:\Users\nicol\OneDrive\Documentos\td2_ultimaV\lpc_chip_175x_6x\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


