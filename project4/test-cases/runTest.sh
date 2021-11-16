rm -f "difference.txt"
for i in $(seq 0 15)
do
    echo "in command ${i}:" >>"difference.txt"
    read file bankroll handsNum mode <"${i}.in"
    $file $bankroll $handsNum $mode >"my${i}.out"
    diff "my${i}.out" "${i}.out" >>"difference.txt"
    rm -f "my${i}.out"
done
