# GuitarHero

Celem naszego projektu jest wykonanie gry "Guitar Hero" przy użyciu płytki rozwojowej FRDM-KL05Z. Obraz wyświetlany zostanie za pomocą wyświetlacza firmy Nokia, a dźwięk emitowany poprzez głośniczek Waveshare Analog Test Board. Gra będzie polegała na włączaniu kolejnego fragmentu melodii, jeżeli slider zostanie dotknięty w miejscu zgodnym z grafiką na wyświetlaczu.
Komunikacja mikrokontrolera z wyświetlaczem odbywa się poprzez protokół SPI. Podświetlenie ekranu realizowane jest przy pomocy sygnału PWM. Do utworzenia tablic wartości reprezentujących odpowiednie grafiki użyto najpierw konwertera online obrazka na bitmapę, a następnie programu LCD Assistant, aby zamienić utworzoną bitmapę na tablicę wartości.
Dźwięk jest zbiorem 8-bitowych próbek PCM. Plik MP3 jest przetwarzany do pliku RAW za pomocą programu 
Audacity a następnie w programie HxD generowany jest na jego podstawie plik C, który zawiera próbki utworu. Kolejno wykonywany jest resampling za pomocą programu napisanego w języku Python.
