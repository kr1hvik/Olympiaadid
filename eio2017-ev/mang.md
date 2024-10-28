
Valisin suvalise paariaasta taguse aasta, et mitte lahendada uuesti samu ülesandeid. Sealt valisin eelvooru ja 40p ülesandeks osutus mang.
Sisend ja väljundfailide asemel otsustasin kasutada stdin ja stdout sest nendega oli mul kotnrollprogramm juba valmis kirjutatud.

enne kood kirjutama hakkamist:
Pärast teksit läbi lugemist sain kohe aru et tegu on graafilülesandega.
Ruutude arvu tõttu ei saaks "lolli" lahendust teha
mõtlesin et on vaja tekitada masiivid kus hoian:
1) kas ruudul olen käinud
2) millistel pean täringuviskeid kontrollima
Kindlasti on vaja funktsiooni, mis ütleb kuhu ruudule satun sest laua lõppedes läheb uuesti algusesse.

kood kirjutamise ajal:
mõtlesin kuidas hoida käidud ruute: kuna max pikkus on 1000 võin lihtsalt sellise pikkusega listi teha
tekkis mõte et mul pole vaja eraldi listi kus hoian käidud ruute, ma saan sisendlisti editida, säästan mälu ja aega.

probleem: vale vastus, peale debuggimist leidsin põhjuse movecalculatorist:
edasi liikumise ruudu arvutamiseks kasutan valemit (praegune+liidetav)%n aga kui praegune+liidetav=n siis on vastus 0, aga peaks olema n koodi jaoks. lahenduseks on if lause.
Probleem: olin unustanud needToCheck listi tühjendada pärast elemendi kontrollimist
teksti lahendused töötavad
testsisendidte abil jõudisn järeldusele et edasi liikumise valem on vigane:
kui summa on negatiivne siis mod nihkub: lahendasin sell liites modile 1 kui summa on negatiivne
ja if lausega on ka probleeme
see vähendas väljundi hälvet
lõpuks sain aru et viga tuli sellest et n algas ühest ja praegune algas 0ist 
peale selle laehendamist kood töötas veatult, kiirelt