# TMGVD-Proy1
Sketches for approximatted similitudes between genomes

### Disclaimer
This project makes use of smhasher, made by aapleby

### Compilation
To run this project, run the command

```bash
g++ main.cpp
```

and execute the file made.

### Execution

After execution, 5 different FNA files will be run through the hyperloglog implementation that was made within. Afterwards, Jaccard will be calculated between the genome's sketches. Finally, the error values will be estimated. All the user can do in this step is wait and read the console outputs.

Note that cardinalities and errors can change between iterations, as the algorithm has a random seed for hashing.
