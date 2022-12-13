# HOW TO ověřit si, že FreeMaster komunikuje s FitKitem

## Prerekvizity
Mít na PC KDS a na FITKIT nahrát nějaký demo od Strnadela (odkaz má někdo plsss? já to mám už stažený a nevím odkud)

## Instalace FreeMasteru
https://community.nxp.com/t5/FreeMASTER-Knowledge-Base/FreeMASTER-3-0-Installation-Guide/ta-p/1101507

## Připojení desky (většinu jsem tak proklikal Next-Next, jenom pokud tam bylo víc možností, tak je to tady napsaný)
- Connection wizard (na úvodní stránce) -> Debugger interface -> Plugin_Configuration -> Test Connection -> OK -> Dokončit 
- Chcete nahrát soubor ELF nebo MAP? -> NE

## Zprovoznění osciloscopu - sleduje hodnoty na dané proměnné
1. Project Tree -> Properties -> Variable Watch -> New -> 
   * name: GPIO_PDOR, Address: 0x400FF040   (adresa GPIO na desce, kde jsou LEDKY tlačítka a tak různě)
2. Project Tree -> Create Osciloscope -> Variables -> Add Variable -> GPIO_PDOR
