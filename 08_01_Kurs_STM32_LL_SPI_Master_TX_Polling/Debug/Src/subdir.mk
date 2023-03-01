################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/logo.c \
../Src/main.c \
../Src/software_timer.c \
../Src/spi.c \
../Src/stm32g0xx_it.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/system_stm32g0xx.c 

OBJS += \
./Src/logo.o \
./Src/main.o \
./Src/software_timer.o \
./Src/spi.o \
./Src/stm32g0xx_it.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/system_stm32g0xx.o 

C_DEPS += \
./Src/logo.d \
./Src/main.d \
./Src/software_timer.d \
./Src/spi.d \
./Src/stm32g0xx_it.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/system_stm32g0xx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DSTM32G071RBTx -DSTM32 -DSTM32G0 -DSTM32G071xx -DUSE_FULL_LL_DRIVER -c -I../Inc -I"D:/STM32_Workspace_Kurs_Low_Layer/08_01_Kurs_STM32_LL_SPI_Master_TX_Polling/Drivers/CMSIS/Device/Inc" -I"D:/STM32_Workspace_Kurs_Low_Layer/08_01_Kurs_STM32_LL_SPI_Master_TX_Polling/Drivers/CMSIS/Inc" -I"D:/STM32_Workspace_Kurs_Low_Layer/08_01_Kurs_STM32_LL_SPI_Master_TX_Polling/Drivers/STM32G0xx_LL_Driver/Inc" -I"D:/STM32_Workspace_Kurs_Low_Layer/08_01_Kurs_STM32_LL_SPI_Master_TX_Polling/User/Config" -I"D:/STM32_Workspace_Kurs_Low_Layer/08_01_Kurs_STM32_LL_SPI_Master_TX_Polling/User/e-Paper" -I"D:/STM32_Workspace_Kurs_Low_Layer/08_01_Kurs_STM32_LL_SPI_Master_TX_Polling/User/Fonts" -I"D:/STM32_Workspace_Kurs_Low_Layer/08_01_Kurs_STM32_LL_SPI_Master_TX_Polling/User/GUI" -I"D:/STM32_Workspace_Kurs_Low_Layer/08_01_Kurs_STM32_LL_SPI_Master_TX_Polling/User/Config" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/logo.d ./Src/logo.o ./Src/logo.su ./Src/main.d ./Src/main.o ./Src/main.su ./Src/software_timer.d ./Src/software_timer.o ./Src/software_timer.su ./Src/spi.d ./Src/spi.o ./Src/spi.su ./Src/stm32g0xx_it.d ./Src/stm32g0xx_it.o ./Src/stm32g0xx_it.su ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/system_stm32g0xx.d ./Src/system_stm32g0xx.o ./Src/system_stm32g0xx.su

.PHONY: clean-Src

