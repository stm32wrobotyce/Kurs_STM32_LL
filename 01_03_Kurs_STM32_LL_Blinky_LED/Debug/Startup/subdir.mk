################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Startup/startup_stm32g071rbtx.s 

OBJS += \
./Startup/startup_stm32g071rbtx.o 

S_DEPS += \
./Startup/startup_stm32g071rbtx.d 


# Each subdirectory must supply rules for building sources it contributes
Startup/%.o: ../Startup/%.s Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m0plus -g3 -DDEBUG -c -I"D:/STM32_Workspace_Kurs_Low_Layer/01_03_Kurs_STM32_LL_Blinky_LED/Drivers/CMSIS/Device/Inc" -I"D:/STM32_Workspace_Kurs_Low_Layer/01_03_Kurs_STM32_LL_Blinky_LED/Drivers/CMSIS/Inc" -I"D:/STM32_Workspace_Kurs_Low_Layer/01_03_Kurs_STM32_LL_Blinky_LED/Drivers/STM32G0xx_LL_Driver/Inc" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

clean: clean-Startup

clean-Startup:
	-$(RM) ./Startup/startup_stm32g071rbtx.d ./Startup/startup_stm32g071rbtx.o

.PHONY: clean-Startup

