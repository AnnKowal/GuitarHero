import serial
import time

data2=[]
data3=[]
data4=[]
data5=[]
data6=[]
data7=[]
data8=[]


plik=open("piosenka1.txt", "r")

l=0
if plik.mode=="r":
    lines = plik.readlines()
    for line in lines:
        if l!=0:
            line = line[1:-2]
            data2.append(line.split(','))
        l+=1

for r in range(943):
    for c in range(12):
        #if c!=0: #and r!=0:
            data2[r][c]=int(data2[r][c],16)
            data4.append(hex(data2[r][c]))

for c1 in range(len(data4)):
    if c1!=0:
        data5.append(data4[c1])

for i in range(len(data4)):
    if i>=0 and i<3000 :
        data3.append(data4[i])

print(len(data3))
print(data3)

zmienna6=b'8'
zmienna9=b'\x05'
zmienna8=b'\xf8'
true1=0
true2=0



for t in range(200):
    with serial.Serial('COM5', 28800) as serial2:
        print('port otwarty')
        zmienna5 = serial2.read(1)
        print(zmienna5)
        with serial.Serial('COM3', 28800) as serial1:
            zmienna11 = serial1.read(1)
            print(zmienna11)
            if zmienna5 == zmienna9 and zmienna11==zmienna6:
                print('wysylanie')
                for k in range(len(data3)):
                    serial1.write(data3[k].encode())
                print('wyslano')
                true1=1

