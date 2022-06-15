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
if [ m ]
    then
    if [ $state = "g" ]
        then
        sed -i "8 s/.*/3.5/" input.in
    elif [ $state = "l" ]
        then
        sed -i "8 s/.*/0.20/" input.in
        
    elif [ $state = "s" ]
        then
        sed -i "8 s/.*/0.10/" input.in
                
    fi
else
    sed -i "8 s/.*/0.0005/" input.in
fi

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
rm G_r.$state.$m.out
rm G_r_fin.$state.$m.out
rm is_epot.$state.$m.out
touch "temp.$state.$m.out"
touch "ekin.$state.$m.out"
touch "epot.$state.$m.out"
touch "etot.$state.$m.out"
touch "pres.$state.$m.out"




g="y"
contr=0
while [ $g = "y" ]
do
    sed -i "3 s/.*/$contr/" input.in
    echo "[Metropolis] Vuoi eseguire l'equilibrazione? [y/n]"
    read g
    if  [ -z "$g" ] || [ $g = "y" ] || [ $g = "yes" ]
        then 
        echo "[Metropolis] Quanti passi vuoi eseguire?"
        read h

        echo "[Editing input.in]"
        sed -i "9 s/.*/$h/" input.in
        sed -i "10 s/.*/1/" input.in

        sh clean.sh
        ./NVE_NVT.exe 

            
            mv output.epot.dat eq.epot.$state.$m.out

            echo "[Coping final configuration in config.$state]"
            cp config.out config.$state
    fi
    contr=1
done

echo "Vuoi continuare la simulazione? [y/n]"
read g
if [ $g = "n" ] || [ $g = "no" ]
    then
    exit
fi

rm epot.dat;
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

    mv epot.dat is_epot.$state.$m.out
    mv output.ekin.dat ekin.$state.$m.out 
    mv output.epot.dat epot.$state.$m.out
    mv output.etot.dat etot.$state.$m.out
    mv output.pres.dat pres.$state.$m.out
    mv output.temp.dat temp.$state.$m.out
    mv G_r.dat  G_r.$state.$m.out
    mv G_r_fin.dat G_r_fin.$state.$m.out