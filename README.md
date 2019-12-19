# Den Irriterende Nabo

I dette projekt har jeg lavet et program der skal simulere "Den Irriterende Nabo". Den nabo der hver december går amok med lyshow, LCD Displays og Snekanon. 


## Fysisk opsætning
 Der er blevet brugt en Atmega Dragon Microcontroller hvortil der er blevet forbundet en Keypad, LED lys, RGB lys, Servo, DC Motor, NTC Thermistor og et LCD Display.
Her kan du se et Context Diagram:
![context diagram](https://i.imgur.com/D1AMYHT.png) 


## Koden

Koden er skrevet i sproget C i programmet Atmel Studio. Projektet er blevet delt op i mapper med header filer der bliver inkluderet i main, så det giver et bedre overblik. 
Her ses et HIPO Diagram der viser programmets overordnede funktionalitet:
![HIPO Diagram](https://i.imgur.com/uFw5vwj.png)

## Funktioner 
### KeyPad
#### ColumnScan()

I funktionen ColumnScan() bliver portene en efter en skiftet til logisk 0 hver gang funktionen bliver kaldt. Der bliver returneret en int der svarer til hvilken kolonne man er nået til, og så bliver en statisk int rettet til, så vi ved hvilken kolonne vi er nået til næste gang funktionen bliver kaldt.

#### ReadRows()

I funktionen ReadRows() bliver der kørt en If-statement der tjekker om en PIN er skiftet til logisk 0, som sker ved at der kommer en kortslutning i det man trykker en knap ned, og der kommer forbindelse til en Outport Port. Efter der er blevet tjekket er der indsat et delay på 10ms inden den samme If-statement bliver kørt igen. Dette er blevet implementeret for at undgå "kontakt krel" der kan forekomme når når man trykker på en knap. Hvis If-statement er true, bliver der returneret en int der svarer til den række PIN er forbundet til.

#### DecodeKeypad(int, int)
Denne funktion bruges til at udregne hvilken knap der er blevet trykket på. Når funktionen bliver kaldt, sendes 2 ints med; en int man får fra ColumnScan() og en int man får fra ReadRows(). Disse to ints lægges sammen ved brug af formlen **a * 10 + b**. eks. er tallene 3 og 6 blevet sendt med, giver det tallet 36. Fordi vi har kolonnerne 1, 2, 3, 4 og rækkerne 5, 6, 7, 8, kan vi lave 16 mulige kombinationer, som svarer til de 16 knapper der findes på vores Keypad. Derfor er der lavet en switch case med alle 16 kombinationer, som hver især svarer til en bestemt knap. 

### LED
#### LEDPicker()
I denne funktion bliver der kørt en switch case, som tjekker en global variabel, som kan sættes ved hjælp af 4 af knapperne på Keypad'en. I hver case er der en funktion der styrer LED'erne og får dem f.eks. til at blinke, tænde, eller slukke. 

### Motor (SneKanon)
#### SneControl()
I denne funktion bliver der kørt en ADC Conversion, hvor der bliver målt på et NTC Thermistor. ADC dataen bliver så omregnet til en Celcius temperatur. Derefter bliver der kørt en if-elseif statement der tjekker om temperaturen er over eller under 30 grader (da jeg ikke kan lave minus grader med fingrene, har jeg valgt at bruge 30 grader som vendingspunkt. I et fungerende program i den virkelige verden, ville der selvfølgelig blive valgt 0 grader som vendingspunkt).
Hvis der er under 30 grader står motoren helt stille og et RGB lys viser rød. Hvis det derimod er over 30 grader, sættes hastigheden på motoren til maks, og RGB'et lyser grøn. 

### LCD
#### GlaedeligJul(), JingleBells()
I disse funktioner har jeg lavet en række strings, som bliver udskrevet til et LCD display karakter for karakter, så det giver et form for flydende flow som ser lækkert ud. Det er lavet ved at jeg laver et char array, og derefter kører det array igennem en for loop, som tjekker længden af arrayet, ved brug af strlen, og så tilskriver LCD displayet den karakter programmet er nået til.

### Servo
til servo'en er der ikke lavet nogle funktioner, da den bruger en timer, som bare skal have en OCR værdi, som bliver sat i DecodeKeypad() funktionen.

## Flowchart
Her er 2 flowcharts der viser hvordan programmet kører funktionerne igennem:
![Flowchart 1](https://i.imgur.com/51AvQzf.png)![Flowchart 2](https://i.imgur.com/7A39hgw.png)

## Diverse
Billede af opsætning på keypad: 
![Opsætning](https://i.imgur.com/E1TJ49v.jpg)

