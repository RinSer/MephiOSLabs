# Скрипт для тестирования программы,
# должен запускаться в одной папке с бинарником
for n in {2..100}
do
  for m in {1..1000000}
  do
    for l in {1..100}
    do
      ./MephiOSLabs6.out $n $m $l
    done
  done
done