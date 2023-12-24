& cd "./cmake-build-debug/"
& cmake "../CMakeLists.txt"
& cmake --bulid
& cd ..

if ($LASTEXITCODE -eq 0) {
    Write-Host "Compilation successful. Executable: .\tests.cpp.o"
    & "./CMakeFiles/tests.dir/tests.cpp.o"
} else {
    Write-Host "Compilation failed."
}