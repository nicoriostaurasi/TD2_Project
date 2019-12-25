################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/tasks/AdcTask_lpc1769.c \
../src/tasks/ControlTask.c \
../src/tasks/GpiosTask_lpc1769.c \
../src/tasks/filtrado.c \
../src/tasks/task-heartbeat_lpc1769.c \
../src/tasks/task-watchdog_lpc1769.c 

OBJS += \
./src/tasks/AdcTask_lpc1769.o \
./src/tasks/ControlTask.o \
./src/tasks/GpiosTask_lpc1769.o \
./src/tasks/filtrado.o \
./src/tasks/task-heartbeat_lpc1769.o \
./src/tasks/task-watchdog_lpc1769.o 

C_DEPS += \
./src/tasks/AdcTask_lpc1769.d \
./src/tasks/ControlTask.d \
./src/tasks/GpiosTask_lpc1769.d \
./src/tasks/filtrado.d \
./src/tasks/task-heartbeat_lpc1769.d \
./src/tasks/task-watchdog_lpc1769.d 


# Each subdirectory must supply rules for building sources it contributes
src/tasks/%.o: ../src/tasks/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -D__LPC17XX__ -D__REDLIB__ -I"C:\Users\nicol\OneDrive\Documentos\workspace_domingo\CMSIS_DSPLIB_CM3\inc" -I"C:\Users\nicol\OneDrive\Documentos\workspace_domingo\CMSIS_DSPLIB_CM3\inc\arm" -I"C:\Users\nicol\OneDrive\Documentos\workspace_domingo\lpc_board_nxp_lpcxpresso_1769\inc" -I"C:\Users\nicol\OneDrive\Documentos\workspace_domingo\lpc_chip_175x_6x\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


