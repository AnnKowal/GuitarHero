data1=[]
data2=[]

plik=open("piosenka.txt", "r")

plik2=open("samples2.txt", "w").close()
plik3=open("samples3.txt", "w").close()
plik4=open("samples4.txt", "w").close()
plik5=open("samples5.txt", "w").close()
plik6=open("samples6.txt", "w").close()
plik7=open("samples7.txt", "w").close()

plik2=open("samples2.txt", "a")
plik3=open("samples3.txt", "a")
plik4=open("samples4.txt", "a")
plik5=open("samples5.txt", "a")
plik6=open("samples6.txt", "a")
plik7=open("samples7.txt", "a")


if plik.mode=="r":
    data=plik.read()

data1=data.split(',')
wartosc=30000

for k in range(len(data1)): #podprobkowanie
    if(k%6==0):
        data2.append(data1[k])

for i in range(len(data2)):
    if i>=wartosc and i<wartosc+5000:
        zmienna = data2[i] + ', '
        plik2.write(zmienna)
    elif i>=wartosc+5000 and i<10000+wartosc:
        zmienna = data2[i] + ', '
        plik3.write(zmienna)
    elif i>=10000+wartosc and i<15000+wartosc:
        zmienna = data2[i] + ', '
        plik4.write(zmienna)
    elif i>=15000+wartosc and i<20000+wartosc:
        zmienna = data2[i] + ', '
        plik5.write(zmienna)
    elif i>=20000+wartosc and i<25000+wartosc:
        zmienna = data2[i] + ', '
        plik6.write(zmienna)
    elif i>=25000+wartosc and i<2*wartosc:
        zmienna = data2[i] + ', '
        plik7.write(zmienna)

