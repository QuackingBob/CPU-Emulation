& g++ .\tests.cpp .\signals.cpp .\gates.cpp .\arithmetics.cpp .\switches.cpp .\alu.cpp .\mux.cpp .\mem.cpp .\stats.cpp .\decoder.cpp .\components.cpp .\rom.cpp .\controller.cpp -o .\tests.exe

if ($LASTEXITCODE -eq 0) {
    Write-Host "Compilation successful. Executable: .\tests.exe"
    & .\tests.exe
} else {
    Write-Host "Compilation failed."
}