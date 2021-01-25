import serial

data2=[]
data3=[]
data4=[]
data7=[]


plik=open("piosenka.txt", "r") #otwarcie pliku z probkami piosenki do odczytu

if plik.mode=="r": #odczyt z pliku i zapis rozdzielonych wartosci do tablicy
    lines = plik.readlines()
    for line in lines:
            line = line[1:-2]
            data2.append(line.split(','))

print(len(data2))
for r in range(246000): 
    for c in range(12):
            data2[r][c]=int(data2[r][c],16) 
            data4.append(hex(data2[r][c]))


zmienna6=b'\x05'
true1=0
true2=0
z1=0
z2=12000

with serial.Serial('COM3', 921600) as serial1: #otwarcie portu szeregowego z zadana predkoscia transmisji
    while serial1.isOpen(): #dopoki port szeregowy jest otwarty
        data3.clear() #wyzyszczenie tablic z probkami
        data7.clear()
        print('port otwarty')
        
        for i in range(len(data4)):
            if i%4==0: #downsapling, zmiana z czestotliwosci probkowania 8kHz na 2kHz
                if i >= z1 and len(data3)<3000:
                    data3.append(data4[i]) #wpisanie nowych, kolejnych probek do tablicy
                elif i >= z2 and len(data7)<3000:
                    data7.append(data4[i]) #wpisanie nowych, kolejnych probek do tablicy
                    
        if true1!=1: #jezeli w twj iteracji petli nie przeslano zawartosci tablicy data3
            zmienna5 = serial1.read(1)

            if zmienna5 == zmienna6: #jezeli mikroprocesor przeslal zmienna tozsama z checia przyjecia probek dzwieku
                print('wysylanie')
                for k in range(len(data3)):
                    serial1.write(data3[k].encode()) #wysylanie danych w petli do mikroprocesora
                    zmienna11=serial1.read(1) #odczyt danych od mikroprocesora
              
                true2=1  
                true1=1
        
        if true2==1: #jezeli w tej iteracji petli nie przeslano zawartosci tablicy data7
            zmienna7 = serial1.read(1) #odczyt danych od mikroprocesora
            print(zmienna7)

            if zmienna7 == zmienna6:  #jezeli mikroprocesor przeslal zmienna tozsama z checia przyjecia probek dzwieku
                for t in range(len(data7)): 
                    serial1.write(data7[t].encode()) #wysylanie danych w petli do mikroprocesora
                    zmienna9=serial1.read(1) #odczyt danych od mikroprocesora
                
                true1 = 0
                true2 = 0
                z1 += 24000 #zwiekszenie zmiennych ktore definiuja poczatek numer elementu, ktory w kolejnej iteracji petli bedzie wysylany przez UART jako pierwszy
                z2 += 24000
 
