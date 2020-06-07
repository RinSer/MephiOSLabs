# Скрипт для тестирования программы,
# должен запускаться в одной папке с бинарником
for n in $(seq 2 100)
do
  for m in $(seq 1 1000000)
  do
    for l in $(seq 1 100)
    do
      ./MephiOSLabs6.out $n $m $l
    done
  done
done