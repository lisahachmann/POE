README 
Lab 02: 3D IR Scanner

IR3D-arduino.ino must be run with arduino and be able to control the serial ports of the computer running it. The script controls two servos and collects data from the IR scanner. It then packages it all and sends it to Python

IR3D_python.py unpackages the information from arduino and repackages it in a way that is graphable. To run this script, you need to have Pyserial and Python's math package installed. Pyserial can be installed in multiple ways:
- in terminal linux, if you have PyPI already installed, just write 
" pip install pyserial "
or 
" easy_install -U pyserial "
- Download from the archive at https://pypi.python.org/pypi/pyserial
Unpackage the file (tar.gz) and write in linux terminal " python setup.py install " or " python3 setup.py install " if you have Python 3 versions. 

lab2circuit.png shows the electrical connections involved in this project- namely, two servos and an IR scanner, all connected to an Arduino Uno. 
