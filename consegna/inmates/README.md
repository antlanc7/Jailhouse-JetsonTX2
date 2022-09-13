# Applicazioni inmate per la cella bare-metal

Abbiamo scritto due diversi inmate, entrambi per la cella da noi configurata e fornita:

- `gpio-demo.c`: inmate che esegue il classico toggle on off del pin GPIO J21 della TX2, non sfrutta la comunicazione tra celle.
- `gpio-comm-demo.c`: inmate che sfruttando la comunicazione tra celle legge un valore in una cella di memoria condivisa e lo usa come valore per il pin GPIO.
Questo inmate richiede un'app sulla cella Linux che vada ad aggiornare il valore della cella di memoria condivisa.

Per utilizzarli è necessario copiare i file `jetson-tx2-gpio-inmate.c` forniti in questa cartella nel seguente percorso:

> `[JAILHOUSE_REPO_PATH]/inmates/demos/arm`

In seguito bisogna modificare i makefile delle cartelle `arm` e `arm64` come quelli forniti da noi, e poi ricompilare Jailhouse con il comando 
> `sudo make`

Verranno generati i rispettivi file `.bin` nella cartella `arm64` che saranno poi visibili agli script bash.