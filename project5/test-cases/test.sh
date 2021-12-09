g++ -o calc ../calc.cpp -Wall
g++ -o call ../call.cpp -Wall

echo difference: > difference.txt

cd pretest
for i in $(seq 0 3)
do
    echo "In command ${i}:" >> difference.txt
    ../calc <"${i}.in" >"my${i}.out"
    diff "my${i}.out" "${i}.out" >> difference.txt
    rm -f "my${i}.out"
done
cd ..

for i in $(seq 0 5)
do
    echo "In command ${i}:" >> difference.txt
    ../call <"${i}.in" >"my${i}.out"
    diff "my${i}.out" "${i}.out" >> difference.txt
    rm -f "my${i}.out"
done

for i in $(seq 6 9)
do
    echo "In command ${i}:" >> difference.txt
    ../calc <"${i}.in" >"my${i}.out"
    diff "my${i}.out" "${i}.out" >> difference.txt
    rm -f "my${i}.out"
done