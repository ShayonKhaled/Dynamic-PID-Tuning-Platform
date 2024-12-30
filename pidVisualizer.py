import matplotlib
matplotlib.use("TkAgg")  # Use TkAgg backend for compatibility on macOS

import serial
import serial.tools.list_ports
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import tkinter as tk
from tkinter import StringVar, OptionMenu

# Global variables for serial connection
ser = None
baudRate = 115200
dataPoints = 100  # Number of points to display on the graph

# Data storage
rpmData = []
setpointData = []
pidData = []

# Labels for real-time values
pValue = None
iValue = None
dValue = None
setpointValue = None
currentSpeed = None
controlOutput = None

# Function to list available serial ports
def getSerialPorts():
    ports = serial.tools.list_ports.comports()
    return [port.device for port in ports]

# Function to start the serial connection
def startConnection(selectedPort, statusLabel, disconnectButton):
    global ser
    try:
        ser = serial.Serial(selectedPort, baudRate, timeout=1)
        statusLabel.config(text=f"Connected to {selectedPort}", fg="lightgreen")
        disconnectButton.config(state="normal")  # Enable the disconnect button
    except Exception as e:
        statusLabel.config(text=f"Failed to connect: {e}", fg="red")

# Function to disconnect the serial connection
def disconnectConnection(statusLabel, disconnectButton):
    global ser
    if ser and ser.is_open:
        ser.close()
        ser = None
        statusLabel.config(text="Disconnected", fg="red")
        disconnectButton.config(state="disabled")  # Disable the disconnect button

# Function to update the graph and all displayed values
def updateGraph(frame, pValue, iValue, dValue, setpointValue, currentSpeed, controlOutput):
    global rpmData, setpointData, pidData, ser

    if ser and ser.is_open:
        try:
            line = ser.readline().decode('utf-8').strip()
            if line:
                # Parse data (e.g., Setpoint:2000,RPM:1500,PID:500.0,P:0.5,I:0.01,D:0.001)
                data = {}
                for pair in line.split(','):
                    key, value = pair.split(':')
                    data[key] = float(value)

                # Update all displayed values
                pValue.set(f"P: {data['P']:.2f}")
                iValue.set(f"I: {data['I']:.2f}")
                dValue.set(f"D: {data['D']:.2f}")
                setpointValue.set(f"Setpoint: {data['Setpoint']:.0f}")
                currentSpeed.set(f"Speed: {data['RPM']:.0f}")
                controlOutput.set(f"Output: {data['PID']:.2f}")

                # Append data to lists
                rpmData.append(data['RPM'])
                setpointData.append(data['Setpoint'])
                pidData.append(data['PID'])

                # Keep data list lengths consistent
                if len(rpmData) > dataPoints:
                    rpmData.pop(0)
                    setpointData.pop(0)
                    pidData.pop(0)

                # Update plots
                rpmLine.set_ydata(rpmData)
                setpointLine.set_ydata(setpointData)
                pidLine.set_ydata(pidData)
                rpmLine.set_xdata(range(len(rpmData)))
                setpointLine.set_xdata(range(len(setpointData)))
                pidLine.set_xdata(range(len(pidData)))

                ax.relim()
                ax.autoscale_view()
        except Exception as e:
            print(f"Error reading data: {e}")

# Create the main application
def createApp():
    global rpmLine, setpointLine, pidLine, ax

    # Initialize the Tkinter root
    root = tk.Tk()
    root.title("Dynamic PID Tuning Platform")

    # Apply dark mode
    root.configure(bg="black")

    # Create StringVars after the root is initialized
    global pValue, iValue, dValue, setpointValue, currentSpeed, controlOutput
    pValue = StringVar(root)
    iValue = StringVar(root)
    dValue = StringVar(root)
    setpointValue = StringVar(root)
    currentSpeed = StringVar(root)
    controlOutput = StringVar(root)

    # Set default values
    pValue.set("P: 0.0")
    iValue.set("I: 0.0")
    dValue.set("D: 0.0")
    setpointValue.set("Setpoint: 0")
    currentSpeed.set("Speed: 0")
    controlOutput.set("Output: 0.0")

    # Create a frame for real-time values
    valueFrame = tk.Frame(root, bg="black")
    valueFrame.pack(side=tk.TOP, fill=tk.X)

    # Add labels for P, I, D, Setpoint, Speed, and Output
    fontSettings = ("Helvetica", 30)  # Bigger font size for better visibility
    tk.Label(valueFrame, textvariable=pValue, font=fontSettings, fg="white", bg="black").pack(side=tk.LEFT, padx=10, pady=10)
    tk.Label(valueFrame, textvariable=iValue, font=fontSettings, fg="white", bg="black").pack(side=tk.LEFT, padx=10, pady=10)
    tk.Label(valueFrame, textvariable=dValue, font=fontSettings, fg="white", bg="black").pack(side=tk.LEFT, padx=10, pady=10)
    tk.Label(valueFrame, textvariable=setpointValue, font=fontSettings, fg="white", bg="black").pack(side=tk.LEFT, padx=10, pady=10)
    tk.Label(valueFrame, textvariable=currentSpeed, font=fontSettings, fg="white", bg="black").pack(side=tk.LEFT, padx=10, pady=10)
    tk.Label(valueFrame, textvariable=controlOutput, font=fontSettings, fg="white", bg="black").pack(side=tk.LEFT, padx=10, pady=10)

    # Create a matplotlib figure with dark theme
    plt.style.use("dark_background")
    fig, ax = plt.subplots()
    rpmLine, = ax.plot([], [], label='RPM', color='cyan')
    setpointLine, = ax.plot([], [], label='Setpoint', color='lime')
    pidLine, = ax.plot([], [], label='PID Output', color='magenta')

    ax.set_title("Motor Data", color="white")
    ax.set_xlabel("Time", color="white")
    ax.set_ylabel("Values", color="white")
    ax.tick_params(colors="white")
    ax.legend(facecolor="black", edgecolor="white")

    # Embed the matplotlib figure in the Tkinter window
    canvas = FigureCanvasTkAgg(fig, master=root)
    canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=True)

    # Create a frame for the dropdown and status
    controlFrame = tk.Frame(root, bg="black")
    controlFrame.pack(side=tk.BOTTOM, fill=tk.X)

    # Dropdown menu for serial ports
    availablePorts = getSerialPorts()
    selectedPort = StringVar(root)
    if availablePorts:
        selectedPort.set(availablePorts[0])  # Default to the first available port
    else:
        selectedPort.set("No ports available")
        selected_port = StringVar(value=available_ports[0])
    tk.Label(controlFrame, text="Select Serial Port:", fg="white", bg="black").pack(side=tk.LEFT, padx=5, pady=10)
    portDropdown = OptionMenu(controlFrame, selectedPort, *availablePorts)
    portDropdown.config(bg="black", fg="white")
    portDropdown.pack(side=tk.LEFT, padx=5, pady=10)

    # Status label
    statusLabel = tk.Label(controlFrame, text="Not connected", fg="red", bg="black")
    statusLabel.pack(side=tk.LEFT, padx=5, pady=10)

    # Connect button
    connectButton = tk.Button(
        controlFrame, text="Connect", bg="white", fg="black",
        command=lambda: startConnection(selectedPort.get(), statusLabel, disconnectButton)
    )
    connectButton.pack(side=tk.LEFT, padx=5, pady=10)

    # Disconnect button
    disconnectButton = tk.Button(
        controlFrame, text="Disconnect", bg="white", fg="black",
        command=lambda: disconnectConnection(statusLabel, disconnectButton),
        state="disabled"  # Initially disabled
    )
    disconnectButton.pack(side=tk.LEFT, padx=5, pady=10)

    # Start the matplotlib animation
    ani = FuncAnimation(fig, updateGraph, interval=100, fargs=(pValue, iValue, dValue, setpointValue, currentSpeed, controlOutput), cache_frame_data=False)

    # Run the Tkinter main loop
    root.mainloop()

    # Close serial connection on exit
    if ser and ser.is_open:
        ser.close()

# Run the application
createApp()
