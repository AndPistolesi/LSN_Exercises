
echo "Quale parametro vuoi variare? [s/Ne/Nt]"
read g

rm NN1.out #resetting NN1.out
touch NN1.out

if [ $g = "s" ]
    then
    for i in 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9
        do
        sed -i "1 s/.*/$i/g" input.dat #modifico input.dat
        sed -i "2 s/.*/30/g" input.dat
        sed -i "3 s/.*/500/g" input.dat

        python tf.py
        done
    mv NN1.out NN_sigma.out
    fi


if [ $g = "Ne" ]
    then
    for i in 10 20 30 40 50 60 70 80 90 100
        do
        sed -i "1 s/.*/0.3/g" input.dat #modifico input.dat
        sed -i "2 s/.*/$i/g" input.dat
        sed -i "3 s/.*/500/g" input.dat

        python tf.py
        done
    mv NN1.out NN_Nepochs.out
    fi

if [ $g = "Nt" ]
    then
    for i in 100 200 300 400 500 600 700 800 900 1000
        do
        sed -i "1 s/.*/0.3/g" input.dat #modifico input.dat
        sed -i "2 s/.*/30/g" input.dat
        sed -i "3 s/.*/$i/g" input.dat

        python tf.py
        done
    mv NN1.out NN_Ntrain.out
    fi