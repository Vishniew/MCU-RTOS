################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/usart1_Tx.c 

OBJS += \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/usart1_Tx.o 

C_DEPS += \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/usart1_Tx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F746NGHx -DSTM32F746G_DISCO -DSTM32F7 -c -I../Inc -I"/home/packetp/STM32F407/MCU_1/stm32f7xx_drivers/drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/usart1_Tx.cyclo ./Src/usart1_Tx.d ./Src/usart1_Tx.o ./Src/usart1_Tx.su

.PHONY: clean-Src

