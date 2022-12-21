# How to do starting demo
- Tohle demo navazuje na tutoriál Jak spojit FreeMaster s deskou a zobrazení v Osciloscopu. Na [Discordu](https://discord.com/channels/461541385204400138/1032942392833212456/1050891266159824976) nebo na Githubu

     v tomhle demu se postupně naprogramuje fitkit, zprovozní spojení s FreeMasterem a nakonec pomocí Javascript aplikace v prohlížeči připojení na FreeMaster můžeme číst a zpisovat hodnotu přímo ve FitKitu.

## Naprogramování FITkitu
- Ve složce KDS jsou tři soubory. 
- Založ novej čistej projekt a místo obsahu main.c zkopíruj main.c ze složky (má hlavičku s autory a popisem)
- Build + Spusť DEBUG.
- appka by měla po stisku tlačítka SW6 negovat hodnotu LEDEK 9-12.
- Pokud funguje, **VYPNI Debug program v KDS**.

## Nastavení ve FreeMasteru
- New Project, přidat proměnnou **GPIOB_PDOR s adresou 0x400FF040**.
- Zobrazit v osciloscopu pro kontrolu. (podle přechozího tutoriálu, zkus si, jestli se mění hodnota v osciloscopu, když zmáčkneš tlačítko.) 
- V Nastavení proměnné NAVÍC: 
	- Záložka Modyfying -> zaškrtnout možnost "Any value within limits" (vlevo nahoře)
	- V pravo nahoře nastavit Min na 0, Max na 60.
	- Pod tím Pole "step" nastavit na 2.

## JS appka
- Ve složce "JS_app_using_JSON_RPC" je starting_demo.htm, tak zatím nic nemusíš měnit.

## Zpět do FreeMasteru
- V horní liště Project -> Options. Záložka HTML_pages. Do Control Page URL ulož adresu s cestou k starting_demo.htm.
	- (pokud se nic nezmění, tak klikni pravým na název projektu v Project Tree -> Properties -> do Description URL ulož opět starting_demo.htm) 

Pokud je vše správně, tak by se Ti měla na stránce zobrazovat aktuální hodnota GPIO_PDOR (zkus zmáčknout tlačítko, jestli se změní) a zároveň by Ti mělo jít zapsat hodnotu do pole pod tím.

## Závěr
- Snad Vám to běží, pokud ne, napiš, nebo se ptej ostatních.
- Ve složce je i FreeMaster projekt, ale ten prosím Vás **NEPOUŽÍVEJTE** to byste to měli až moc lehký a hned v dalším kroku stejně nebudete vědět jak...






