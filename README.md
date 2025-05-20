# Edge2A

Short for Edge2ANode. The best Graph Database Managment System of our times[^1]

[^1]: trust me bro

# Instructions

## Requirements

Make sure you have the following dependencies installed before building:
- **CMake** (version 3.22 or higher)
- **GCC** / **Clang** (with C++20 support)
- **FLEX** (Fast Lexical Analyzer)
- **BISON** (GNU Parser Generator)

## Build
``` shell
mkdir build
cd build
cmake ..
make
```

## Test

``` shell
ctest
```

## Run

``` shell
./edge2a
```

## Demo
This is a simple demo application which uses graphDB populated with the movies dataset.
It fetches movies according to filters provided by the user.

`Frontend:  React`
`Backend:   C++`

Install node dependencies as
```
cd ./demo/frontend/
npm install
```

Run the application using
```
npm start
```
