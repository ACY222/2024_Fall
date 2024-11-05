# GDB Tutorial

## Enter gdb mode

gcc -g <source file> -o <output file>      enable built-in debugging support
gdb -q <file>              load a file to debug

## Debug with gdb

help [command]          get help
l                       list the code, 10 lines by default
l <num>                 list 10 lines of code around the target line
l <function>            list the function code

### Running

* r                     run the program
* c                     continue until breakpoint
* s                     step
* n                     next, view function-call as an single instruction
* finish                runs until current function finished
* until <line>          run to the target line
* tips: when ENTER, gdb will repeat the same command you just give it.

### Breakpoint

b <line>                set a breakpoint at the target line
b <line> <condition>    breaks when the condition is true
b <function>            set a breakpoint at a particular function
info b                  show information about all declared breakpoints
d <breakpoint>          delete breakpoint with target number
clear <line>            delete breakpoint in target line
disable <breakpoint>    disable a breakpoint
enable <breakpoint>     enable a breakpoint
d breakpoints           delete all breakpoints, watchpoints, tracepoints

### Monitoring

disp <var>              print the value of variable every time
print <var>             print the value of variable
whatis <var>            print the type of variable
watch <var>             stops whenever the watched variable is modified

### Split windows

layout                  split the windows, navigate different parts of code
layout  src             split the windows and show source code 

### Quit from gdb

q                 quit from gdb
