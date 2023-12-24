& cd "./cmake-build-debug/"
& cmake "../CMakeLists.txt"
& cmake --build .

if ($LASTEXITCODE -eq 0) {
    Write-Host "Compilation successful. Executable: .\tests.exe"
    & "./Debug/tests.exe"
} else {
    Write-Host "Compilation failed."
}

& cd ..