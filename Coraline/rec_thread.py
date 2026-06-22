#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  webcam_stream.py
#  
#  Copyright 2025  <coraline@raspberrypi>
#  
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#  
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#  
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
#  MA 02110-1301, USA.
#  
#  

import cv2
from threading import Thread

class WebcamStream:
    def __init__(self, src=0, width=320, height=320, fps=30):
        self.cap = cv2.VideoCapture(src, cv2.CAP_V4L2)
        self.cap.set(cv2.CAP_PROP_FRAME_WIDTH, width)
        self.cap.set(cv2.CAP_PROP_FRAME_HEIGHT, height)
        self.cap.set(cv2.CAP_PROP_FPS, fps)
        
        self.grabbed, self.frame = self.cap.read()
        self.stopped = False
        self.fps = fps
        self.width = width
        self.height = height
        
    def start(self):
        Thread(target=self.update, daemon = True).start()
        return self
        
    def update(self):
        while not self.stopped:
            self.grabbed, self.frame = self.cap.read()
            
    def read(self):
        return self.frame
        
    def stop(self):
        self.stopped = True
        self.cap.release()
