g++ -o tmp tmp.cpp -std=c++14 -O2 -fsanitize=address,undefined
./tmp<tmp.in>tmp.out
# time ./tmp<tmp.in>tmp.out