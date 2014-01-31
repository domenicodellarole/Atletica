Atletica
========

Arduino con l'atletica

I codici presenti in questa pagina, permettono di stabilire se l'atleta ha percorso la distanza desiderata,
sotto il tempo stabilito. Ci sono due versioni di programmi:

Atletica_Tempo_ECHO

Questo programma permette di calcolare il tempo che l'atleta impiega su una determinata distanza. La partenza viene
scandita attraverso un beep acustico ed un led luminoso, mentre l'arrivo viene stabilito attraverso un sensore ad 
ultrasuoni il HC-SR04. Il tempo di recupero e vari "delay" sono facilmente modificabili direttamente dal codice

Atletica_Tempo_Easy

Per questo programma, occorre soltanto un Arduino e va posto all'arrivo della corsa. Occorre premere il pulsante, per 
far attivare la procedura, che consiste in un tempo di recupero, nel quale l'atleta dovrà porsi ai blocchi di partenza
e la procedura di inizio, che sarà effettuata, attraverso una luce e un beep sonoro. 
Il LED si riaccenderà soltanto dopo che sarà passato il tempo stabilito dall'atleta, che sarà quindi in grado di stabilire 
se effettivamente la prestazione è andata bene ! 

Versione 1.0 Programma perfettamente funzionante 
Versione 1.1 //TODO Impostare i parametri da KeyPad, senza ricompilare il programma

Atletica_Tempo_RX e TX

Questo progetto necessita ancora di essere testato, sopratutto per problemi di comunicazioni tra i due dispositivi

a