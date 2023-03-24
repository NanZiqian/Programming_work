g++ -o man -I bitmap-master/src manderbrot-master/src/manderbrot.cpp bitmap-master/src/bitmap.cpp -std=c++17
./man $1 $2 $3 $4

