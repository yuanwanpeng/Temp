################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HARDWARE/24C0X/24C0x.c \
../HARDWARE/24C0X/IIC.c 

OBJS += \
./HARDWARE/24C0X/24C0x.o \
./HARDWARE/24C0X/IIC.o 

C_DEPS += \
./HARDWARE/24C0X/24C0x.d \
./HARDWARE/24C0X/IIC.d 


# Each subdirectory must supply rules for building sources it contributes
HARDWARE/24C0X/%.o: ../HARDWARE/24C0X/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


