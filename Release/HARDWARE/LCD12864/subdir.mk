################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HARDWARE/LCD12864/LCD12864.c \
../HARDWARE/LCD12864/LCD12864_Display_Menu.c \
../HARDWARE/LCD12864/LCD12864_Display_Menu_Delay_Inspection.c \
../HARDWARE/LCD12864/LCD12864_Display_Menu_HUMI_Compensation.c \
../HARDWARE/LCD12864/LCD12864_Display_Menu_Max_Route.c \
../HARDWARE/LCD12864/LCD12864_Display_Menu_Route_Reset.c \
../HARDWARE/LCD12864/LCD12864_Display_Menu_Set_Strategy.c \
../HARDWARE/LCD12864/LCD12864_Display_Menu_Set_Strategy_Info.c \
../HARDWARE/LCD12864/LCD12864_Display_Menu_Set_Time.c \
../HARDWARE/LCD12864/LCD12864_Display_Menu_Stroking_Cycle.c \
../HARDWARE/LCD12864/LCD12864_Display_Menu_Version_Information.c \
../HARDWARE/LCD12864/TypeFace.c 

OBJS += \
./HARDWARE/LCD12864/LCD12864.o \
./HARDWARE/LCD12864/LCD12864_Display_Menu.o \
./HARDWARE/LCD12864/LCD12864_Display_Menu_Delay_Inspection.o \
./HARDWARE/LCD12864/LCD12864_Display_Menu_HUMI_Compensation.o \
./HARDWARE/LCD12864/LCD12864_Display_Menu_Max_Route.o \
./HARDWARE/LCD12864/LCD12864_Display_Menu_Route_Reset.o \
./HARDWARE/LCD12864/LCD12864_Display_Menu_Set_Strategy.o \
./HARDWARE/LCD12864/LCD12864_Display_Menu_Set_Strategy_Info.o \
./HARDWARE/LCD12864/LCD12864_Display_Menu_Set_Time.o \
./HARDWARE/LCD12864/LCD12864_Display_Menu_Stroking_Cycle.o \
./HARDWARE/LCD12864/LCD12864_Display_Menu_Version_Information.o \
./HARDWARE/LCD12864/TypeFace.o 

C_DEPS += \
./HARDWARE/LCD12864/LCD12864.d \
./HARDWARE/LCD12864/LCD12864_Display_Menu.d \
./HARDWARE/LCD12864/LCD12864_Display_Menu_Delay_Inspection.d \
./HARDWARE/LCD12864/LCD12864_Display_Menu_HUMI_Compensation.d \
./HARDWARE/LCD12864/LCD12864_Display_Menu_Max_Route.d \
./HARDWARE/LCD12864/LCD12864_Display_Menu_Route_Reset.d \
./HARDWARE/LCD12864/LCD12864_Display_Menu_Set_Strategy.d \
./HARDWARE/LCD12864/LCD12864_Display_Menu_Set_Strategy_Info.d \
./HARDWARE/LCD12864/LCD12864_Display_Menu_Set_Time.d \
./HARDWARE/LCD12864/LCD12864_Display_Menu_Stroking_Cycle.d \
./HARDWARE/LCD12864/LCD12864_Display_Menu_Version_Information.d \
./HARDWARE/LCD12864/TypeFace.d 


# Each subdirectory must supply rules for building sources it contributes
HARDWARE/LCD12864/%.o: ../HARDWARE/LCD12864/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


