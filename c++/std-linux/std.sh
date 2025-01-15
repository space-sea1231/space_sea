g++ -o std std.cpp -std=c++14 -O2 -fsanitize=address,undefined
./std<std.in>std.out
# diff -Bb std.out ans.out