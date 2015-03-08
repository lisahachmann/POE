"""streaming test: not sure if the arduino serial monitor is safely outputting to python"""
import serial
import math
ser = serial.Serial('/dev/ttyACM0', 9600)

bol = True
raw = []
data = []
distx = []
disty = []
distz = []
x = []
y = []
z = []
calib = []
deltasin = []
deltacos = []
alphasin = []
alphacos = []
pos = []
tiltpos = []
x = []

while bol:
        #read from the serial line
        raw.append(ser.readline())
        #take this many data points and then end
        if len(raw) == 500:
            bol = False

try:
    #Unpackaging the serial line, without any of the arduino errors
    data = (map(str.strip, raw))
    for i in range(len(data)):
        current = data[i]
        if len(current) >= 7 and len(current) <=11:
            USA = current.split(',')
            for i in range(0, len(USA), 4):
                if len(USA) != 4:
                    pass
                else:
                    pos.append(USA[0])
                    tiltpos.append(USA[1])
                    x.append(USA[2])

    for j in range(len(x)):
        #convert ir sensor readings into actual/calibrated distances
        xdata = float(x[j])
        calib.append(288.6 - (2.5*xdata) + ((0.0112)*(xdata**2)) - ((0.0000271)*(xdata**3)) + ((0.0000000335)*(xdata**4)) - ((0.0000000000167)*(xdata**5)))
    print calib[j]

    for k in range(len(pos)):
        #convert from spherical input data to cartesian coordinates
        alphadeg = float(tiltpos[k])
        if alphadeg < 0 : 
            alphadeg=  abs(alphadeg)
        alpharad = alphadeg * (math.pi/180)
        deltadeg = (float(pos[k]))  + 30
        deltarad = deltadeg* (math.pi/180)
        deltasin.append(math.sin(deltarad))
        if deltadeg <90:
            deltacos.append(math.cos(deltarad))
        elif deltadeg <=90:
            deltacos.append(math.cos(deltarad - (90*math.pi/180)))
        alphasin.append(math.sin(alpharad))
        alphacos.append(math.cos(alpharad))
        print len(calib)
        print len((deltacos))
        print len(deltasin)
        print len(alphacos)
        print len(alphasin)
    for m in range(len(calib)):    
        if len(deltasin) == len(calib) and len(deltasin) == len(alphasin) :
            #using the spherical to cartesian conversions of 
            #x=r*sin(theta)*cos(phi)
            #y=r*sin(theta)*sin(phi)
            #z=r*cos(theta) #Added initial height as well
            distx.append(calib[m]* deltasin[m] * alphacos[m])
            disty.append(calib[m] * alphasin[m] * deltasin[m])
            #disty.append(deltacos[m] * calib[m] +10.2)
            #distz.append((calib[m]*deltacos[m]) + 10.2)
    #output so data can be manually entered into the next plotting script
    print distx
    print disty
    print distz

#Arduino sometimes has broken serial lines that include '\letters', so to ignore those:
except data == '' or "\"" in data:
        pass       