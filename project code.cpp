import json
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

FILE = "patients.json"

# ------------------ FILE HANDLING ------------------

def load_data():
    try:
        with open(FILE, "r") as f:
            return json.load(f)
    except FileNotFoundError:
        return {}

def save_data(data):
    with open(FILE, "w") as f:
        json.dump(data, f, indent=4)

# ------------------ PATIENT ------------------

def add_patient(data):
    pid = input("Enter Patient ID: ")

    if pid in data:
        print(" Patient ID already exists")
        return

    name = input("Enter Name: ")

    try:
        age = int(input("Enter Age: "))
    except ValueError:
        print(" Invalid age")
        return

    gender = input("Enter Gender: ")

    data[pid] = {
        "name": name,
        "age": age,
        "gender": gender,
        "vitals": []
    }

    save_data(data)
    print(" Patient added successfully")

# ------------------ VITALS ------------------

def add_vitals(data):
    pid = input("Enter Patient ID: ")

    if pid not in data:
        print(" Patient not found")
        return

    try:
        bp = int(input("Enter BP: "))
        hr = int(input("Enter Heart Rate: "))
    except ValueError:
        print(" Invalid BP or Heart Rate")
        return

    if bp > 140 and hr > 100:
        status = "High BP & High HR"
    elif bp > 140:
        status = "High BP"
    elif hr > 100:
        status = "High HR"
    else:
        status = "Normal"

    data[pid]["vitals"].append({
        "bp": bp,
        "hr": hr,
        "status": status
    })

    save_data(data)
    print(" Vitals added successfully")

# ------------------ VIEW PATIENT ------------------

def view_patient(data):
    pid = input("Enter Patient ID: ")

    if pid in data:
        print("\n===== Patient Details =====")
        print("Name:", data[pid]["name"])
        print("Age:", data[pid]["age"])
        print("Gender:", data[pid]["gender"])
        print("Vitals:", data[pid]["vitals"])
    else:
        print(" Patient not found")

# ------------------ ANALYSIS ------------------

def analyze(data):
    pid = input("Enter Patient ID: ")

    if pid not in data:
        print(" Patient not found")
        return

    vitals = data[pid]["vitals"]

    if len(vitals) == 0:
        print(" No vitals data available")
        return

    bp_list = [v["bp"] for v in vitals]
    hr_list = [v["hr"] for v in vitals]

    avg_bp = np.mean(bp_list)
    avg_hr = np.mean(hr_list)

    print("\n===== Health Analysis =====")
    print("Average BP:", avg_bp)
    print("Average Heart Rate:", avg_hr)

    df = pd.DataFrame(vitals)
    print("\nVitals Data:")
    print(df)

# ------------------ GRAPH ------------------

def plot_graph(data):
    pid = input("Enter Patient ID: ")

    if pid not in data:
        print(" Patient not found")
        return

    vitals = data[pid]["vitals"]

    if len(vitals) == 0:
        print(" No vitals data available")
        return

    bp = [v["bp"] for v in vitals]
    hr = [v["hr"] for v in vitals]

    plt.plot(bp, marker='o', label='Blood Pressure')
    plt.plot(hr, marker='s', label='Heart Rate')
    plt.title("Patient Health Trend")
    plt.xlabel("Record Number")
    plt.ylabel("Values")
    plt.legend()
    plt.grid(True)
    plt.show()

# ------------------ MAIN MENU ------------------

def main():
    data = load_data()

    while True:
        print("\n===== SHM-WAS SYSTEM =====")
        print("1. Add Patient")
        print("2. Add Vitals")
        print("3. View Patient")
        print("4. Analyze Health")
        print("5. Show Graph")
        print("6. Exit")

        try:
            choice = int(input("Enter choice: "))
        except ValueError:
            print(" Invalid choice")
            continue

        if choice == 1:
            add_patient(data)

        elif choice == 2:
            add_vitals(data)

        elif choice == 3:
            view_patient(data)

        elif choice == 4:
            analyze(data)

        elif choice == 5:
            plot_graph(data)

        elif choice == 6:
            print(" Thank you!")
            break

        else:
            print(" Invalid choice")

# ------------------ RUN ------------------

main()
