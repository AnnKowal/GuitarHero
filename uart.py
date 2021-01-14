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
    data=plik.read()

data1=data.split(',')

wartosc=30000

for i in range(len(data1)):
    if i>=30000 and i<33000 :
        data3.append(data1[i])

print(data3)
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
                for k in range(3000):
                    time.sleep(0.1)
                    serial1.write(str.encode(str(data3[k])))
                print('wyslano')

        if true1==1:
            zmienna7 = serial1.read(1)
            print(zmienna7)

            if zmienna7 == zmienna8:
                time.sleep(0.1)
                true2=1
                for t in range(3000):
                    zmienna9=serial1.read(1)
                    print(zmienna9)
                print('odebrano')
