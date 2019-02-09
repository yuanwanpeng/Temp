################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HARDWARE/BUTTON/button.c 

OBJS += \
./HARDWARE/BUTTON/button.o 

C_DEPS += \
./HARDWARE/BUTTON/button.d 


# Each subdirectory must supply rules for building sources it contributes
HARDWARE/BUTTON/%.o: ../HARDWARE/BUTTON/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


