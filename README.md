# Compton Effect experiment
Questa piattaforma Geant4 è stata creata come esercizio per poter apprenderne il funzionamento e approfondire le consoscienze sulla implementazione di nuove geometrie. 


![Geant4 logo](https://geant4.web.cern.ch/sites/default/files/g4logo-web.png)

Lo scopo di questa piattaforma consiste nell'implementare un esperimento per la verifica dell' **Effetto Compton** che consistette in una delle prime evidenze sperimentali della natura cospuscolare della materia.

![Equazione COmpton](https://www.mdpi.com/crystals/crystals-11-00525/article_deploy/html/images/crystals-11-00525-g001.png)

Data infatti una radiazione incidente, ad una data frequenza, attraverso calcoli di meccanica relativistica, si può dimostrare che l'energia del fotone di scattering è data dalla seguente equazione:

![Compton formula](https://h3dgamma.com/images/comptonFormula.PNG)


L'esperimento implementato nella simulazione Geant4 va quindi a simulare un apparato con una sorgente di fotoni puntiforme che spara ad una energia fissata dall'utente lungo una linea retta, un target ATTIVO costituito da uno scintillatore NaI(Tl) posto al centro. Lungo tutta la circonferenza vi sono invece dei rivelatori CdZnTe (CZT) intervallati da scudi di Piombo. Questi rivelatori hanno un preciso angolo di puntamento e sottendono un preciso angolo, settati entrambi dall'utente.