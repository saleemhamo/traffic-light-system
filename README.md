<div align="center">
    <img src="https://github.com/saleemhamo/traffic-light-system/blob/development/docs/LOGO.png" alt="Traffic Light Control System Logo"/>
    <p>
        <i>Pioneering Traffic Management Solutions for Urban Mobility 🚦</i>
    </p>
    <div id="badges">
        <!-- Instagram Badge -->
        <a href="https://www.instagram.com/crossguard_2024"><img src="https://img.shields.io/badge/Instagram-E4405F?style=flat&logo=instagram&logoColor=white" alt="Instagram Badge"/></a>
        <!-- Latest Release Badge -->
        <a href="https://github.com/saleemhamo/traffic-light-system/releases"><img src="https://img.shields.io/github/v/release/saleemhamo/traffic-light-system?color=green&label=Latest%20Release" alt="Latest Release Badge"/></a>
        <!-- Projects Badge -->
        <a href="https://github.com/users/saleemhamo/projects/2"><img src="https://img.shields.io/badge/Project-View%20Project%20Tab-orange.svg" alt="Project Badge"/></a>
        <!-- Issues Badge -->
        <a href="https://github.com/saleemhamo/traffic-light-system/issues"><img src="https://img.shields.io/github/issues/saleemhamo/traffic-light-system.svg" alt="Issues Badge"/></a>
        <!-- Pull Requests Badge -->
        <a href="https://github.com/saleemhamo/traffic-light-system/pulls"><img src="https://img.shields.io/github/issues-pr/saleemhamo/traffic-light-system.svg" alt="Pull Requests Badge"/></a>
    </div>
</div>


# Traffic Light Control System

Welcome to the Traffic Light Control System project, an innovative solution designed to revolutionize urban traffic management across the UK. Our system intelligently optimizes traffic flow and enhances pedestrian safety using cutting-edge technology, all powered by a Raspberry Pi. By analyzing real-time traffic and pedestrian data, we dynamically adjust traffic signals to reduce waiting times and improve the overall safety of road intersections. 

## Getting Started with Installation

### Step 1: Update Your Raspberry Pi
Before installing any new software, ensure your Raspberry Pi is up-to-date with the latest system updates. This can help prevent compatibility issues and ensure the system runs smoothly.

```bash
sudo apt-get update
sudo apt-get upgrade
```

### Step 2: Install PiGPIO
PiGPIO is essential for controlling the GPIO (General Purpose Input Output) pins on the Raspberry Pi. Install it using the following commands:

```bash
wget https://github.com/joan2937/pigpio/archive/master.zip
unzip master.zip
cd pigpio-master
make
sudo make install
```

### Step 3: Install Necessary Libraries
Several libraries are required for the Traffic Light Control System to function properly, including Boost, OpenCV for image processing, and GStreamer for handling media.

- **Install Boost Libraries**:
    ```bash
    sudo apt-get install libboost-all-dev
    ```

- **Install OpenCV**:
    This library is used for processing images and videos, which is crucial for detecting vehicles and pedestrians.
    ```bash
    sudo apt-get install libopencv-dev
    ```

- **Install GStreamer**:
    GStreamer is used for handling video streams which is vital for any camera-based monitoring.
    ```bash
    sudo apt-get install gstreamer1.0-tools gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav
    ```

### Step 4: Clone and Set Up the Project
Clone the repository and prepare the software environment.

```bash
git clone https://github.com/saleemhamo/traffic-light-system.git
cd traffic-light-system
cmake .
make
sudo ./CrossGuard
```

## Project Components

This project is a blend of hardware (HW) and software (SW) components, working harmoniously to bring about a seamless traffic management experience soon to be deployed.

### **Hardware Setup**

The heart of our system lies in its carefully designed circuitry and the selection of equipment:

- **Raspberry Pi**: Acts as the central processing unit of our traffic control system.
- **Sensors**: For real-time traffic and pedestrian demand detection.
- **Signal Lights**: To visually communicate with traffic participants.

For a detailed overview of the circuit design and equipment, please refer to our [Wiki page on hardware setup](https://github.com/saleemhamo/traffic-light-system/wiki/Page-%233:-Implementation-Details#31-hardware-setup).

### **Software architecture**

Our software is developed with efficiency and scalability in mind, featuring:

- **Dynamic Signal Adjustment Algorithms**: To process data from various sensors and adjust traffic lights accordingly.
- **User-Friendly Interface**: For easy system setup and monitoring.

The complete design document can be found in our [GitHub Wiki](https://github.com/saleemhamo/traffic-light-system/wiki) under the [Design Document section](https://github.com/saleemhamo/traffic-light-system/wiki/Page-%232:-Design-Document).



---
> [!TIP]
> Stay updated with the latest developments and share your feedback with us through our [Instagram profile](https://www.instagram.com/crossguard_2024). We're excited to see how our system enhances urban traffic management for communities by dramatically improving pedestrian safety and slashing those seemingly endless waiting times at crossing!

Embrace the future of traffic control with our Traffic Light Control System, where innovation meets practicality.
