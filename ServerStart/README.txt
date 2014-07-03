This is a proof-of-concept front-end for a Window's EQEmu server manager.

It will compile and start a basic server. ('Basic' server is defined as an
all locally-hosted process configuration with a locally-hosted login server.)

This implementation will close associated processes..but, also displays an
empty cmd window for each process... (This is to alleviate the orphaned
process issue until a fix can be found..hopefully...)

Most of this is my design..but, there are some portions borrowed from
publicly available sources. Redistribution is not authorized unless
proper ownership discovery of third-party source is accomplished.

Note: eqlaunch.exe will display self-generated messages..but, the child
'zone' process messages are lost due to the change in behavior of a
Console vs. non-Console process.
