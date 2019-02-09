################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HARDWARE/ESP8266/ESP8266.c \
../HARDWARE/ESP8266/HTTP_CODE.c 

OBJS += \
./HARDWARE/ESP8266/ESP8266.o \
./HARDWARE/ESP8266/HTTP_CODE.o 

C_DEPS += \
./HARDWARE/ESP8266/ESP8266.d \
./HARDWARE/ESP8266/HTTP_CODE.d 


# Each subdirectory must supply rules for building sources it contributes
HARDWARE/ESP8266/%.o: ../HARDWARE/ESP8266/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


