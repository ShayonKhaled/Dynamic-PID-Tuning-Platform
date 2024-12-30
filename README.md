# **Dynamic PID Tuning Platform**

## **Overview**

The **Dynamic PID Tuning Platform** is a user-friendly test rig built to make PID tuning easier for robotics projects. It’s specifically designed for tuning the PID settings of DJI Robomaster M3508 P19 motors, which are controlled using C620 ESCs via the CAN protocol.

With this platform, you can easily adjust PID parameters and monitor real-time feedback on setpoints, motor speed (RPM), and control outputs. The data is displayed on an onboard LCD and can also be visualized using an external Python-based tool for more detailed analysis.

---

## **Features**
- **Real-time PID Tuning:** Adjust P, I, and D values using rotary encoders.
- **CAN Bus Communication:** Sends control data to Robomaster C620 ESCs.
- **Live Monitoring:** Displays motor speed, setpoint, and PID outputs on a 20x4 LCD display.
- **External Visualization:** Outputs CSV-formatted data to a Python-based GUI for graphing and analysis.

### **Limitations**
- At this time, the code supports controlling only **one motor** at a time.

---

## **Hardware Components**
- **Freenove ESP32 Dev Board** (or any ESP32 board)
- **Robomaster C620 ESC** and **M3508 P19 Motor**
- **MCP2515 CAN module**
- **KY-040 Rotary Encoders** (4x for P, I, D, and setpoint)
- **20x4 LCD Display** with I2C Backpack (PCF8574)

### **Recommended Wiring**
For easier connections, it is recommended to use a Freenove ESP32 breakout board. You can also build the circuit on a breadboard if necessary. Using an external 5V power source for peripherals is highly recommended.

---

## **Pin Connections**

| **Component**               | **Pin on Component**   | **Pin on ESP32**  |
|------------------------------|------------------------|-------------------|
| MCP2515 CAN Module           | CS                    | GPIO 5            |
|                              | INT                   | GPIO 15           |
| KY-040 Encoder (P)           | CLK                   | GPIO 35           |
|                              | DT                    | GPIO 32           |
| KY-040 Encoder (I)           | CLK                   | GPIO 25           |
|                              | DT                    | GPIO 33           |
| KY-040 Encoder (D)           | CLK                   | GPIO 27           |
|                              | DT                    | GPIO 26           |
| KY-040 Encoder (Setpoint)    | CLK                   | GPIO 39           |
|                              | DT                    | GPIO 34           |
| 20x4 LCD Display with I2C    | SDA                   | GPIO 21           |
|                              | SCL                   | GPIO 22           |

---

## **Software Features**
### **ESP32 Firmware**
- Written in Arduino framework using PlatformIO.
- Implements PID control logic with:
  - Adjustable P, I, D values using rotary encoders.
  - Real-time CAN communication with the C620 ESC.
  - CSV-formatted serial data output for visualization.

### **Python Visualization Tool**
- Plots real-time graphs of:
  - Motor RPM
  - Setpoint
  - PID output
- Provides GUI controls for serial port selection.

---

## **Setup Instructions**
1. **Hardware Setup:**
   - Connect all components as per the pin connections table.
   - Use an external 5V power source for the MCP2515 module and the LCD to ensure stability.

2. **Software Setup:**
   - Install PlatformIO extension on Visual Studio Code if you haven't already.
   - Clone this repository:
     ```bash
     git clone https://github.com/ShayonKhaled/Dynamic-PID-Tuning-Platform.git
     ```
   - Open the project in PlatformIO and upload the firmware to your ESP32.

3. **Python Visualization:**
   - Install required Python libraries:
     ```bash
     pip install matplotlib pyserial tkinter
     ```
   - Run the Python script for real-time graphing:
     ```bash
     python3 pidVisualizer.py
     ```
   - Select the serial port of your ESP32 from the drop down menu and hit the connect button. The ESP32 must be connected to your computer. 

---

## **Notes**
- **Power Supply:** Avoid drawing power for the MCP2515 and LCD display directly from the ESP32. Use a separate 5V supply to prevent voltage drops and ensure reliable operation.
- **Freenove ESP32 Breakout Board:** The breakout board simplifies wiring but is not mandatory.

---


## **Building the DIN Rail Test Rack**

To house the components and provide a modular design, I used **4X 250mm DIN rails** to build the test rack. The stands for the rails were designed by **PlasticXYZ** and can be found here: [DIN Rail Test Rack Stands by PlasticXYZ](https://www.printables.com/model/150786-din-rail-test-rack).

### **Custom Mount Designs**
I designed custom mounts for the following components:
- **Freenove ESP32 Breakout Board**
- **MCP2515 CAN Transceiver Module**
- **Rotary Encoders**
- **20x4 LCD**

These designs are included in the **"3D Printables"** folder in both **.STL** and **.STEP** formats. You can choose to:
1. **Bolt the mounts directly onto the DIN rail**, or
2. **Use DIN clips** (designed by PlasticXYZ) to attach them. The DIN clips can be mounted or unmounted easily from the DIN rails. You can find the DIN clips design here: [DIN Rail Clip by PlasticXYZ](https://www.printables.com/model/161740-din-rail-clip).

### **Mounting Specifications**
- **Mounting Holes:** 18mm apart. These can be modified using the provided `.STEP` files if needed.
- **Fasteners Used:**
  - **Modules:** Mounted with self-tapping screws.
  - **DIN Clips:** Mounted with M3 bolts (6mm length).
- **No Heat Press Inserts:** The mounts were specifically designed for simplicity, and all components are secured with self-tapping screws or bolts.

This setup provides a sturdy, modular, and customizable framework for the PID tuning platform, making it easy to assemble, modify, and expand as needed.



## **License**
This project is licensed under the GNU General Public License v3.0 License. See the [LICENSE](LICENSE) file for details.

---
