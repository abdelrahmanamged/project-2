# 🖥️ Vole Machine Simulator
### Modern C++ Core Engine | Interactive Qt Desktop GUI

A modular, object-oriented simulator for the **Vole (Brookshear) Machine Architecture**, built from the ground up using **Modern C++ (C++17)** and **Qt Widgets**.

The project provides a complete simulation environment with two independent interfaces:

- **Command-Line Interface (CLI):** For terminal-based program execution.
- **Qt Desktop GUI:** An interactive graphical environment for monitoring memory, registers, CPU state, and program execution in real time.

Developed as part of the **CS213 – Object-Oriented Programming** course at the **Faculty of Computers and Artificial Intelligence, Cairo University (FCAI-CU)**, under the supervision of **Dr. Mohamed El-Ramly**.

---

## ✨ 1. Key Features

### ⚙️ Core Simulation Engine (C++)

The simulation engine models the fundamental components of the Vole Machine architecture.

- **Von Neumann Architecture:** Simulates 256 bytes of linear addressable memory (`0x00–0xFF`), 16 general-purpose 8-bit registers (`R0–RF`), a Program Counter (`PC`), and an Instruction Register (`IR`).
- **Complete Instruction Set:** Supports the machine's instruction set (Opcodes `1–C`), including:
  - Memory load and store operations.
  - Register-to-register data transfers.
  - Two's complement integer addition.
  - Floating-point arithmetic.
  - Bitwise logical operations (`OR`, `AND`, `XOR`).
  - Bitwise right rotations.
  - Conditional jumps.
  - Program termination (`C000`).
- **Fetch-Decode-Execute Cycle:** Executes instructions through a structured CPU processing pipeline.
- **Memory-Mapped I/O (`0xFF`):** Writing a byte to memory address `0xFF` sends its character representation or hexadecimal value to the dedicated screen buffer.
- **Input Validation:** Validates hexadecimal input, removes assembly comments (`;`), enforces valid starting addresses (`0x00–0xFE`), and rejects malformed instructions before execution.

### 🎨 Interactive Qt Desktop GUI

The Qt Widgets interface provides real-time visibility into the internal state of the simulated machine.

#### Live 16×16 Memory Grid

- Displays all 256 memory cells in a structured 16×16 layout.
- Highlights important memory locations:
  - 🟡 **Gold/Amber:** Current Program Counter (`PC`).
  - 🔹 **Light Cyan:** Operand byte (`PC + 1`).
  - 🟢 **Mint Green:** Memory-mapped screen port (`0xFF`).
- **Inline Memory Editing:** Double-click any memory cell to edit its hexadecimal value directly.

#### Real-Time CPU & Register Monitoring

- Displays all 16 general-purpose registers (`R0–RF`).
- Shows register values in:
  - Hexadecimal.
  - Decimal.
  - ASCII.
- Tracks the current `PC`, `IR`, execution step counter, and machine status.
- Includes a human-readable instruction translator to explain the currently executed instruction.

#### Flexible Execution Controls

- **Custom Start Address:** Select a program loading address using a hexadecimal spin box (`0x00–0xFE`, step 2).
- **Continuous Execution:** Run programs automatically with adjustable execution speed (10–500 ms).
- **Single-Step Execution:** Execute one instruction at a time for detailed debugging and instruction tracking.
- **Machine Controls:** Run, pause, reset, and monitor the simulation.

#### CRT-Style Screen Display

- Dedicated terminal-style display connected to the memory-mapped screen port (`0xFF`).
- Instantly reflects screen output during program execution.
- Includes a Clear Screen control.

#### GUI Keyboard Shortcuts

| Shortcut | Action |
|---|---|
| `Ctrl
