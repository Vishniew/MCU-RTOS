################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/packetp/WS/RTOS_WS/Common/ThirdParty/FreeRTOS/portable/MemMang/heap_4.c 

OBJS += \
./Common/ThirdParty/FreeRTOS/portable/MemMang/heap_4.o 

C_DEPS += \
./Common/ThirdParty/FreeRTOS/portable/MemMang/heap_4.d 


# Each subdirectory must supply rules for building sources it contributes
Common/ThirdParty/FreeRTOS/portable/MemMang/heap_4.o: /home/packetp/WS/RTOS_WS/Common/ThirdParty/FreeRTOS/portable/MemMang/heap_4.c Common/ThirdParty/FreeRTOS/portable/MemMang/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I/home/packetp/WS/RTOS_WS/Common/ThirdParty/FreeRTOS/include -I/home/packetp/WS/RTOS_WS/Common/ThirdParty/FreeRTOS/portable/GCC/ARM_CM7/r0p1 -I/home/packetp/WS/RTOS_WS/Common/ThirdParty/SEGGER/Config -I/home/packetp/WS/RTOS_WS/Common/ThirdParty/SEGGER/OS -I/home/packetp/WS/RTOS_WS/Common/ThirdParty/SEGGER/SEGGER -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Common-2f-ThirdParty-2f-FreeRTOS-2f-portable-2f-MemMang

clean-Common-2f-ThirdParty-2f-FreeRTOS-2f-portable-2f-MemMang:
	-$(RM) ./Common/ThirdParty/FreeRTOS/portable/MemMang/heap_4.cyclo ./Common/ThirdParty/FreeRTOS/portable/MemMang/heap_4.d ./Common/ThirdParty/FreeRTOS/portable/MemMang/heap_4.o ./Common/ThirdParty/FreeRTOS/portable/MemMang/heap_4.su

.PHONY: clean-Common-2f-ThirdParty-2f-FreeRTOS-2f-portable-2f-MemMang

