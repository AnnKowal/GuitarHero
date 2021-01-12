import serial

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
    if i>=30000 and i<31000 :
        data3.append(data1[i])

with serial.Serial('COM5', 28800) as serial1:
    if serial1.isOpen():
        print('port otwarty')
       # for c in range(2000000):

        zmienna5 = serial1.read(1)
        print(zmienna5)
        #serial1.write(str.encode(str(hh)))
        #zmienna5 = serial1.read(2)
        #print(zmienna5)

        for k in range(1000):
            serial1.write(str.encode(str(data3[k])))

        zmienna6 = serial1.read(1)
        print(zmienna6)

        zmienna7 = serial1.read(1)
        print(zmienna7)

        zmienna8 = serial1.read(1)
        print(zmienna8)
