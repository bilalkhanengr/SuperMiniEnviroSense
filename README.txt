# SuperMiniEnviroSense 🌡️
*A compact, self‑contained environmental sensor project for the ESP32‑C3 Super Mini.*

It measures temperature and humidity with an **AHT10** sensor and shows real‑time readings on a **128 × 64 SSD1306 OLED**. Built with **ESP‑IDF v5.1.x**.

---

## ✨ Features
- Ambient **temperature** and **humidity** measurement  
- Live display on a **128 × 64 SSD1306 OLED**  
- Tailored for the **ESP32‑C3 Super Mini** board  
- Single‑file drivers (AHT10 & SSD1306) contained in `main/main.c`  
- Data output to both the OLED **and** the USB serial monitor  

---

## 🔌 Hardware Required
| Quantity | Item                                      |
|:-------:|-------------------------------------------|
| 1 | ESP32‑C3 Super Mini board |
| 1 | AHT10 temperature & humidity sensor |
| 1 | 128 × 64 I²C SSD1306 OLED display |
| — | Jumper wires |

---

## 🪛 Wiring  
Both devices share the same I²C bus.

| Device Pin | ESP32‑C3 Pin |
|------------|--------------|
| **SDA**    | `GPIO8` |
| **SCL**    | `GPIO9` |
| **VIN / VCC** | `3V3` |
| **GND**    | `GND` |

---

## 💻 Software & Setup

1. **Install ESP‑IDF ≥ v5.1**  
   Follow Espressif’s official installation guide for your OS.

2. **Clone the repository**
   ```bash
   git clone https://github.com/bilalkhanengr/SuperMiniEnviroSense.git
   cd SuperMiniEnviroSense
   ```

3. **Build, flash & monitor**
   ```bash
   # Build the project
   idf.py build

   # Flash the firmware
   idf.py flash

   # Serial monitor
   idf.py monitor
   ```

---

## ⚙️ Configuration
Edit the macros at the top of `main/main.c` to match your wiring:

```c
/* ---------- user settings ---------------------------------------------- */
#define I2C_PORT      I2C_NUM_0
#define SDA_PIN       8
#define SCL_PIN       9
#define I2C_FREQ_HZ   400000

#define AHT10_ADDR    0x38
#define OLED_ADDR     0x3C      /* change to 0x3D if needed */
/* ----------------------------------------------------------------------- */
```

---

## 🚀 Usage
On power‑up the firmware:

1. Initializes the AHT10 and the OLED.  
2. Updates the display **every second**.

```
+----------------------+
| Temp: 28.5 °C        |
| Hum : 62.1 %         |
|                      |
|                      |
|                      |
|                      |
|                      |
|                      |
+----------------------+
```

The same readings appear on the serial monitor for debugging.

---

## 📜 License
This project is licensed under the **MIT License**.

MIT License

Copyright (c) 2024 Bilal Khan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
