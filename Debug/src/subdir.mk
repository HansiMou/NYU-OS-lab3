################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/bitoperation.o \
../src/main.o \
../src/pager.o \
../src/prepare.o \
../src/random.o 

CPP_SRCS += \
../src/bitoperation.cpp \
../src/main.cpp \
../src/pager.cpp \
../src/prepare.cpp \
../src/random.cpp \
../src/vmm.cpp 

OBJS += \
./src/bitoperation.o \
./src/main.o \
./src/pager.o \
./src/prepare.o \
./src/random.o \
./src/vmm.o 

CPP_DEPS += \
./src/bitoperation.d \
./src/main.d \
./src/pager.d \
./src/prepare.d \
./src/random.d \
./src/vmm.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


