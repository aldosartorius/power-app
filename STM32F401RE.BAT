SET PATH=C:\Keil_v5\ARM\ARMCLANG\Bin;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Windows\System32\OpenSSH\;C:\Program Files (x86)\AMD\ATI.ACE\Core-Static;C:\Program Files\MATLAB\R2017b\runtime\win64;C:\Program Files\MATLAB\R2017b\bin;C:\Program Files (x86)\STMicroelectronics\STM32 ST-LINK Utility\ST-LINK Utility;C:\Users\aldo_\AppData\Local\Microsoft\WindowsApps;
SET ARMCC6_ASMOPT=--diag_suppress=9931
SET ARMCC6_CCOPT=--diag_suppress=9931
SET ARMCC6_LINKOPT=--diag_suppress=9931
SET CPU_TYPE=STM32F401RETx
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=STM32F401RE
SET CPU_CLOCK=0x00F42400
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @".\objects\main.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @".\objects\stm32f4xx_hal_gpio.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @".\objects\stm32f4xx_hal_gpio_cfg.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @".\objects\stm32f4xx_hal_tim.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @".\objects\stm32f4xx_hal_tim_cfg.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @".\objects\stm32f4xx_hal_uart.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @".\objects\stm32f4xx_hal_uart_cfg.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @".\objects\main_cfg.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @".\objects\startup_stm32f401xe._ac"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @".\objects\system_stm32f4xx.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmLink" --Via ".\Objects\Armdroid_Robot_PWM_Test.lnp"
"C:\Keil_v5\ARM\ARMCLANG\Bin\fromelf.exe" ".\Objects\Armdroid_Robot_PWM_Test.axf" --i32combined --output ".\Objects\Armdroid_Robot_PWM_Test.hex"
