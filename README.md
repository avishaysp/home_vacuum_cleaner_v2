Authors: Avishay Spitzer & Dory Grossman

To compile the program:
```make all```

To clean bin files:
```make clean```

## Description
The program recives as an argument a file containing:
1. maximum steps allowed on the run.
2. maximum steps allowed on a signle charge of the battery.
3. Size of the house.
4. map of the house, as the format below.

Writes to the output file the result.


## Example input
1. stam house
MaxSteps = 200
MaxBattery=30
Rows = 4
Cols =10
WWWW
W D
W 123456789

# The vacuum cleaner see the house as:
WWWWWWWWWWWW
WWWWW      W
WW D       W
WW 12345678W
W          W
WWWWWWWWWWWW


## Run

./myrobot <input_file>