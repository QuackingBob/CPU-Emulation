# LC3 Processor Emulation

### This is our attempt to emulate the LC3 Processor in CPP from a simulated transistor circuit upwards. 

### Resources:
- [Details on registers](https://www.cs.colostate.edu/~cs270/.Fall18/resources/PattPatelAppA.pdf)
- [Details on data path](https://cs2461-2020.github.io/lectures/Datapath.pdf)
- [Further reading on data path](https://www.cs.utexas.edu/users/fussell/courses/cs310h/lectures/Lecture_10-310h.pdf)
- [Resource that helped us develop initial understanding](https://nandgame.com/)
- [LC3 ISA Download Link](https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&ved=2ahUKEwiz-cuS7rCDAxXPIUQIHabEANkQFnoECBsQAQ&url=https%3A%2F%2Fcanvas.illinois.edu%2Fcourses%2F14248%2Ffiles%2F2263411%2Fdownload%3Fdownload_frd%3D1&usg=AOvVaw1MerXtT4UchO0Fc8hMaMIu&opi=89978449)

### How to Run:

#### VSCode:
To generate tasks, run 
```bash
python generate_tasks.py
```
Then you can just run the task

#### CMake:
If using powershell, run
```bash
$ cmake_build_run.ps1
```
Alternatively, in terminal write:
```bash
$ cd "./cmake-build-debug"
$ cmake "../CMakeLists.txt"
$ cmake --build .
$ "./Debug/tests.exe"
```

#### G++
If using powershell, run
```
$ compile_tests.ps1
```
Else, run
```
$ g++ ./tests.cpp ./signals.cpp ./gates.cpp ./arithmetics.cpp ./switches.cpp ./alu.cpp ./mux.cpp ./mem.cpp ./stats.cpp ./decoder.cpp ./components.cpp -o ./tests.exe
$ ./tests.exe
```