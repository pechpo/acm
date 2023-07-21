@echo off
:loop
    random.exe
    mine.exe < data.in > mine.out
    std.exe < data.in > std.out
    fc mine.out std.out
    if not errorlevel 1 goto loop
    pause 
    goto loop