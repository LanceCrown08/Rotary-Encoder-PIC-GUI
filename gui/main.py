import serial
import serial.tools.list_ports
import tkinter as tk

# ---------- LIST AVAILABLE COM PORTS ----------
ports = list(serial.tools.list_ports.comports())
print("Available COM ports:")
for p in ports:
    print(p.device)

# ---------- CHANGE THIS TO CORRECT PORT ----------
PORT = "COM3"   # <-- CHANGE AFTER CHECKING ABOVE

try:
    ser = serial.Serial(PORT, 9600, timeout=1)
except serial.SerialException as e:
    print("ERROR: Cannot open serial port")
    print(e)
    input("Press Enter to exit...")
    exit()

# ---------- GUI ----------
root = tk.Tk()
root.title("Rotary Encoder GUI")
root.geometry("300x150")

label = tk.Label(root, text="Waiting for data...", font=("Arial", 18))
label.pack(pady=40)

def read_serial():
    try:
        if ser.in_waiting:
            line = ser.readline().decode(errors="ignore").strip()
            print("RX:", line)
            if line.startswith("COUNT:"):
                value = line.split(":")[1]
                label.config(text=f"Count: {value}")
    except Exception as e:
        print("Serial read error:", e)

    root.after(50, read_serial)

read_serial()
root.mainloop()
#use this command in cmd after connecting the output to com 3
#cd C:\Users\Suraj Khanduri\.vscode
#python encoder_gui.py
