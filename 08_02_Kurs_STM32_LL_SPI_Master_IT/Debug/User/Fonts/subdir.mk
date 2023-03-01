################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/Fonts/font12.c \
../User/Fonts/font12CN.c \
../User/Fonts/font16.c \
../User/Fonts/font20.c \
../User/Fonts/font24.c \
../User/Fonts/font24CN.c \
../User/Fonts/font8.c 

OBJS += \
./User/Fonts/font12.o \
./User/Fonts/font12CN.o \
./User/Fonts/font16.o \
./User/Fonts/font20.o \
./User/Fonts/font24.o \
./User/Fonts/font24CN.o \
./User/Fonts/font8.o 

C_DEPS += \
./User/Fonts/font12.d \
./User/Fonts/font12CN.d \
./User/Fonts/font16.d \
./User/Fonts/font20.d \
./User/Fonts/font24.d \
./User/Fonts/font24CN.d \
./User/Fonts/font8.d 


# Each subdirectory must supply rules for building sources it contributes
User/Fonts/%.o User/Fonts/%.su: ../User/Fonts/%.c User/Fonts/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DSTM32G071RBTx -DSTM32 -DSTM32G0 -DSTM32G071xx -DUSE_FULL_LL_DRIVER -c -I../Inc -I"D:/STM32_Workspace_Kurs_Low_Layer/08_01_Kurs_STM32_LL_SPI_Master_TX_Polling/Drivers/CMSIS/Device/Inc" -I"D:/STM32_Workspace_Kurs_Low_Layer/08_01_Kurs_STM32_LL_SPI_Master_TX_Polling/Drivers/CMSIS/Inc" -I"D:/STM32_Workspace_Kurs_Low_Layer/08_01_Kurs_STM32_LL_SPI_Master_TX_Polling/Drivers/STM32G0xx_LL_Driver/Inc" -I"D:/STM32_Workspace_Kurs_Low_Layer/08_01_Kurs_STM32_LL_SPI_Master_TX_Polling/User/Config" -I"D:/STM32_Workspace_Kurs_Low_Layer/08_01_Kurs_STM32_LL_SPI_Master_TX_Polling/User/e-Paper" -I"D:/STM32_Workspace_Kurs_Low_Layer/08_01_Kurs_STM32_LL_SPI_Master_TX_Polling/User/Fonts" -I"D:/STM32_Workspace_Kurs_Low_Layer/08_01_Kurs_STM32_LL_SPI_Master_TX_Polling/User/GUI" -I"D:/STM32_Workspace_Kurs_Low_Layer/08_01_Kurs_STM32_LL_SPI_Master_TX_Polling/User/Config" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-User-2f-Fonts

clean-User-2f-Fonts:
	-$(RM) ./User/Fonts/font12.d ./User/Fonts/font12.o ./User/Fonts/font12.su ./User/Fonts/font12CN.d ./User/Fonts/font12CN.o ./User/Fonts/font12CN.su ./User/Fonts/font16.d ./User/Fonts/font16.o ./User/Fonts/font16.su ./User/Fonts/font20.d ./User/Fonts/font20.o ./User/Fonts/font20.su ./User/Fonts/font24.d ./User/Fonts/font24.o ./User/Fonts/font24.su ./User/Fonts/font24CN.d ./User/Fonts/font24CN.o ./User/Fonts/font24CN.su ./User/Fonts/font8.d ./User/Fonts/font8.o ./User/Fonts/font8.su

.PHONY: clean-User-2f-Fonts

