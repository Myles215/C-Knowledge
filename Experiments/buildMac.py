import subprocess
import os
import argparse

p1 = subprocess.Popen('cmake . -B Build', shell=True, stdout=subprocess.PIPE)
p1.wait()
p2 = subprocess.Popen('cmake --build build', shell=True, stdout=subprocess.PIPE)
p2.wait()

if (p2.returncode == 0):
    print("Build successful")