################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/bsp/iks01a1/lps22hb/LPS22HB_Driver.c \
../lib/bsp/iks01a1/lps22hb/LPS22HB_Driver_HL.c 

OBJS += \
./lib/bsp/iks01a1/lps22hb/LPS22HB_Driver.o \
./lib/bsp/iks01a1/lps22hb/LPS22HB_Driver_HL.o 

C_DEPS += \
./lib/bsp/iks01a1/lps22hb/LPS22HB_Driver.d \
./lib/bsp/iks01a1/lps22hb/LPS22HB_Driver_HL.d 


# Each subdirectory must supply rules for building sources it contributes
lib/bsp/iks01a1/lps22hb/LPS22HB_Driver.o: ../lib/bsp/iks01a1/lps22hb/LPS22HB_Driver.c lib/bsp/iks01a1/lps22hb/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F1 -DNUCLEO_F103RB -DSTM32F103RBTx -DSTM32 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../lib/bsp -I../lib//middleware/MIDI/ -I../lib/bsp/iks01a1 -I../lib/bsp/iks01a1/Common -I../lib/bsp/iks01a1/hts221 -I../lib/bsp/iks01a1/lis3mdl -I../lib/bsp/iks01a1/lps22hb -I../lib/bsp/iks01a1/lps25hb -I../lib/bsp/iks01a1/lsm6ds0 -I../lib/bsp/iks01a1/lsm6ds3 -I../lib/bsp/tft_ili9341 -I../lib/bsp/tft_pcd8544 -I../lib/hal/inc -I../lib/bsp/Common -I../lib/CMSIS/core -I../lib/CMSIS/device -I../lib/middleware/FatFs -I../lib/middleware/FatFs/src -I../lib/middleware/FatFs/src/drivers -I../appli -O0 -ffunction-sections -fdata-sections -Wall -Wextra -Wconversion -fstack-usage -MMD -MP -MF"lib/bsp/iks01a1/lps22hb/LPS22HB_Driver.d" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"
lib/bsp/iks01a1/lps22hb/LPS22HB_Driver_HL.o: ../lib/bsp/iks01a1/lps22hb/LPS22HB_Driver_HL.c lib/bsp/iks01a1/lps22hb/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F1 -DNUCLEO_F103RB -DSTM32F103RBTx -DSTM32 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../lib/bsp -I../lib//middleware/MIDI/ -I../lib/bsp/iks01a1 -I../lib/bsp/iks01a1/Common -I../lib/bsp/iks01a1/hts221 -I../lib/bsp/iks01a1/lis3mdl -I../lib/bsp/iks01a1/lps22hb -I../lib/bsp/iks01a1/lps25hb -I../lib/bsp/iks01a1/lsm6ds0 -I../lib/bsp/iks01a1/lsm6ds3 -I../lib/bsp/tft_ili9341 -I../lib/bsp/tft_pcd8544 -I../lib/hal/inc -I../lib/bsp/Common -I../lib/CMSIS/core -I../lib/CMSIS/device -I../lib/middleware/FatFs -I../lib/middleware/FatFs/src -I../lib/middleware/FatFs/src/drivers -I../appli -O0 -ffunction-sections -fdata-sections -Wall -Wextra -Wconversion -fstack-usage -MMD -MP -MF"lib/bsp/iks01a1/lps22hb/LPS22HB_Driver_HL.d" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"

