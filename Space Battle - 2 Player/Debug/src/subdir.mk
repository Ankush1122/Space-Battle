################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Space\ Battle\ Deluxe.c 

OBJS += \
./src/Space\ Battle\ Deluxe.o 

C_DEPS += \
./src/Space\ Battle\ Deluxe.d 


# Each subdirectory must supply rules for building sources it contributes
src/Space\ Battle\ Deluxe.o: ../src/Space\ Battle\ Deluxe.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Space Battle Deluxe.d" -MT"src/Space\ Battle\ Deluxe.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


