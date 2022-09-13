# Applicazioni in linguaggio Go

Abbiamo scritto tre diverse applicazioni in linguaggio Go da eseguire in linux:

- `go-led.go`: applicazione che esegue il classico toggle on off del pin GPIO J21 della TX2 nativamente da Linux (non è necessario Jailhouse attivo).

- `go-led-api`: web server con una pagina web che permette attraverso la pressione di un bottone di eseguire il toggle on off del pin GPIO J21 della TX2.

- `go_led_api_jailhouse`: web server con una pagina web che permette attraverso la pressione di un bottone di eseguire il toggle on off del valore nella cella di memoria condivisa creata da Jailhouse, da usare insieme all'inmate `gpio-comm-demo` per accendere e spegnere il pin GPIO J21.