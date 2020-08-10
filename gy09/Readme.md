- jelzés:
    ha több cél küld jelzést a szülőnek:
    ha még az első jelzést nem dolgoztuk fel, akkor a másodikat eldobja a rendszer.
    - megoldás: 
        - két különböző típusú jelzés használata
        - valós idejű jelzés
    pause() vár a jelzésre, ütemezés közbe szólhat, mikor mi érkezik meg, lehet, hogy pause előtt már megérkezett a jelzés
    - megoldás:
        - while signal arrived, handlerben ezt változtatni.
    ki küldi kinek a jelzést, ha gyerek küld, akkor a szülő biztos létezik.
    ha a szülő küld üzenetet a gyerek programnak, akkor számolni kell a lehetőséggel, hogy a gyerek még nem futott le, a jelzés feldolgozásig se
    pid-et érdemes küldeni, plussz adat legyen adatstruktúra, és legyen ott létrehozva, ahol mindenki látja
- pipe:
    általában kell kettesért, nevesítetlen csővezetéknél olvasó vég ha nincs nyitva a rendszer lehet lezárja idő előtt.
    ha nincs író fej nyitva, olvasó fej várakozás megszünhet.
    nevesítettnél, töröljünk a program elején unlink-kel, hogy ne legyen belőle probléma.
    jelzéssel figyeljük, vagy több csővezetéket használjunk oda vissza kommunikációnál.
    system5: meg lehet címezni, hogy kinek szóljon az üzenet, szinkronizáció adott
        beragadó üzenetek törlésére kell figyelni 
        ipcs cmd paranccsal lehet megnézni milyen beragadt üzenetek vannak
        ipcrm cmd paranccsal lehet törölni
    POSIX bonyibb, de ez a szabvány, ekkor kell kapcsoló a fordításhoz -lrt
    csak akkor küld üzenetet, ha az üzenet sorom üres volt, nem kapok jelzést róla.