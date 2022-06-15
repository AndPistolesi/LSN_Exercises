#! /bin/bash


echo "[Compiling]"
make
echo "[Compiled]"

echo "Cancellare i .out? [y/n]"
read g
if [ -z $g ] || [ $g = "yes" ] || [ $g = "y" ]
    then
    rm *.out
fi
echo "Resettare conifg.in? [y/n]"
read g
if [ -z $g ] || [ $g = "yes" ] || [ $g = "y" ]
    then
    sed -i "1 s/.*/1./" config.in
    sed -i "2 s/.*/1./" config.in
fi


sed -i "4 s/.*/10/" input.in
sed -i "5 s/.*/100/" input.in

declare -a temp
declare -a mu

#temperatures and metropolis step radius
temp=( 32 16 8 6 4 3 2 1.5 1 0.5 0.2 0.1 0.05 0.02 0.01 )
mu=( 2.7 2.5 2 1.5 1.2 1.1 1 0.8 0.7 0.5 0.35 0.27 0.12 0.07 0.05 )

for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 
do
echo -e "\n[T=${temp[$i]}, mu=${mu[$i]}] Eseguire la simulazione? [y/n]"
read g
if [ -z $g ] || [ $g = "yes" ] || [ $g = "y" ]
    then
    
    sed -i "1 s/.*/${temp[$i]}/" input.in
    sed -i "2 s/.*/${mu[$i]}/" input.in
    sed -i "3 s/.*/${mu[$i]}/" input.in

    echo -e "\n[T=${temp[$i]}, mu=${mu[$i]}] Executing main.exe"

    ./main.exe
    #mv Parameters.out Parameters.$a.out
    cp config.out config.in
fi

done