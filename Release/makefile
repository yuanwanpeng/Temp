################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Src/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/RVDS/ARM_CM3/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/subdir.mk
-include MDK-ARM/TEMP/subdir.mk
-include MDK-ARM/RTE/Data_Exchange/subdir.mk
-include HARDWARE/RTC/subdir.mk
-include HARDWARE/RELAY/subdir.mk
-include HARDWARE/LED/subdir.mk
-include HARDWARE/LCD12864/subdir.mk
-include HARDWARE/HUMI/subdir.mk
-include HARDWARE/ESP8266/subdir.mk
-include HARDWARE/DMA/subdir.mk
-include HARDWARE/DELAY/subdir.mk
-include HARDWARE/BUZZER/subdir.mk
-include HARDWARE/BUTTON/subdir.mk
-include HARDWARE/24C0X/subdir.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include Drivers/CMSIS/Device/ST/STM32F1xx/Source/Templates/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Source/TransformFunctions/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Source/SupportFunctions/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Source/StatisticsFunctions/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Source/MatrixFunctions/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Source/FastMathFunctions/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Source/ControllerFunctions/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Source/ComplexMathFunctions/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Source/CommonTables/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Source/BasicMathFunctions/subdir.mk
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
all: eclipse_for_TEMP

# Tool invocations
eclipse_for_TEMP: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross GCC Linker'
	gcc  -o "eclipse_for_TEMP" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) eclipse_for_TEMP
	-@echo ' '

.PHONY: all clean dependents

-include ../makefile.targets
