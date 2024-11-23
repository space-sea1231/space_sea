g++ -o std std.cpp -std=c++14 -fsanitize=address,undefined,signed-integer-overflow 
./std<std.in>std.out