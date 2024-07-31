Authors: Avishay Spitzer & Dory Grossman

To compile the program:
```make all```

To clean bin files:
```make clean```

## Description
The program recives as an argument a file containing:
1. maximum steps allowed on a signle charge of the battery.
2. maximum steps allowed on the run.
3. coordinates of the docking location, which is also the starting point.
4. map of the house, as the format below.

Writes to the output file the cleaned house.


## Example input
20,100,(1|1)
+ +-+-+-+
 /|3 2 0|
+-+ + + +
|5 0 / 2|
+-+-+-+-+

# Legend
'+' = a cross of walls. must be present o all even indecies.
' ' = a coridor posible to pass through
'/' = a tile where there is no indoor flor (e.g. balcony)
'3' = a tile with dirt level 3
'-' = horizontal wall
'|' = vertical wall

## Run

./myrobot <input_file>