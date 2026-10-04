# STM32 作品合集

基于 **STM32F103C8T6** 的入门到进阶外设练习合集，使用 **STM32 标准外设库（StdPeriph Library）** 开发，涵盖 GPIO、中断、定时器、PWM、ADC、OLED 显示、直流电机与舵机控制等内容。每个文件夹都是一个独立、可直接编译下载的 Keil 工程。

## 开发环境

| 项目 | 说明 |
| --- | --- |
| 主控芯片 | STM32F103C8T6（Cortex-M3，72 MHz） |
| 固件库 | STM32F10x 标准外设库 V3.5 |
| 开发工具 | Keil MDK-ARM 5（ARMCC） |
| 下载调试 | ST-Link / CMSIS-DAP |

## 工程列表

| 文件夹 | 功能 | 涉及知识点 |
| --- | --- | --- |

| `电协1点灯大师` | 按键与 LED 综合练习 | GPIO 输入/输出 |
| `电协2进化：流水灯！` | 多种流水灯模式 | GPIO、逻辑控制 |
| `电协3觉醒吧， oled！` | OLED 界面显示 | I2C、字库取模、界面刷新 |
| `电协4面对疾风吧` | PWM 驱动直流电机调速 | 定时器 PWM、电机驱动、OLED 状态显示 |
| `电协5来个舵机摇一摇` | 电位器控制舵机角度 | ADC + PWM 舵机控制、角度映射 |

## 目录结构

每个工程内部结构基本一致：

```
工程目录/
├── User/          # main.c、中断处理、工程配置
├── Hardware/      # 外设驱动（LED、Key、OLED、Motor、Servo 等）
├── System/        # 系统级文件（时钟、延时等）
├── Start/         # 启动文件与内核相关头文件
├── Library/       # STM32 标准外设库源码
├── Listings/      # 编译输出（已忽略，不入库）
├── Objects/       # 编译输出（已忽略，不入库）
├── DebugConfig/   # 调试配置（已忽略，不入库）
├── 接线/          # 接线示意图（部分工程）
└── Project.uvprojx # Keil 工程文件，双击打开
```

## 使用方法

1. 安装 Keil MDK-ARM 5 及 STM32F1 芯片支持包（Keil::STM32F1xx_DFP）。
2. 进入对应工程文件夹，双击打开 `Project.uvprojx`。
3. 连接 ST-Link，点击 **Build（F7）** 编译，**Download（F8）** 下载。
4. 编译输出目录（`Objects`、`Listings`、`DebugConfig`）不纳入版本管理，可由 Keil 自动生成；也可运行工程内的 `keilkill.bat` 清理。

## 说明

- 仓库仅保存源码、库文件与 Keil 工程配置，编译中间文件（`.o/.d/.crf/.axf` 等）已通过 `.gitignore` 排除。
- 部分工程的 `User/main_注释版.txt` 为带详细注释的学习备份。
