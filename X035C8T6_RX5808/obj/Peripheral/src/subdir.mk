################################################################################
# MRS Version: 1.9.1
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Peripheral/src/ch32x035_adc.c \
../Peripheral/src/ch32x035_awu.c \
../Peripheral/src/ch32x035_dbgmcu.c \
../Peripheral/src/ch32x035_dma.c \
../Peripheral/src/ch32x035_exti.c \
../Peripheral/src/ch32x035_flash.c \
../Peripheral/src/ch32x035_gpio.c \
../Peripheral/src/ch32x035_i2c.c \
../Peripheral/src/ch32x035_iwdg.c \
../Peripheral/src/ch32x035_misc.c \
../Peripheral/src/ch32x035_opa.c \
../Peripheral/src/ch32x035_pwr.c \
../Peripheral/src/ch32x035_rcc.c \
../Peripheral/src/ch32x035_spi.c \
../Peripheral/src/ch32x035_tim.c \
../Peripheral/src/ch32x035_usart.c \
../Peripheral/src/ch32x035_wwdg.c 

OBJS += \
./Peripheral/src/ch32x035_adc.o \
./Peripheral/src/ch32x035_awu.o \
./Peripheral/src/ch32x035_dbgmcu.o \
./Peripheral/src/ch32x035_dma.o \
./Peripheral/src/ch32x035_exti.o \
./Peripheral/src/ch32x035_flash.o \
./Peripheral/src/ch32x035_gpio.o \
./Peripheral/src/ch32x035_i2c.o \
./Peripheral/src/ch32x035_iwdg.o \
./Peripheral/src/ch32x035_misc.o \
./Peripheral/src/ch32x035_opa.o \
./Peripheral/src/ch32x035_pwr.o \
./Peripheral/src/ch32x035_rcc.o \
./Peripheral/src/ch32x035_spi.o \
./Peripheral/src/ch32x035_tim.o \
./Peripheral/src/ch32x035_usart.o \
./Peripheral/src/ch32x035_wwdg.o 

C_DEPS += \
./Peripheral/src/ch32x035_adc.d \
./Peripheral/src/ch32x035_awu.d \
./Peripheral/src/ch32x035_dbgmcu.d \
./Peripheral/src/ch32x035_dma.d \
./Peripheral/src/ch32x035_exti.d \
./Peripheral/src/ch32x035_flash.d \
./Peripheral/src/ch32x035_gpio.d \
./Peripheral/src/ch32x035_i2c.d \
./Peripheral/src/ch32x035_iwdg.d \
./Peripheral/src/ch32x035_misc.d \
./Peripheral/src/ch32x035_opa.d \
./Peripheral/src/ch32x035_pwr.d \
./Peripheral/src/ch32x035_rcc.d \
./Peripheral/src/ch32x035_spi.d \
./Peripheral/src/ch32x035_tim.d \
./Peripheral/src/ch32x035_usart.d \
./Peripheral/src/ch32x035_wwdg.d 


# Each subdirectory must supply rules for building sources it contributes
Peripheral/src/%.o: ../Peripheral/src/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\Chip_development\WCH\CH32X035C8T6\Project\X035C8T6_RX5808\Debug" -I"D:\Chip_development\WCH\CH32X035C8T6\Project\X035C8T6_RX5808\Core" -I"D:\Chip_development\WCH\CH32X035C8T6\Project\X035C8T6_RX5808\User" -I"D:\Chip_development\WCH\CH32X035C8T6\Project\X035C8T6_RX5808\Peripheral\inc" -I"D:\Chip_development\WCH\CH32X035C8T6\Project\X035C8T6_RX5808\System" -I"D:\Chip_development\WCH\CH32X035C8T6\Project\X035C8T6_RX5808\Hardware\oled" -I"D:\Chip_development\WCH\CH32X035C8T6\Project\X035C8T6_RX5808\Hardware\rx5808" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

