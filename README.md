# iBeacon Building Locator App

Welcome to the iBeacon Building Locator App repository! This repository contains the code and resources necessary to create an app that detects iBeacons and identifies the building you are in based on the detected iBeacon signals.

## Overview

This project utilizes the MIT App Inventor platform to create a mobile application that interfaces with an ESP32 device acting as an iBeacon. When the iBeacon signal is detected by the app, it provides a sound notification indicating the building you are currently in.

## Features

- Detects iBeacons to determine the building location.
- Provides sound notification with the building information.
- Utilizes MIT App Inventor for app development.
- Compatible with ESP32 devices acting as iBeacons.

## Repository Contents

- **ESP32 Code:** Contains the code to be uploaded to an ESP32 device to configure it as an iBeacon.
- **App AIA File:** The AIA file, exported from the MIT App Inventor, containing the project configuration.
- **APK File:** APK file for installing the iBeacon Building Locator App on your Android device.
- **Extension Dependency:** Dependency extension required for the proper functioning of the app. (Link to the extension provided below)

## Installation and Usage

1. Upload the provided ESP32 code to your ESP32 device to configure it as an iBeacon.
2. Import the AIA file into the MIT App Inventor platform.
3. Compile and build the app project in the MIT App Inventor.
4. Install the generated APK file on your Android device.
5. Upon launching the app, ensure to grant location permissions manually to enable iBeacon detection, Unless your android version is below less than 10
6. Once permissions are granted, the app will start detecting iBeacons in the vicinity, providing building location notifications.

## Extension Dependency

Our project depends on a specific extension for proper functionality. Please download and install the following extension:
- [BLEIbeacon](https://drive.google.com/file/d/1AOTuc9uNSfs_GRZ9y9UW73SCkKqPHvSY/view?usp=sharing)

## Contributing

Contributions to this project are welcome! Feel free to submit issues, feature requests, or pull requests to help improve the iBeacon Building Locator App.

## License

This project is licensed under the MIT License. Feel free to modify and distribute the code for your own purposes.

## Acknowledgments

Special thanks to the developers of MIT App Inventor and the contributors to the ESP32 platform for their valuable tools and resources.

---

Thank you for exploring our iBeacon Building Locator App repository! If you have any questions or feedback, please don't hesitate to contact us. Happy building locating!
