@echo off

if exist build (
    rmdir /s /q build
)

if exist GlCraft.exe (
    del /q forge.exe
)
