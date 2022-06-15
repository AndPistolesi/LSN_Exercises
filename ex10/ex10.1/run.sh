
echo "[Compiling]"
make
echo "[Compiled]"

rm *.out
mpiexec -np $1 ./main.exe