################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HARDWARE/DMA/dma.c 

OBJS += \
./HARDWARE/DMA/dma.o 

C_DEPS += \
./HARDWARE/DMA/dma.d 


# Each subdirectory must supply rules for building sources it contributes
HARDWARE/DMA/%.o: ../HARDWARE/DMA/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


