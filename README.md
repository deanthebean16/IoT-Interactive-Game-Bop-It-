# IoT-Interactive-Game-Bop-It 

| [YouTube Video Demo/Explaination](https://youtu.be/YgGdhbMRT2k) |

---

### Project Overview
This project is a hardware-based recreation of the classic "Bop It" game. It utilizes an **ESP32 microcontroller** to process real-time inputs from physical buttons and wireless commands, challenging the user's reaction time through a series of randomized instructions.

---

### Key Features & Logic
* **Event-Driven Input Handling:** Developed logic in **C++** to asynchronously process inputs from physical tactile buttons and wireless **Dabble Gamepad** inputs via Bluetooth.
* **Real-Time Feedback:** Integrated an **OLED display** via the **I2C protocol** to provide instant user instructions, score tracking, and "Game Over" sequences.
* **Virtual Prototyping:** Utilized the **Wokwi Simulator** to validate circuit logic and pin configurations before physical battery-powered deployment.

* ### Technical Logic Breakdown

#### 1. Randomized Instruction Engine
The game generates a random integer to determine the next action (Bop, Twist, Pull). The user must respond within a shrinking time window to continue.

```cpp
// Sample Logic: Generating and Validating Game State
void nextMove() {
    targetAction = random(1, 4); // 1 = Bop, 2 = Twist, 3 = Pull
    displayInstruction(targetAction);
    startTime = millis();
    
    while (millis() - startTime < timeLimit) {
        if (checkInput() == targetAction) {
            score++;
            timeLimit -= 50; // Increase difficulty
            return;
        }
    }
    gameOver();
}
```

### Hybrid Input Logic (Dabble + Physical)
The game checks both the local hardware pins and the Bluetooth serial stream from the Dabble app to register a "Bop"

```cpp
int checkInput() {
    Dabble.processInput(); 
    if (digitalRead(BOP_BUTTON_PIN) == LOW || Gamepad.isPressed(2)) {
        return 1; // Bop detected
    }
    // Additional logic for Twist and Pull sensors...
    return 0;
}
```

### Built With

* **Microcontroller**: ESP32 (Dual-core, Wi-Fi/Bluetooth enabled)
* **Languages**: C++ (Arduino Framework)
* **Protocols**: I2C (for OLED), Bluetooth/BLE (for Dabble integration)
* **Tools**: VS Code, Arduino IDE, Wokwi Circuit Simulator
