# musicfy
Shazam simulation with 2 terminals. In one terminal the user writes the melody of a song, and in the other terminal the programs check if that melody 
correspond to a song in the database.
The conexion between two terminals is made by CAN BUS.

# Example of an execution.
Open 2 terminals (it will be called "inputTerminal" and "outputTerminal").
1) On inputTerminal, execute "./inputTerminal".
2) On outputTerminal, execute "./outputTerminal".
3) On inputTerminal, write a melody (notes and duration indicates with '-'). For example:
DO-RE---MI-FA--SOL-----LA-SI-DO---
4) Observe the output terminal the message that it shows. If the input melody is contained in a song of the data base,
it will be a possible match.

# Requirements
In order to run this program, it is necessary: 
- Turn on the virtual can bus interface enabled on your computer.
- Download and compile sqlite3 library.

# Using sqlite3.
1) Download from    https://www.sqlite.org/download.htm  "amalgamation", version autoconf. It depends of the version, but the name will be similar to:
"sqlite-autoconf-3390400.tar.gz".

2) Unzip the file.

3) In the folder where the file has been unzipped, execute the following commands:
./configure; make;

4) To be able to use the library, it is necessary to make some adjustments to the CMakeLists.txt.
4.1) include_directories("path_to_folder_compiled")
4.2) link_directories("path_to_folder_compiled")
4.3) target_link_libraries(targetName sqlite3)
4.4) In the folder where the CMakeLists.txt is, execute:   cmake .; make;

# Turn up virtual can bus.
1) Install can-utils:
sudo apt-get install can-utils

2) Turn up virtual can bus:
sudo modprobe vcan
sudo ip link add dev vcan0 type vcan
sudo ip link set up vcan0

3) To check if the process has been successful, execute the command in a terminal:
candump vcan0
and in another terminal de comand:
cangen -v vcan0
