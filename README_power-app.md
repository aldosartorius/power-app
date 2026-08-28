# power-app

Firmware for the **power microcontroller** (STM32F401RE) of the Armdroid 2001
dual-MCU control and power platform.

This code generates the PWM signal and rotation direction for each motor
bridge, and is the application layer running on top of the
[`HAL_STM32F401`](https://github.com/aldosartorius/HAL_STM32F401) hardware
abstraction layer (HAL_GPIO, HAL_TIM, HAL_UART, HAL_EXTI).

## Scope and relation to the platform paper

The platform's electronics and firmware support **6 actuator channels**:
the 5 arm joints (5-DOF) plus a gripper (Motor 6).

The manuscript **"Open-Architecture Dual-MCU Control and Power Platform for
a Legacy 5-DOF Manipulator: Design and Experimental
Characterization"** reports
characterization of the **5 arm joints only (Motors 1–5)**. Motor 6
(gripper) is implemented and operational in this firmware but is **outside
the scope** of the experiments reported in that manuscript (E1, E2, E3).

## Communication protocol (used in this snapshot)

Host (PC) → MCU, single character per motor + direction command, received
via UART1 interrupt (`USART1_IRQHandler`):

| Char | Action          | Char | Action          |
|------|-----------------|------|------------------|
| A    | Motor1 forward  | B    | Motor1 backward  |
| C    | Motor2 forward  | D    | Motor2 backward  |
| E    | Motor3 forward  | F    | Motor3 backward  |
| G    | Motor4 forward  | H    | Motor4 backward  |
| I    | Motor5 forward  | J    | Motor5 backward  |
| K    | Motor6 forward  | L    | Motor6 backward  |

Each command drives the motor at a fixed open-loop duty cycle (`speed`,
currently 0.8) for a fixed time window (`MotorOnTimeMiliseconds`, currently
400 ms), then disables all bridges.

This is the **simplified single-character protocol** used to generate the
experimental data reported in the paper. A formal 24-byte frame protocol
with per-motor duty cycle is in separate, ongoing development and is
**not** part of this snapshot.

## Dependencies

- [`HAL_STM32F401`](https://github.com/aldosartorius/HAL_STM32F401) —
  tagged [`v2.0.0-platform-paper`](https://github.com/aldosartorius/HAL_STM32F401/releases/tag/v2.0.0-platform-paper)
  (commit `c234d27`)

## Reproducibility note

This repository is tagged `v1.0-power-app-platform-paper` as the exact
snapshot used to generate the results reported in the manuscript
referenced above. This tag will not be modified or deleted after
submission. Any future fix will be published under a separate tag (e.g.
`v1.0.1-power-app-platform-paper-revised`).
