# Real-world I2C Trojan Project

## Overview

This repository contains the implementation for **Part 3: Impersonating the EEPROM** and **Part 4: A Machine-in-the-Middle Attack** of the Real-world I2C Trojan project. These tasks are part of an academic exercise in hardware security, utilizing STM32 microcontroller development kits to explore the vulnerabilities and behaviors of I2C communication systems.

The repository focuses on:
- Mimicking an EEPROM using an STM32 NUCLEO-F411RE microcontroller (Part 3).
- Developing a Trojan device capable of modifying I2C communications in a controlled manner (Part 4).

## Prerequisites

### Hardware
- STM32 NUCLEO-F411RE development kit
- STM32 F042K6 development board
- 24C32 EEPROM
- Required peripherals (e.g., jumper wires, breadboards)

### Software
- [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html)
- STM32 HAL libraries for I2C and UART communication
- Debugging tools (optional: logic analyzer for I2C analysis)

---

## Part 3: Impersonating the EEPROM

In this task, the STM32 NUCLEO-F411RE microcontroller is programmed to impersonate a 24C32 EEPROM. The implementation involves:
1. Setting up the I2C peripheral API on the NUCLEO-F411RE.
2. Using interrupts for handling I2C communication:
   - **`HAL_I2C_AddrCallback`**: Triggered when the secondary device receives an I2C transmission.
   - **`HAL_I2C_SlaveRxCpltCallback`**: Handles received data.
   - **`HAL_I2C_ListenCpltCallback`**: Resets the I2C interrupt after transmission completion.
3. Storing the memory buffer in the on-board RAM to simulate EEPROM behavior.

### Key Functions
- `HAL_I2C_EnableListen_IT`: Enables the interrupt-based listening mode.
- `HAL_I2C_Slave_Seq_Receive_IT`: Receives data from the primary device.
- `HAL_I2C_Slave_Seq_Transmit_IT`: Transmits data to the primary device.

### Testing
- The EEPROM impersonation was tested using a second development board acting as the primary device.

---

## Part 4: A Machine-in-the-Middle Attack

This task combines the previous parts to create a Trojan device that intercepts and modifies I2C communications:
1. **Interception**:
   - Receives commands from the main controller and forwards them to the EEPROM.
   - Implements a conditional logic-based response:
     - Discards or modifies write operations starting at address `0x0200`.
     - Replaces read data starting at `0x0200` with a predefined value.
2. **Key Modifications**:
   - Blocks write propagation for specific addresses.
   - Responds with custom data patterns during read requests.

### Custom Data for Address `0x0200`
- The returned data starts with the pattern: `09 F9 11 02 9D 74 E3 5B D8 41 56 C5 63 56 88 C0`.

### Key Functions
- **Clock-stretching**: Used to handle delays in communication while processing malicious logic.

### Testing
- Multiple hardware setups were used to validate the functionality, including:
  - An STM32 F042K6 as the main controller.
  - A physical 24C32 EEPROM for baseline comparison.
  - Logic analyzers to verify I2C traffic.

---

## How to Use

1. Clone the repository:
   ```bash
   git clone https://github.com/ali-rasteh/I2C_Trojan.git
   ```
2. Open the respective project in STM32CubeIDE.
3. Compile and upload the code to the STM32 NUCLEO-F411RE board.
4. Connect the hardware as per the project diagrams in the documentation.
5. Use a logic analyzer to monitor I2C communication.

---

## Acknowledgments

- **Course**: EL 9453 - Introduction to Hardware Security and Trust (NYU Tandon School of Engineering)
- **Resources**:
  - STM32 HAL documentation
  - [CAT24C32 EEPROM Datasheet](https://www.onsemi.com/pdf/datasheet/cat24c32-d.pdf)

## License

This project is licensed under the MIT License. See the LICENSE file for details.
