
Overview
========
I use this simple blinky project to show how `cbuild` script can be used to facilitate building process and flashing the built program into the target board (**STM32F429-Discovery**).

The `Drivers/` folder contains only the necessary STM32Fxx and CMSIS drivers to keep the size to the minimal. The `scripts/` folder contains `cbuild` and other scripts.

Commands
========
To view all available commands issue:
```
rake -T
```
The new commands added by `scripts/hw.rb` are:
```
rake hw:flash
rake hw:release
```

Release
=======
To build hardware `release` version, type:
```
rake hw:release
```
The script for building it can be found in `scripts/hw.rb`. Edit the script if you need different compilation/linking outcome. 

Flash
=====
To flash hardware `release` version, type:
```
rake hw:release
```
This command might trigger a re-build if some of the source code is modified. This command relies on `ST-LINK_CLI.exe` program. The program can be obtained from [here](http://www.st.com/web/en/catalog/tools/PF258168). You need to include the path to that program into the system path, so that the build system is able to invoke it. 
