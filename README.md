# Nonogram Solver
Another nonogram solver based on *[An Efficient Approach to Solving Nonograms](https://ieeexplore.ieee.org/document/6476646)*.  
Not yet complete.

## Usage
### Download the code
```
git clone https://github.com/9501sam/nonogram-solver
cd nonogram-solver/
```

### Compile and run
#### 1. using makefile
```sh
make run
```
#### 2. compile manually
```sh
gcc -c board.c -Wall -O3
gcc -c solve.c -Wall -O3
gcc -c nonogram.c -Wall -O3
gcc -o nonogram board.o solve.o nonogram.o -Wall -O3
./nonogram input_data
```
