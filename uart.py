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
        data2.append(line.split(','))


for r in range(257641):
    for c in range(12):
        if c!=0 and r!=0:
            data4.append(data2[r][c])
#for c1 in range(len(data4)):
 #   if c1!=0:
  #      data5.append(data4[c1])

wartosc=30000

for i in range(len(data4)):
    if i>=30000 and i<30100 :
        data3.append(data4[i])
        print(data4[i])



zmienna6=b'\x05'
zmienna8=b'\x01'
true1=0
true2=0

with serial.Serial('COM5', 28800) as serial1:
    while serial1.isOpen():
        print('port otwarty')

        if true1!=1:
            zmienna5 = serial1.read(1)
            print(zmienna5)

            if zmienna5 == zmienna6:
                true1=1
                print('wysylanie')
                for k in range(len(data3)):
                    time.sleep(0.001)
                    serial1.write(str.encode(str(data3[k])))
                    time.sleep(0.001)
                    zmienna11=serial1.read(1)
                    print(zmienna11)
                print('wyslano')

        if true1==1:
            zmienna7 = serial1.read(1)
            print(zmienna7)

