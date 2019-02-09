################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HARDWARE/RELAY/Check_Stroking_Cycle.c \
../HARDWARE/RELAY/Monitor_IN1.c \
../HARDWARE/RELAY/relay.c 

OBJS += \
./HARDWARE/RELAY/Check_Stroking_Cycle.o \
./HARDWARE/RELAY/Monitor_IN1.o \
./HARDWARE/RELAY/relay.o 

C_DEPS += \
./HARDWARE/RELAY/Check_Stroking_Cycle.d \
./HARDWARE/RELAY/Monitor_IN1.d \
./HARDWARE/RELAY/relay.d 


# Each subdirectory must supply rules for building sources it contributes
HARDWARE/RELAY/%.o: ../HARDWARE/RELAY/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


