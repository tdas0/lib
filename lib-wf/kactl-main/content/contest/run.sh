g++ -std=c++17 -o generator generator.cpp
g++ -std=c++17 -o main main.cpp
g++ -std=c++17 -o naive naive.cpp

value=1

while [ $value -le $1 ]
do
  ./generator $value > in.txt
  ./main < in.txt > out_main.txt
  ./naive < in.txt > out_naive.txt

  result=$(diff out_main.txt out_naive.txt)

  if [ $? -eq 0 ]
  then
          printf "Test $value: Accepted\n"
  else
          printf "Test $value: Wrong Answer\n"
          printf "\nInput:\n"
          cat in.txt
          printf "\nOutput:\n"
          cat out_main.txt
          printf "\nAnswer:\n"
          cat out_naive.txt

          break
  fi

  value=$((value+1))
done
