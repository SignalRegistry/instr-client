RD /S /Q build
MKDIR build
CD build
cmake ..
msbuild instr-client.sln
CD ..