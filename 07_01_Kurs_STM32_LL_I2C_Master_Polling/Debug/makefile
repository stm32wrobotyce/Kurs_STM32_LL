################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include Drivers/STM32G0xx_LL_Driver/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := 07_01_Kurs_STM32_LL_I2C_Master_Polling
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
07_01_Kurs_STM32_LL_I2C_Master_Polling.elf \

MAP_FILES += \
07_01_Kurs_STM32_LL_I2C_Master_Polling.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
07_01_Kurs_STM32_LL_I2C_Master_Polling.list \


# All Target
all: main-build

# Main-build Target
main-build: 07_01_Kurs_STM32_LL_I2C_Master_Polling.elf secondary-outputs

# Tool invocations
07_01_Kurs_STM32_LL_I2C_Master_Polling.elf 07_01_Kurs_STM32_LL_I2C_Master_Polling.map: $(OBJS) $(USER_OBJS) D:\STM32_Workspace_Kurs_Low_Layer\07_01_Kurs_STM32_LL_I2C_Master_Polling\STM32G071RBTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "07_01_Kurs_STM32_LL_I2C_Master_Polling.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m0plus -T"D:\STM32_Workspace_Kurs_Low_Layer\07_01_Kurs_STM32_LL_I2C_Master_Polling\STM32G071RBTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="07_01_Kurs_STM32_LL_I2C_Master_Polling.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

07_01_Kurs_STM32_LL_I2C_Master_Polling.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "07_01_Kurs_STM32_LL_I2C_Master_Polling.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) 07_01_Kurs_STM32_LL_I2C_Master_Polling.elf 07_01_Kurs_STM32_LL_I2C_Master_Polling.list 07_01_Kurs_STM32_LL_I2C_Master_Polling.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
