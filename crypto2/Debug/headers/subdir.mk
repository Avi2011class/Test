################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../headers/converter.cpp \
../headers/encoder.cpp \
../headers/keys.cpp \
../headers/scanner.cpp \
../headers/simple_math.cpp \
../headers/writer.cpp 

OBJS += \
./headers/converter.o \
./headers/encoder.o \
./headers/keys.o \
./headers/scanner.o \
./headers/simple_math.o \
./headers/writer.o 

CPP_DEPS += \
./headers/converter.d \
./headers/encoder.d \
./headers/keys.d \
./headers/scanner.d \
./headers/simple_math.d \
./headers/writer.d 


# Each subdirectory must supply rules for building sources it contributes
headers/%.o: ../headers/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -O3 -Wall -c -fmessage-length=0 -fopenmp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


