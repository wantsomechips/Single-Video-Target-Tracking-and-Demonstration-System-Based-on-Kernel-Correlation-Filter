# Single Video Target Tracking and Demonstration System Based on Kernel Correlation Filter

This project implements a video object tracking system based on the classic Kernelized Correlation Filter (KCF) algorithm. It includes a graphical user interface built with Qt6 and supports cross-platform deployment via Docker. The system is designed for multi-camera real-time tracking with user-friendly operation.


## Overview

KCF is a widely used tracking algorithm known for its high speed and accuracy. However, its default model update strategy is prone to contamination when the target is occluded or disappears. To improve robustness, we incorporate an **APCE-based high-confidence update strategy**, ensuring model updates only occur under reliable tracking conditions.

The system provides a complete end-to-end demonstration, including:

- Real-time multi-camera capture and display (up to 9 cameras)
- Manual target selection and tracking
- Multilingual GUI (English and Chinese)
- Containerized deployment with browser-based access


## Features

- Efficient KCF tracking with APCE-based high-confidence model updates
- Manual bounding box selection for each camera
- GUI built with Qt6, supporting:
  - Camera on/off switching
  - Target set/remove
  - Layout adjustment: 1 $\times$ 1, 2 $\times$ 2, 3 $\times$ 3 grid modes
  - Language change (English / Chinese)
- Cross-platform deployment using Docker and VNC
- Browser-accessible interface

## System Architecture

- **Tracking Module (C++ / OpenCV)**  
  Handles video capture, feature extraction, and real-time tracking using the KCF algorithm.

- **GUI Module (Qt6)**  
  Provides an interactive interface for selecting cameras, setting targets, and visualizing tracking results.

- **Deployment (Docker + VNC)**  
  Uses a pre-configured Ubuntu container (`dorowu/ubuntu-desktop-lxde-vnc:focal-arm64`) with OpenCV and Qt preinstalled. The GUI is served via VNC and accessible in any modern browser.

- **Build System (CMake)**  
  Independently builds and links the GUI and tracking modules.


## APCE-Based Model Update Strategy

To prevent model corruption during occlusions or temporary disappearance of the target, we use **Average Peak-to-Correlation Energy (APCE)** as a confidence metric. Only when the peak response and APCE values of the current frame exceed a threshold relative to historical averages will the tracker update its model.

This improves robustness and significantly reduces tracking drift in challenging conditions.



## Getting Started

### Run Locally with OpenCV and Qt installed

```bash
cd build
cmake ..
../bin/main
```

Make sure CMake 3.16, OpenCV 4.6 and Qt 6.3 are properly installed.

### Run with Docker

You can also run the program with Docker.

1. Ensure Docker and docker-compose are installed.
2. Place OpenCV 4.6 and opencv_contrib 4.6 source folders into the project root directory.
3. Build and start the container:

```bash
docker-compose up --build -d
```

3. Access the application through your browser:

```
http://localhost
```

This will launch the GUI environment using an LXDE desktop with VNC accessible through port 80. All OpenCV and Qt dependencies are prebuilt during container creation.


## Interface Preview

<h3>System Overview</h3>
<img src="./image/System Overview.png" alt="Select an obejct" width="500"/>

<h3>Manually Select an Object</h3>
<img src="./image/Select object.png" alt="Select an obejct" width="300"/>

<h3>Automatically Track an Object</h3>
<img src="./image/Tracking object.png" alt="Select an obejct" width="300"/>

<h3>VNC Overview</h3>
<img src="./image/VNC Overview.png" alt="Select an obejct" width="500"/>

<h3>Run program in VNC</h3>
<img src="./image/Run in VNC.png" alt="Select an obejct" width="500"/>




## Third-party Code Attribution

This project includes modified portions of the KCF tracking algorithm from the open-source project:

- **KCFcpp**
- URL: [https://github.com/joaofaro/KCFcpp](https://github.com/joaofaro/KCFcpp)
- License: BSD 3-Clause License
- Copyright (c) 2015, Joao Faro

Modifications were made for feature calculation and APCE-based tracker reliability assessment.


## License

This project is licensed under the **MIT License**.
See [LICENSE](./LICENSE) for details.

Third-party code from KCFcpp is licensed under the **BSD 3-Clause License**, see [LICENSE.thirdparty](./kcf/LICENSE.thirdparty) for full text.


## Author

**wantSomeChips**

Xidian University

[GitHub Profile](https://github.com/wantsomechips)