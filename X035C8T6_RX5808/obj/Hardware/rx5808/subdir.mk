################################################################################
# MRS Version: 1.9.1
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Hardware/rx5808/rtc6715.c \
../Hardware/rx5808/rx5808.c 

OBJS += \
./Hardware/rx5808/rtc6715.o \
./Hardware/rx5808/rx5808.o 

C_DEPS += \
./Hardware/rx5808/rtc6715.d \
./Hardware/rx5808/rx5808.d 


# Each subdirectory must supply rules for building sources it contributes
Hardware/rx5808/%.o: ../Hardware/rx5808/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\Chip_development\WCH\CH32X035C8T6\Project\X035C8T6_RX5808\Debug" -I"D:\Chip_development\WCH\CH32X035C8T6\Project\X035C8T6_RX5808\Core" -I"D:\Chip_development\WCH\CH32X035C8T6\Project\X035C8T6_RX5808\User" -I"D:\Chip_development\WCH\CH32X035C8T6\Project\X035C8T6_RX5808\Peripheral\inc" -I"D:\Chip_development\WCH\CH32X035C8T6\Project\X035C8T6_RX5808\System" -I"D:\Chip_development\WCH\CH32X035C8T6\Project\X035C8T6_RX5808\Hardware\oled" -I"D:\Chip_development\WCH\CH32X035C8T6\Project\X035C8T6_RX5808\Hardware\rx5808" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

