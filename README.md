# Proactive Child Distress & Safety Detection using Edge AIoT (TinyML)

## Overview
This project presents a **privacy-preserving AIoT-based child safety system** that proactively detects early signs of **child distress, neglect, or unsafe indoor environments** using **on-device Edge AI and TinyML**.

Unlike traditional cloud-based surveillance systems, all intelligence runs **locally on low-power microcontrollers**, ensuring **low latency, scalability, and strict data privacy**. The system generates a real-time **Child Risk Index (CRI)** and alerts caregivers before harm escalates.

---

## Problem Statement
Current child monitoring and safety systems are:
- Reactive rather than preventive  
- Highly dependent on cloud infrastructure  
- Privacy-invasive (audio/video storage)  
- Fragmented across single-sensor solutions  

Early indicators such as **distress cries, inactivity, isolation, and unsafe environmental conditions** often go unnoticed until critical situations arise.

---

## Proposed Solution
An **Edge AIoT node** equipped with **multi-modal sensors** and **TinyML models** that:
- Continuously monitors child environments
- Detects distress patterns and behavioral anomalies
- Evaluates environmental safety
- Generates a **Child Risk Index (0–100)**
- Sends alerts **without storing or streaming sensitive data**

All inference happens **on the device**, making the solution ethical, scalable, and deployment-ready.

---

## Key Features
- Cry & distress sound classification (TinyML)
- Inactivity and isolation detection
- Temperature & humidity safety monitoring
- Air quality and overcrowding detection
- Child Risk Index (CRI)
- Intelligent alert generation
- Privacy-first, on-device inference
- Live dashboard visualization
- Low-power and low-cost deployment

---

## Privacy & Ethics
- No audio or video storage  
- No cloud-based inference  
- No child identity tracking  
- Only alerts and risk scores are transmitted  

**Privacy is a core design principle, not an afterthought.**

---

## Technology Stack

### Hardware (Simulated using Wokwi)
- ESP32 / Arduino Nano 33 BLE Sense
- Microphone sensor
- PIR motion sensor
- DHT11 / DHT22 (Temperature & Humidity)
- MQ-135 (Air Quality)

### AI & Software
- TinyML (TensorFlow Lite Micro)
- Edge anomaly detection
- Sensor fusion logic
- Arduino / PlatformIO
- Wokwi IoT Simulator

---

## System Architecture
Sensors → Edge AI (TinyML) → Risk Engine → Alerts / Dashboard

# All data processing is performed locally on the edge device.

---

## Process Flow
Sensor Data Collection
-->
Feature Extraction
-->
TinyML Inference
-->
Anomaly Detection
-->
Risk Score Generation (CRI)
-->
Alert / Dashboard Update

---

## Code Status
🚧 **Work in Progress**

Source code will be added incrementally:
- Sensor integration
- TinyML inference pipeline
- Risk scoring logic
- Dashboard communication

---

## 🖥️ Dashboard 

- Child Risk Index Gauge (0–100)
- Cry Type: Normal / Distress
- Motion Status: Active / Inactive
- Environment Status: Safe / Unsafe
- Alert History
- Recommended Actions

Color Coding:
- Green – Safe
- Yellow – Attention
- Red – Immediate Action

<img width="300" height="300" alt="image" src="https://github.com/user-attachments/assets/558b8cd1-8989-430a-9eee-a6eb0b3db11b" />

---

## Use Cases
- Schools and childcare centers
- Pediatric hospital wards
- Hostels and orphanages
- NGOs and child welfare departments
- Government child safety programs

---

## Future Enhancements
- Federated learning across devices
- BLE / LoRa communication
- Mobile caregiver application
- Thermal stress detection
- Government-scale analytics dashboard

---

## Hackathon Alignment
- AIoT & Edge AI
- TinyML
- Child safety & well-being
- Privacy-preserving systems
- Smart and sustainable solutions

---

