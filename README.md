# lpwan-device

# Introduction

# Configuration

# Commands

## Shell help
$ help
?            display help on given or available commands
<TAB>        auto-completion
<cr>         execute command line
CTRL-P       recall previous input line
CTRL-N       recall next input line
<any>        treat as input character

## Commands help
$ ?
help   display help
mem    show free memory
print  print settings
send   send a packet
txp    set the tx power
txsf   set the tx spreading factor
txbw   set the tx bandwidth
txf    set the tx frequency
txiq   Invert radio I/Q
recv   recv a packet
rxsf   set the tx spreading factor
rxbw   set the tx bandwidth
rxf    set the tx frequency
rxto   set the rx timeout ms
rxiq   Invert radio I/Q
sleep  sleep for a set number of milliseconds


# Peer to Peer

Using the same frequency, spreading factor and bandwidth settings on both sides will allow peer to peer communication.

# LoRa Gateway Connectivity

With Invert IQ disabled a LoRa gateway will be able to receive packets from the device.
LoRaWAN will enable Invert IQ for downlinks. CRC will expect to be enabled on only uplink packets.

# References

https://github.com/MultiTechSystems/mbed-os-lorawan-tinyshell

https://github.com/ARMmbed/mbed-semtech-lora-rf-drivers/

https://os.mbed.com/users/murilopontes/code/tinyshell

https://os.mbed.com/teams/MultiTech/code/flash-fs/

https://github.com/pellepl/spiffs

https://developer.mbed.org/teams/MultiTech/code/SpiFlash25

