################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/Config/DEV_Config.c 

OBJS += \
./User/Config/DEV_Config.o 

C_DEPS += \
./User/Config/DEV_Config.d 


# Each subdirectory must supply rules for building sources it contributes
User/Config/%.o User/Config/%.su: ../User/Config/%.c User/Config/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DSTM32G071RBTx -DSTM32 -DSTM32G0 -DSTM32G071xx -DUSE_FULL_LL_DRIVER -c -I../Inc -I"D:/STM32_Workspace_Kurs_Low_Layer/08_01_Kurs_STM32_LL_SPI_Master_TX_Polling/Drivers/CMSIS/Device/Inc" -I"D:/STM32_Workspace_Kurs_Low_Layer/08_01_Kurs_STM32_LL_SPI_Master_TX_Polling/Drivers/CMSIS/Inc" -I"D:/STM32_Workspace_Kurs_Low_Layer/08_01_Kurs_STM32_LL_SPI_Master_TX_Polling/Drivers/STM32G0xx_LL_Driver/Inc" -I"D:/STM32_Workspace_Kurs_Low_Layer/08_01_Kurs_STM32_LL_SPI_Master_TX_Polling/User/Config" -I"D:/STM32_Workspace_Kurs_Low_Layer/08_01_Kurs_STM32_LL_SPI_Master_TX_Polling/User/e-Paper" -I"D:/STM32_Workspace_Kurs_Low_Layer/08_01_Kurs_STM32_LL_SPI_Master_TX_Polling/User/Fonts" -I"D:/STM32_Workspace_Kurs_Low_Layer/08_01_Kurs_STM32_LL_SPI_Master_TX_Polling/User/GUI" -I"D:/STM32_Workspace_Kurs_Low_Layer/08_01_Kurs_STM32_LL_SPI_Master_TX_Polling/User/Config" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-User-2f-Config

clean-User-2f-Config:
	-$(RM) ./User/Config/DEV_Config.d ./User/Config/DEV_Config.o ./User/Config/DEV_Config.su

.PHONY: clean-User-2f-Config

