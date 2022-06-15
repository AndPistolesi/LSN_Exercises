#!/bin/bash

echo "[Compiling]"
make
echo "[Compiled]"


echo "s, l, g"
read state

echo "[copying input.$state in input.in]"
cp input.$state input.in

echo "Inserire 1 per Metropolis e 0 per Verlet"
read m

sed -i "1 s/.*/$state/" input.in
sed -i "2 s/.*/$m/" input.in

echo "Configurazione iniziale da config."
read init
cp config.$init config.in 

echo "Updating files.$state.$m.out"

rm "ekin.$state.$m.out"
rm "epot.$state.$m.out"
rm "etot.$state.$m.out"
rm "pres.$state.$m.out"
rm "temp.$state.$m.out"
rm "G_r.$state.$m.out"
rm "G_r_fin.$state.$m.out"


echo "Inserire la temperatura"
read temp
sed -i "4 s/.*/$temp/" input.in


g="y"
contr=0
while [ $g = "y" ]
do
    sed -i "3 s/.*/$contr/" input.in
    echo "[T=$temp] Vuoi eseguire l'equilibrazione? [y/n]"
    read g
    if  [ -z "$g" ] || [ $g = "y" ] || [ $g = "yes" ]
        then 
        echo "[T=$temp] Quanti passi vuoi eseguire?"
        read h

        echo "[Editing input.in]"
        sed -i "9 s/.*/$h/" input.in
        sed -i "10 s/.*/1/" input.in

        ./NVE_NVT.exe 

            rm eq.temp.$state.$m.out
            cat "output.temp.dat" >> eq.temp.$state.$m.out

            echo "[Coping final configuration in config.$state]"
            cp config.out config.$state
    fi
    contr=1
done

echo "Vuoi continuare la simulazione? [y/n]"
read g
if [ $g == "n" ] || [ $g == "no"]
    then
    exit
    fi


echo "[INIZIO SIMULAZIONE]"
echo "[Editing input.in]"
echo "[Cleaning]"

    sh clean.sh
    echo "[$state]Inserire il numero di passi"
    read passi
    echo "[$state]Inserire il numero di blocchi"
    read blocchi
    sed -i "3 s/.*/1/" input.in

    if [ -z $passi ] || [ -z $blocchi ]
        then
        sed -i "9 s/.*/20/" input.in
        sed -i "10 s/.*/2000/" input.in
    else
        sed -i "9 s/.*/$blocchi/" input.in
        sed -i "10 s/.*/$passi/" input.in
    fi

./NVE_NVT.exe 

            
    mv output.ekin.dat ekin.$state.$m.out 
    mv output.epot.dat epot.$state.$m.out
    mv output.etot.dat etot.$state.$m.out
    mv output.pres.dat pres.$state.$m.out
    mv output.temp.dat temp.$state.$m.out
    mv G_r.dat G_r.$state.$m.out
    mv G_r_fin.dat G_r_fin.$state.$m.out
    mv seed.out seed.$state.$m.out