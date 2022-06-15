#!/bin/bash



echo "Vuoi eseguire clean.sh?"
read  g

echo "Inserisci il campo magnetico"
read mag
sed -i "4 s/.*/$mag/" input.dat

echo "Inserire 1 per Metropolis e 0 per Gibbs"
read m
sed -i "5 s/.*/$m/" input.dat
if [ $mag = "0" ]
    then
    rm ene$m.out
    rm heat$m.out
    rm chi$m.out
    touch ene$m.out
    touch heat$m.out
    touch chi$m.out
   
else
    rm mag$m.out
    touch mag$m.out
fi

if [ $g = "y" ] || [ $g = "yes" ]
    then
    sh clean.sh
fi

for i in 0.5 0.6 0.7 0.8 0.9 1.0 1.1 1.2 1.3 1.4 1.5 1.6 1.7 1.8 1.9 2.0
do
    
    sed -i "1 s/.*/$i/" input.dat
    g="y"

    while [ $g = "y" ]
    do
        echo "[T=$i] Vuoi eseguire l'equilibrazione? [y/n]"
        read g
        if  [ -z "$g" ] || [ $g = "y" ] || [ $g = "yes" ]
            then 
            echo "[T=$i] Quanti passi vuoi eseguire?"
            read h
            if [ -z "$h" ]
                then
                h=200
            fi

            echo "[Editing input.dat]"
            sed -i "6 s/.*/$h/" input.dat
            sed -i "7 s/.*/1/" input.dat

            ./Monte_Carlo_ISING_1D.exe 

            
            if [ $mag = "0" ]
                then
                mv "output.ene.0" "output.ene.$m.eq0.$i"
                mv "output.heat.0" "output.heat.$m.eq0.$i"
                mv "output.chi.0" "output.chi.$m.eq0.$i"
                rm "output.mag.0" 
            else 
                rm "output.ene.0" 
                rm "output.heat.0" 
                rm "output.chi.0" 
                mv "output.mag.0" "output.mag.$m.eq$mag.$i"
            fi

            echo "[Coping final configuration in config.in]"
            cp config.final config.in
        fi

        if [ -z "$g" ]
            then
            g="n"
        fi

    done

    echo "Vuoi compiere la simulazione per T = $i ?[y/n]"
    read l
    if [ -z "$l" ] || [ $l = "y" ] || [ $l = "yes" ]
        then 
        echo "*****************"
        echo "TEMPERATURA = $i"
        echo -n "*****************\n\n"
        
        echo "[Editing input.dat]"

        sed -i "6 s/.*/20/" input.dat
        sed -i "7 s/.*/10000/" input.dat
        

    else
        exit
    fi
    
    ./Monte_Carlo_ISING_1D.exe 
    
    echo "[Renaming files]"
    if [ $mag = "0" ]
                then
                mv "output.ene.0" "output.ene0.$m.$i"
                mv "output.heat.0" "output.heat0.$m.$i"
                mv "output.chi.0" "output.chi0.$m.$i"
                rm "output.mag.0" 
            else 
                rm "output.ene.0"
                rm "output.heat.0" 
                rm "output.chi.0" 
                mv "output.mag.0" "output.mag$mag.$m.$i"
            fi
  
    
    echo "[adding values to output files]"
    if [ $mag = "0" ]
    then
        x="$(tail -n 1 output.ene0.$m.$i)"
        echo "$i   $x" >> "ene$m.out"
        x="$(tail -n 1 output.chi0.$m.$i)"
        echo "$i   $x" >> "chi$m.out"
        x="$(tail -n 1 output.heat0.$m.$i)"
        echo "$i   $x" >> "heat$m.out"

    else
        x="$(tail -n 1 output.mag$mag.$m.$i)"
        echo "$i   $x" >> "mag$m.out"
    fi
done
