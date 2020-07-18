# Air-compressor-controller

Controller for my DIY air compressor


# Description

I made air compressor from two washing machine's motors, some tank, air pump and a few other elements. 
Those motors are universal brush motors, so i need some controller to stabilize their speed. 
This controller stabilises motors speed with PID algorithm, turns them on and off at specified pressure and have some other features:
- temperature protection
- oil change interval reminder (It measures working time and turn on LED when oil should be changed) 
- fan control 
- soft start (PID)
- overload protection



In software directory is Eclipse C++ project.
In hardware directory are board and schematic. It should be run with AutoDesk Eagle. 



# WARNING

DIY air compressors are very dangerous. 
There is high voltage in this circuit that can kill you.
High pressure tank also can be dangerous. It can explode.

I did it at my own risk for science and fun. Do not do this by yourself!
