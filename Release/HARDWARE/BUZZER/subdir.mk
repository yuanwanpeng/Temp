################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HARDWARE/BUZZER/BUZZER.c 

OBJS += \
./HARDWARE/BUZZER/BUZZER.o 

C_DEPS += \
./HARDWARE/BUZZER/BUZZER.d 


# Each subdirectory must supply rules for building sources it contributes
HARDWARE/BUZZER/%.o: ../HARDWARE/BUZZER/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


