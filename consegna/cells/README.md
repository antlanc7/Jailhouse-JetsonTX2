# File di configurazione celle Jailhouse

Abbiamo configurato una nuova cella che permette l'accesso alla periferica GPIO e alla memoria condivisa.

Per utilizzarla è necessario copiare il file `jetson-tx2-gpio-inmate.c` fornito in questa cartella nel seguente percorso:

> `[JAILHOUSE_REPO_PATH]/configs/arm64`

e poi ricompilare Jailhouse con il comando 
> `sudo make`

per generare il file `jetson-tx2-gpio-inmate.cell` che sarà poi visibile agli script bash.