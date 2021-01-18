import serial
import time

data2=[]
data3=[]
data4=[]
data5=[]
data6=[]
data7=[]
data8=[]


plik=open("piosenka.txt", "r")

if plik.mode=="r":
    lines = plik.readlines()
    for line in lines:
            line = line[1:-2]
            data2.append(line.split(','))


for r in range(943):
    for c in range(12):
            data2[r][c]=int(data2[r][c],16)
            data4.append(hex(data2[r][c]))


wartosc=30000

for i in range(len(data4)):
 #  if i>=0 and i<3000 :
        data3.append(data4[i])


print(data3)
zmienna6=b'\x05'
zmienna8=b'\x01'
true1=0
true2=0

with serial.Serial('COM3', 28800) as serial1:
    while serial1.isOpen():
        print('port otwarty')

        if true1!=1:
            zmienna5 = serial1.read(1)

            if zmienna5 == zmienna6:
                print('wysylanie')
                for k in range(len(data3)):
                    time.sleep(0.01)
                    serial1.write(data3[k].encode())
                    time.sleep(0.01)
                    zmienna11=serial1.read(1)
                    print (zmienna11.hex())
                print('wyslano')

        if true1==1:
            zmienna7 = serial1.read(1)
            print(zmienna7)

            if zmienna7 == zmienna8:
                time.sleep(0.1)
                true2=1
                if true2!=1:
                    for t in range(3000):
                        zmienna9=serial1.read(1)
                    print('odebrano')