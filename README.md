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
| `Ctrl + O` | Load a program file |
| `F5` | Run / Pause execution |
| `F10` | Execute a single instruction |
| `F2` | Reset machine state |

---

## 🏗️ 2. System Architecture & OOP Design

The project follows a modular architecture based on **Object-Oriented Programming principles**, with a clear separation between the simulation engine and its presentation layers.

It applies SOLID design principles and uses architectural patterns such as **Facade** and **Dependency Injection** to improve modularity, maintainability, and component interaction.

### Core Components

| Component | Responsibility |
|---|---|
| `VoleMachine` | Main Facade coordinating the CPU, Memory, RegisterFile, ProgramLoader, and display components. |
| `CPU` | Manages the Fetch-Decode-Execute cycle, PC, IR, and instruction processing. |
| `Memory` | Encapsulates the 256-byte memory space using `std::vector<uint8_t>` with boundary checks. |
| `RegisterFile` | Manages the 16 general-purpose registers (`R0–RF`) with index validation. |
| `ProgramLoader` | Parses external assembly/machine-code files, removes comments, validates input, and loads programs into memory. |
| `ScreenDisplay` | Provides a hardware abstraction for the memory-mapped screen peripheral at address `0xFF`. |
| `ConsoleUI` | Handles command-line interaction with the simulation engine. |
| `MainWindow` | Implements the Qt graphical interface and real-time machine visualization. |

### Architectural Highlights

- Separation of core simulation logic from user interfaces.
- Modular and independent hardware component classes.
- Reference-based component interaction through dependency injection.
- Centralized coordination through the `VoleMachine` Facade.
- Multiple UML design iterations documented using PlantUML.

---

## 📂 3. Repository Structure

```text
project-2/
│
├── classes.cpp/             # Core C++ source files
├── classes.h/               # Core C++ header files
│
├── qt project2/             # Qt Desktop GUI project
│   ├── MainWindow
│   ├── VoleSimulator.pro
│   └── CMakeLists.txt
│
├── even or odd.txt          # Sample assembly program
├── Documentation.pdf        # Architecture, UML diagrams & test cases
└── README.md                # Project documentation
```

---

## 🚀 4. Getting Started

### Prerequisites

Before running the project, make sure you have:

- A C++17-compatible compiler (GCC or MSVC).
- Qt 5.15+ or Qt 6.x.
- Qt Creator (recommended for the GUI version).
- The appropriate Qt Desktop Kit (MinGW or MSVC).

### Step 1: Clone the Repository

```bash
git clone https://github.com/abdelrahmanamged/project-2.git

cd project-2
```

### Step 2: Build & Run the Qt GUI (Recommended)

1. Open **Qt Creator**.
2. Select `File → Open File or Project`.
3. Navigate to the `qt project2` directory.
4. Open `VoleSimulator.pro` or `CMakeLists.txt`.
5. Select your configured Qt Desktop Kit.
6. Click **Configure Project**.
7. Press `Ctrl + R` or click the Run button to build and launch the simulator.

### Step 3: Build & Run the CLI Version

Compile the core C++ source files using a C++17-compatible compiler.

Example using GCC:

```bash
g++ -std=c++17 classes.cpp/*.cpp -I classes.h -o VoleSimulatorCLI
```

Run the executable:

```bash
./VoleSimulatorCLI
```

**Note:** The compilation command assumes the source and header directory structure matches the repository layout. Adjust the paths if necessary.

---

## 🧪 5. Sample Assembly Program

The repository includes an example program (`even or odd.txt`) that determines whether the value stored in `R1` is even or odd.

It uses a bitwise AND operation with the mask `0x01` to inspect the least significant bit, then displays the corresponding result through the memory-mapped screen port (`0xFF`).

### Sample Code

```asm
2108 ; Load 0x08 into R1
2201 ; Load bit-mask 0x01 into R2
8312 ; R3 = R1 AND R2
B314 ; If R3 == R0, jump to address 0x14

244F ; Load ASCII 'O' into R4
34FF ; Print 'O' to screen
2444 ; Load ASCII 'D' into R4
34FF ; Print 'D' to screen
34FF ; Print 'D' to screen
C000 ; Halt execution

2445 ; Load ASCII 'E' into R4 (Even branch)
34FF ; Print 'E' to screen
2456 ; Load ASCII 'V' into R4
34FF ; Print 'V' to screen
2445 ; Load ASCII 'E' into R4
34FF ; Print 'E' to screen
244E ; Load ASCII 'N' into R4
34FF ; Print 'N' to screen
C000 ; Halt execution
```

### Expected Output

```text
EVEN
```

Changing the initial value loaded into `R1` allows testing both execution paths.

---

## 👥 6. Team Members

Developed collaboratively by students of the **Faculty of Computers and Artificial Intelligence, Cairo University**.

| Team Member | Key Contributions |
|---|---|
| **Omar Ayman Mohamed (Team Leader)** | Initial class architecture design, assembly test programs, Qt GUI synchronization, and debugging. |
| **Abdelrahman Amgad Mosad** | GitHub repository management, CPU and ProgramLoader implementation, AI-assisted design synthesis, and project walkthrough video. |
| **Hesham Waleed Fawzi** | Technical documentation, VoleMachine coordination, and ConsoleUI refinements. |
| **Yassine Awadallah Bakry** | Initial PlantUML diagrams, Memory, RegisterFile, and ScreenDisplay implementation. |

---

## 📄 7. License & Educational Purpose

This project was developed for educational purposes as part of the **CS213 – Object-Oriented Programming** course at the Faculty of Computers and Artificial Intelligence, Cairo University.

---

⭐ **If you find this project interesting, feel free to explore the repository and check out the implementation!**
