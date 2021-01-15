import serial
import time

data2=[]
data3=[]
data4=[]
data5=[]
data6=[]
data7=[]
data8=[]

plik=open("piosenka1.txt", "r", encoding='utf-8')


if plik.mode=="r":
    lines = plik.readlines()
    for line in lines:
        line=line[1:-2]
        data2.append(line.split(', '))


for r in range(257641):
    for c in range(12):
        if c!=0:
            data4.append(data2[r][c])

for p in range(len(data4)):
    if p%3==0:
        data5.append(data4[p])



for i in range(len(data5)):
    if i > 67000 and i <= 70000:
        data7.append(data5[i])
    if i>70000 and  i<=73000 :
        data3.append(data5[i])


print(len(data3))


zmienna6=b'\x05'
zmienna8=b'\x02'
true1=0
true2=0

with serial.Serial('COM5', 28800) as serial1:
    while serial1.isOpen():
        print('port otwarty')


        zmienna5 = serial1.read(1)
        print(zmienna5)

        if zmienna5 == zmienna6 and true1!=1:
            print('wysylanie')
            for k in range(len(data3)):
                serial1.write(str.encode(str(data3[k])))
            true=1
            print('wyslano')

        ##if zmienna5 == zmienna8:
          ##  print('wysylanie')
            ##for k1 in range(len(data7)):
              ##  serial1.write(str.encode(str(data7[k1])))
        ##print('wyslano')


