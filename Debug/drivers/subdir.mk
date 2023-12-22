################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_anatop_ai.c \
../drivers/fsl_cache.c \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_common_arm.c \
../drivers/fsl_dcdc.c \
../drivers/fsl_enet.c \
../drivers/fsl_gpio.c \
../drivers/fsl_lpuart.c \
../drivers/fsl_pmu.c 

C_DEPS += \
./drivers/fsl_anatop_ai.d \
./drivers/fsl_cache.d \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_common_arm.d \
./drivers/fsl_dcdc.d \
./drivers/fsl_enet.d \
./drivers/fsl_gpio.d \
./drivers/fsl_lpuart.d \
./drivers/fsl_pmu.d 

OBJS += \
./drivers/fsl_anatop_ai.o \
./drivers/fsl_cache.o \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_common_arm.o \
./drivers/fsl_dcdc.o \
./drivers/fsl_enet.o \
./drivers/fsl_gpio.o \
./drivers/fsl_lpuart.o \
./drivers/fsl_pmu.o 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c drivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -D_POSIX_SOURCE -DXIP_BOOT_HEADER_DCD_ENABLE=1 -DUSE_SDRAM -DDATA_SECTION_IS_CACHEABLE=1 -DCPU_MIMXRT1166DVM6A_cm7 -DSDK_DEBUGCONSOLE=1 -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DLWIP_ENET_FLEXIBLE_CONFIGURATION -DFSL_SDK_ENABLE_DRIVER_CACHE_CONTROL=1 -DFSL_FEATURE_PHYKSZ8081_USE_RMII50M_MODE -DUSE_RTOS=1 -DPRINTF_ADVANCED_ENABLE=1 -DFSL_SDK_DRIVER_QUICK_ACCESS_ENABLE=1 -DLWIP_DISABLE_PBUF_POOL_SIZE_SANITY_CHECKS=1 -DSERIAL_PORT_TYPE_UART=1 -DSDK_OS_FREE_RTOS -DMCUXPRESSO_SDK -DCPU_MIMXRT1166DVM6A -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\os\Documents\MCUXpressoIDE_11.8.0_1165\2_13_RT1160\evkmimxrt1160_lwip_ping_freertos_cm7__test\source" -I"C:\Users\os\Documents\MCUXpressoIDE_11.8.0_1165\2_13_RT1160\evkmimxrt1160_lwip_ping_freertos_cm7__test\component\phy" -I"C:\Users\os\Documents\MCUXpressoIDE_11.8.0_1165\2_13_RT1160\evkmimxrt1160_lwip_ping_freertos_cm7__test\lwip\port" -I"C:\Users\os\Documents\MCUXpressoIDE_11.8.0_1165\2_13_RT1160\evkmimxrt1160_lwip_ping_freertos_cm7__test\lwip\src" -I"C:\Users\os\Documents\MCUXpressoIDE_11.8.0_1165\2_13_RT1160\evkmimxrt1160_lwip_ping_freertos_cm7__test\lwip\src\include" -I"C:\Users\os\Documents\MCUXpressoIDE_11.8.0_1165\2_13_RT1160\evkmimxrt1160_lwip_ping_freertos_cm7__test\drivers" -I"C:\Users\os\Documents\MCUXpressoIDE_11.8.0_1165\2_13_RT1160\evkmimxrt1160_lwip_ping_freertos_cm7__test\component\silicon_id" -I"C:\Users\os\Documents\MCUXpressoIDE_11.8.0_1165\2_13_RT1160\evkmimxrt1160_lwip_ping_freertos_cm7__test\lwip\contrib\apps\ping" -I"C:\Users\os\Documents\MCUXpressoIDE_11.8.0_1165\2_13_RT1160\evkmimxrt1160_lwip_ping_freertos_cm7__test\device" -I"C:\Users\os\Documents\MCUXpressoIDE_11.8.0_1165\2_13_RT1160\evkmimxrt1160_lwip_ping_freertos_cm7__test\utilities" -I"C:\Users\os\Documents\MCUXpressoIDE_11.8.0_1165\2_13_RT1160\evkmimxrt1160_lwip_ping_freertos_cm7__test\component\uart" -I"C:\Users\os\Documents\MCUXpressoIDE_11.8.0_1165\2_13_RT1160\evkmimxrt1160_lwip_ping_freertos_cm7__test\component\serial_manager" -I"C:\Users\os\Documents\MCUXpressoIDE_11.8.0_1165\2_13_RT1160\evkmimxrt1160_lwip_ping_freertos_cm7__test\component\lists" -I"C:\Users\os\Documents\MCUXpressoIDE_11.8.0_1165\2_13_RT1160\evkmimxrt1160_lwip_ping_freertos_cm7__test\startup" -I"C:\Users\os\Documents\MCUXpressoIDE_11.8.0_1165\2_13_RT1160\evkmimxrt1160_lwip_ping_freertos_cm7__test\xip" -I"C:\Users\os\Documents\MCUXpressoIDE_11.8.0_1165\2_13_RT1160\evkmimxrt1160_lwip_ping_freertos_cm7__test\CMSIS" -I"C:\Users\os\Documents\MCUXpressoIDE_11.8.0_1165\2_13_RT1160\evkmimxrt1160_lwip_ping_freertos_cm7__test\freertos\freertos-kernel\include" -I"C:\Users\os\Documents\MCUXpressoIDE_11.8.0_1165\2_13_RT1160\evkmimxrt1160_lwip_ping_freertos_cm7__test\freertos\freertos-kernel\portable\GCC\ARM_CM4F" -I"C:\Users\os\Documents\MCUXpressoIDE_11.8.0_1165\2_13_RT1160\evkmimxrt1160_lwip_ping_freertos_cm7__test\board" -Og -fno-common -g3 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-drivers

clean-drivers:
	-$(RM) ./drivers/fsl_anatop_ai.d ./drivers/fsl_anatop_ai.o ./drivers/fsl_cache.d ./drivers/fsl_cache.o ./drivers/fsl_clock.d ./drivers/fsl_clock.o ./drivers/fsl_common.d ./drivers/fsl_common.o ./drivers/fsl_common_arm.d ./drivers/fsl_common_arm.o ./drivers/fsl_dcdc.d ./drivers/fsl_dcdc.o ./drivers/fsl_enet.d ./drivers/fsl_enet.o ./drivers/fsl_gpio.d ./drivers/fsl_gpio.o ./drivers/fsl_lpuart.d ./drivers/fsl_lpuart.o ./drivers/fsl_pmu.d ./drivers/fsl_pmu.o

.PHONY: clean-drivers

