jailhouse enable ~/linux-jailhouse-jetson/configs/arm64/jetson-tx2.cell
jailhouse cell create ~/linux-jailhouse-jetson/configs/arm64/jetson-tx2-gpio-inmate.cell
jailhouse cell load jetson-tx2-gpio-inmate ~/linux-jailhouse-jetson/inmates/demos/arm64/gpio-comm-demo.bin
jailhouse cell start jetson-tx2-gpio-inmate
