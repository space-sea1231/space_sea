g++ -o data_in data_in.cpp -std=c++14 -O2 -fsanitize=address,undefined
g++ -o data_out data_out.cpp -std=c++14 -O2 -fsanitize=address,undefined
./data_in
./data_out