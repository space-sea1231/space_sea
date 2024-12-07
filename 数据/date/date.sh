g++ -o date_in date_in.cpp -std=c++14 -O2 -fsanitize=address,undefined
g++ -o date_out date_out.cpp -std=c++14 -O2 -fsanitize=address,undefined
./date_in
./date_out