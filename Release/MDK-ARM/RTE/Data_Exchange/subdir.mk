################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MDK-ARM/RTE/Data_Exchange/jansson_config.c 

OBJS += \
./MDK-ARM/RTE/Data_Exchange/jansson_config.o 

C_DEPS += \
./MDK-ARM/RTE/Data_Exchange/jansson_config.d 


# Each subdirectory must supply rules for building sources it contributes
MDK-ARM/RTE/Data_Exchange/%.o: ../MDK-ARM/RTE/Data_Exchange/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


