################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HARDWARE/RTC/RTC.c 

OBJS += \
./HARDWARE/RTC/RTC.o 

C_DEPS += \
./HARDWARE/RTC/RTC.d 


# Each subdirectory must supply rules for building sources it contributes
HARDWARE/RTC/%.o: ../HARDWARE/RTC/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


