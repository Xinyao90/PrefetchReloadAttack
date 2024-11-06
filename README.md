# PrefetchReloadAttack

## Compile and Link All Files Together
Compile sender.c, receiver.c, and message.c together, so the linker knows where to find message.

```
gcc -o sender sender.c message.c util.c -lrt
gcc -o receiver receiver.c message.c util.c -lrt
```
