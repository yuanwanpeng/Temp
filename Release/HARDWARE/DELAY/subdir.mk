################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HARDWARE/DELAY/delay.c 

OBJS += \
./HARDWARE/DELAY/delay.o 

C_DEPS += \
./HARDWARE/DELAY/delay.d 


# Each subdirectory must supply rules for building sources it contributes
HARDWARE/DELAY/%.o: ../HARDWARE/DELAY/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


