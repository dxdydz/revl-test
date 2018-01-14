
mkdir -p build
mkdir -p tools

#BUILD TOOLS/SCRIPTS
g++ -std=c++11 -I ./include/ ./src/commandline_script.cpp ./src/telemetry.cpp -o ./tools/process_csv

#Compile
g++ -std=c++11 -I ./include/ -c ./src/telemetry.cpp -o ./build/telemetry.o
