& g++ .\temp_tests.cpp .\signals.cpp .\gates.cpp .\arithmetics.cpp .\switches.cpp .\alu.cpp .\mux.cpp .\mem.cpp .\stats.cpp .\decoder.cpp .\components.cpp .\rom.cpp .\controller.cpp -O3 -Ofast -frename-registers -funroll-loops -o .\opt_tests.exe 

if ($LASTEXITCODE -eq 0) {
    Write-Host "Compilation successful. Executable: .\opt_tests.exe"
    & .\opt_tests.exe
} else {
    Write-Host "Compilation failed."
}

Write-Host "Profile Guided Optimization"
& g++ .\temp_tests.cpp .\signals.cpp .\gates.cpp .\arithmetics.cpp .\switches.cpp .\alu.cpp .\mux.cpp .\mem.cpp .\stats.cpp .\decoder.cpp .\components.cpp .\rom.cpp .\controller.cpp -O3 -Ofast -frename-registers -funroll-loops -fprofile-generate -o .\opt_tests.exe 
if ($LASTEXITCODE -eq 0) {
    Write-Host "Compilation successful. Profiling Executable: .\opt_tests.exe"
    & .\opt_tests.exe
} else {
    Write-Host "Compilation failed."
}

Write-Host "Compiling With Generated Profile"
& g++ .\temp_tests.cpp .\signals.cpp .\gates.cpp .\arithmetics.cpp .\switches.cpp .\alu.cpp .\mux.cpp .\mem.cpp .\stats.cpp .\decoder.cpp .\components.cpp .\rom.cpp .\controller.cpp -O3 -Ofast -frename-registers -funroll-loops -fprofile-use -o .\opt_tests.exe 
if ($LASTEXITCODE -eq 0) {
    Write-Host "Compilation successful. Profiling Executable: .\opt_tests.exe"
    & .\opt_tests.exe
} else {
    Write-Host "Compilation failed."
}