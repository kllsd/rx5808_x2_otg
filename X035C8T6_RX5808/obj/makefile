################################################################################
# MRS Version: 1.9.1
# 自动生成的文件。不要编辑！
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include User/subdir.mk
-include System/subdir.mk
-include Startup/subdir.mk
-include Peripheral/src/subdir.mk
-include Hardware/rx5808/subdir.mk
-include Hardware/oled/subdir.mk
-include Debug/subdir.mk
-include Core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
X035C8T6_RX5808.hex \

SECONDARY_LIST += \
X035C8T6_RX5808.lst \

SECONDARY_SIZE += \
X035C8T6_RX5808.siz \


# 所有目标
all: X035C8T6_RX5808.elf secondary-outputs

# 工具调用
X035C8T6_RX5808.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -T "D:\Chip_development\WCH\CH32X035C8T6\Project\X035C8T6_RX5808\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"X035C8T6_RX5808.map" --specs=nano.specs --specs=nosys.specs -o "X035C8T6_RX5808.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@	@
X035C8T6_RX5808.hex: X035C8T6_RX5808.elf
	@	riscv-none-embed-objcopy -O ihex "X035C8T6_RX5808.elf"  "X035C8T6_RX5808.hex"
	@	@
X035C8T6_RX5808.lst: X035C8T6_RX5808.elf
	@	riscv-none-embed-objdump --all-headers --demangle --disassemble -M xw "X035C8T6_RX5808.elf" > "X035C8T6_RX5808.lst"
	@	@
X035C8T6_RX5808.siz: X035C8T6_RX5808.elf
	@	riscv-none-embed-size --format=berkeley "X035C8T6_RX5808.elf"
	@	@
# 其他目标
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) X035C8T6_RX5808.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
