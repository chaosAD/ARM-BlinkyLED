
Overview
========
I use this simple blinky project to show how `cbuild` script can be used to facilitate building process and flashing the built program into the target board (**STM32F429-Discovery**) using `rake`. The script extracts all necessary file names to build the project from CoIDE's project file (in this case `Blinky.coproj`). This means you can update (adding or deleting filenames) your project in CoIDE and the script will build using the latest update automatically.

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
rake hw:flash
```
This command might trigger a re-build if some of the source code is modified. This command relies on `ST-LINK_CLI.exe` program by default. The program can be obtained from [here](http://www.st.com/web/en/catalog/tools/PF258168). You need to include the path to that program into the system path, so that the build system is able to invoke it.

To specify a different name of or specific path to flash-programmer, you can pass it in through rake command:
```
rake hw:flash flasher=/c/STM/stlink/ST_FLASHER
```

GCC compiles and links C/C++ files to ELF executable. Unfortunately, `ST-LINK_CLI` lacks the ability to read such file, but only HEX or BIN file. The good news is, the translation can be done by `arm-none-eabi-objcopy`. The `rake hw:flash` command automatically performs this and assumes that the program is in the Bash path. If the name or the path needs to be specified, you can issue:
```
rake hw:flash elf_to_hex="/e/ProgramFiles/GNU Tools ARM Embedded/4.9 2015q1/bin/arm-none-eabi-objcopy"
```