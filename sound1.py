data1=[]
data2=[]
data3=[]

plik=open("piosenka.txt", "r")
plik1=open("samples1.txt", "w").close()
plik2=open("samples2.txt", "w").close()
plik3=open("samples3.txt", "w").close()
plik4=open("samples4.txt", "w").close()
plik5=open("samples5.txt", "w").close()
plik6=open("samples6.txt", "w").close()
plik7=open("samples7.txt", "w").close()
plik8=open("samples8.txt", "w").close()
plik9=open("samples9.txt", "w").close()
plik10=open("samples10.txt", "w").close()
plik11=open("samples11.txt", "w").close()
plik12=open("samples12.txt", "w").close()
plik13=open("samples13.txt", "w").close()
plik14=open("samples14.txt", "w").close()
plik15=open("samples15.txt", "w").close()
plik16=open("samples16.txt", "w").close()
plik17=open("samples17.txt", "w").close()
plik18=open("samples18.txt", "w").close()
plik19=open("samples19.txt", "w").close()
plik20=open("samples20.txt", "w").close()
plik21=open("samples21.txt", "w").close()
plik22=open("samples22.txt", "w").close()
plik23=open("samples23.txt", "w").close()
plik24=open("samples24.txt", "w").close()
plik25=open("samples25.txt", "w").close()
plik26=open("samples26.txt", "w").close()
plik27=open("samples27.txt", "w").close()
plik28=open("samples28.txt", "w").close()
plik29=open("samples29.txt", "w").close()
plik30=open("samples30.txt", "w").close()

plik1=open("samples1.txt", "a")
plik2=open("samples2.txt", "a")
plik3=open("samples3.txt", "a")
plik4=open("samples4.txt", "a")
plik5=open("samples5.txt", "a")
plik6=open("samples6.txt", "a")
plik7=open("samples7.txt", "a")
plik8=open("samples8.txt", "a")
plik9=open("samples9.txt", "a")
plik10=open("samples10.txt", "a")
plik11=open("samples11.txt", "a")
plik12=open("samples12.txt", "a")
plik13=open("samples13.txt", "a")
plik14=open("samples14.txt", "a")
plik15=open("samples15.txt", "a")
plik16=open("samples16.txt", "a")
plik17=open("samples17.txt", "a")
plik18=open("samples18.txt", "a")
plik19=open("samples19.txt", "a")
plik20=open("samples20.txt", "a")
plik21=open("samples21.txt", "a")
plik22=open("samples22.txt", "a")
plik23=open("samples23.txt", "a")
plik24=open("samples24.txt", "a")
plik25=open("samples25.txt", "a")
plik26=open("samples26.txt", "a")
plik27=open("samples27.txt", "a")
plik28=open("samples28.txt", "a")
plik29=open("samples29.txt", "a")
plik30=open("samples30.txt", "a")

if plik.mode=="r":
    data=plik.read()

data1=data.split(',')
wartosc=50000

for k in range(len(data1)): #podprobkowanie z 8000Hz na 40000Hz
    if(k%2==0):
        data2.append(data1[k])

for i in range(len(data2)):
    if i<wartosc:
        zmienna = data2[i] + ', '
        plik1.write(zmienna)
    elif i>=wartosc and i<2*wartosc:
        zmienna = data2[i] + ', '
        plik2.write(zmienna)
    elif i>=2*wartosc and i<3*wartosc:
        zmienna = data2[i] + ', '
        plik3.write(zmienna)
    elif i>=3*wartosc and i<4*wartosc:
        zmienna = data2[i] + ', '
        plik4.write(zmienna)
    elif i>=4*wartosc and i<5*wartosc:
        zmienna = data2[i] + ', '
        plik5.write(zmienna)
    elif i>=5*wartosc and i<6*wartosc:
        zmienna = data2[i] + ', '
        plik6.write(zmienna)
    elif i>=6*wartosc and i<7*wartosc:
        zmienna = data2[i] + ', '
        plik7.write(zmienna)
    elif i>=7*wartosc and i<8*wartosc:
        zmienna = data2[i] + ', '
        plik8.write(zmienna)
    elif i>=8*wartosc and i<9*wartosc:
        zmienna = data2[i] + ', '
        plik9.write(zmienna)
    elif i>=9*wartosc and i<10*wartosc:
        zmienna = data2[i] + ', '
        plik10.write(zmienna)
    elif i>=10*wartosc and i<11*wartosc:
        zmienna = data2[i] + ', '
        plik11.write(zmienna)
    elif i>=11*wartosc and i<12*wartosc:
        zmienna = data2[i] + ', '
        plik12.write(zmienna)
    elif i>=12*wartosc and i<13*wartosc:
        zmienna = data2[i] + ', '
        plik13.write(zmienna)
    elif i>=13*wartosc and i<14*wartosc:
        zmienna = data2[i] + ', '
        plik14.write(zmienna)
    elif i>=14*wartosc and i<15*wartosc:
        zmienna = data2[i] + ', '
        plik15.write(zmienna)
    elif i>=15*wartosc and i<16*wartosc:
        zmienna = data2[i] + ', '
        plik16.write(zmienna)
    elif i>=16*wartosc and i<17*wartosc:
        zmienna = data2[i] + ', '
        plik17.write(zmienna)
    elif i>=17*wartosc and i<18*wartosc:
        zmienna = data2[i] + ', '
        plik18.write(zmienna)
    elif i>=18*wartosc and i<19*wartosc:
        zmienna = data2[i] + ', '
        plik19.write(zmienna)
    elif i>=19*wartosc and i<20*wartosc:
        zmienna = data2[i] + ', '
        plik20.write(zmienna)
    elif i>=20*wartosc and i<21*wartosc:
        zmienna = data2[i] + ', '
        plik21.write(zmienna)
    elif i>=21*wartosc and i<22*wartosc:
        zmienna = data2[i] + ', '
        plik22.write(zmienna)
    elif i>=22*wartosc and i<23*wartosc:
        zmienna = data2[i] + ', '
        plik23.write(zmienna)
    elif i>=23*wartosc and i<24*wartosc:
        zmienna = data2[i] + ', '
        plik24.write(zmienna)
    elif i>=24*wartosc and i<25*wartosc:
        zmienna = data2[i] + ', '
        plik25.write(zmienna)
    elif i>=25*wartosc and i<26*wartosc:
        zmienna = data2[i] + ', '
        plik26.write(zmienna)
    elif i>=26*wartosc and i<27*wartosc:
        zmienna = data2[i] + ', '
        plik27.write(zmienna)
    elif i>=27*wartosc and i<28*wartosc:
        zmienna = data2[i] + ', '
        plik28.write(zmienna)
    elif i>=28*wartosc and i<29*wartosc:
        zmienna = data2[i] + ', '
        plik29.write(zmienna)
    elif i>=29*wartosc:
        zmienna = data2[i] + ', '
        data3.append(zmienna)
        plik30.write(zmienna)

print(len(data3))
