# Applicazioni in linguaggio C

Abbiamo scritto due diverse applicazioni in linguaggio C da compilare ed eseguire direttamente in linux:

- `gpio.c`: applicazione che esegue il classico toggle on off del pin GPIO J21 della TX2 nativamente da Linux (non è necessario Jailhouse attivo).

- `gpio-comm.c`: applicazione che va ad aggiornare automaticamente ogni secondo il valore nella cella di memoria condivisa creata da Jailhouse, da usare insieme all'inmate `gpio-comm-demo` per accendere e spegnere il pin GPIO.