This is a proof-of-concept front-end for a Window's EQEmu server manager.

It will compile and start a basic server. However, it will not close the
processes it starts, when closed. This must be done manually through the
system Task Manager. ('Basic' server is defined as an all locally-hosted
process configuration with a locally-hosted login server.)

Most of this is my design..but, there are some portions borrowed from
publicly available sources. Redistribution is not authorized unless
proper ownership discovery of third-party source is accomplished.

Note: eqlaunch.exe will display self-generated messages..but, the child
'zone' process messages are lost due to the change in behaviour of a
Console vs. non-Console process.
