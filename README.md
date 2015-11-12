
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

By default rake loads `project.yml` configuration file for Ceedling. You can override that by issuing `project=<yml_filename>`. E.g.,
```
rake project=./myproject.yml test:all
```
will load `myproject.yml` configuration file in the current directory and then run all tests.

Release
=======
To build hardware `release` version, type:
```
rake hw:release
```
The script for building it can be found in `scripts/hw.rb`. Edit the script if you need different compilation/linking outcome.

The command above only works if there is **exactly** one `.coproj` file in the current directory. If it has none, you need to specify the path and filename of the coproj. E.g.,
```
rake hw:release[project/Blinky.coproj]
```
Similarly, if there are many `coproj` files in the current directory, you need to specify which one `coproj` file to be used for building.

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

Since the command depends on `hw:release`, you might need to specify the `coproj` file explictly if there is conflict (refer to Release). E.g.,
```
rake hw:flash[Blinky02.coproj]
```

Flash Erase
==========
To perform full (flash) chip erase, type:
```
rake hw:full_erase
```

Loading Additional Scripts
=====================
Sometimes there is a need to load extra scripts from YAML file. There is `load_extra_scripts()` function in `helper.rb` that helps do just that. The following shows how to load the scripts from YAML file.
```
load_extra_scripts('project.yml')
```
And the YAML file should contain `:project:load_scripts` like below:
```
---
:project:
  :load_scripts: [scripts/hw.rb, scripts/host.rb]
---
```
where `scripts/hw.rb` and `scripts/host.rb` are the additional scripts to load. If `:load_scripts` does not exist, the function will just return silently.