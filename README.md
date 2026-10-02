# Handwritten Character Dataset Tool and Neural Network Classifier

Final project of the Computer Vision course (3rd year, BSc in Industrial Computing and Robotics, Universitat Politècnica de València). Individual project.

## Overview

A general-purpose tool to build image datasets of handwritten characters from scanned paper templates, used to train and deploy a neural network classifier.

## How it works

1. **Template:** participants fill in a printable template with 30 boxes (160 × 320 px each, with a 14 px border to make them easy to detect).
2. **Dataset creation (C++ with OpenCV):** the program loads the scanned template in greyscale, applies inverse binary thresholding and detects the boxes with external contour detection (`findContours`). Each bounding rectangle is filtered by expected size within a tolerance, and the inner region is cropped to remove the border. Each character is shown on screen, labelled by the user and saved as a PNG in a folder per class, created automatically with `std::filesystem`.
3. **Training and deployment:** the dataset (lowercase letters, question marks and the hyphen) was split 70/15/15 and used to train a neural network on an NVIDIA Jetson Nano. The model was exported to ONNX and deployed with a Python program that classifies the camera feed in real time.

## Usage (dataset tool)

1. Open `ProyectoVision.sln` in Visual Studio (requires OpenCV).
2. Set the global variables `nombreUsuario` (name of the scanned template file) and `carpeta` (folder containing it).
3. Run the program. For each detected character, press Enter on the image window, then type the label in the terminal and press Enter.
4. One folder per character class is created next to the template.

## Technologies

C++, OpenCV, Python, NVIDIA Jetson Nano, ONNX.

## Limitations

The classifier was trained on a small dataset, so only some characters are recognised reliably. Collecting more samples is the main improvement planned.
