#python yolo_detect.py --model=yolo11n_ncnn_model --source=usb0 --resolution=640x480

import os
import sys
import argparse
import glob
import time

import cv2
import numpy as np
from ultralytics import YOLO
from webcam_stream import WebcamStream


# Load the model into memory and get labemap
model = YOLO('modelopatinho_ncnn_model', task='detect')
labels = model.names

stream = WebcamStream(src= 0, width = 320, height=320, fps=30).start()
time.sleep(1)


# Set bounding box colors (using the Tableu 10 color scheme)
bbox_colors = [(164,120,87), (68,148,228), (93,97,209), (178,182,133), (88,159,106), 
              (96,202,231), (159,124,168), (169,162,241), (98,118,150), (172,176,184)]

# Initialize control and status variables
avg_frame_rate = 0
frame_rate_buffer = []
fps_avg_len = 200
img_count = 0

cont = 0
starttime = time.time()
fps = 0
frame_count = 0
object_count = 0

# Begin inference loop
while True:


    # Load frame from image source
    frame = stream.read()
    frame_count += 1
    cont += 1
    

    passou = time.time() - starttime
        
    if frame_count % 1 == 0:
        
        # Run inference on frame
        results = model(frame, verbose=False)

        # Extract results
        detections = results[0].boxes

        # Initialize variable for basic object counting example
        object_count = 0

        # Go through each detection and get bbox coords, confidence, and class
        for i in range(len(detections)):

            # Get bounding box coordinates
            # Ultralytics returns results in Tensor format, which have to be converted to a regular Python array
            xyxy_tensor = detections[i].xyxy.cpu() # Detections in Tensor format in CPU memory
            xyxy = xyxy_tensor.numpy().squeeze() # Convert tensors to Numpy array
            xmin, ymin, xmax, ymax = xyxy.astype(int) # Extract individual coordinates and convert to int

            # Get bounding box class ID and name
            classidx = int(detections[i].cls.item())
            classname = labels[classidx]

            # Get bounding box confidence
            conf = detections[i].conf.item()

            # Draw box if confidence threshold is high enough
            if conf > 0.5:

                color = bbox_colors[classidx % 10]
                cv2.rectangle(frame, (xmin,ymin), (xmax,ymax), color, 2)

                label = f'{classname}: {int(conf*100)}%'
                labelSize, baseLine = cv2.getTextSize(label, cv2.FONT_HERSHEY_SIMPLEX, 0.5, 1) # Get font size
                label_ymin = max(ymin, labelSize[1] + 10) # Make sure not to draw label too close to top of window
                cv2.rectangle(frame, (xmin, label_ymin-labelSize[1]-10), (xmin+labelSize[0], label_ymin+baseLine-10), color, cv2.FILLED) # Draw white box to put label text in
                cv2.putText(frame, label, (xmin, label_ymin-7), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 0), 1) # Draw label text

                # Basic example: count the number of objects in the image
                object_count = object_count + 1
                
                
    
    if passou >= 1.0:
        fps = cont / passou
        cont = 0
        starttime = time.time()

    # Calculate and draw framerate (if using video, USB, or Picamera source)
    cv2.putText(frame, f"FPS: {fps:.2f}", (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
        
    
        # Display detection results
    cv2.putText(frame, f'Number of objects: {object_count}', (10,40), cv2.FONT_HERSHEY_SIMPLEX, .7, (0,255,255), 2) # Draw total number of detected objects
    cv2.imshow('YOLO detection results',frame) # Display image
  
    
    if cv2.waitKey(1) & 0xFF == ord('q'): # Press 'q' to quit
        break
    


# Clean up
stream.stop()
cv2.destroyAllWindows()
