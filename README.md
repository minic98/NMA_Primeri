# NMA_Primeri
Primeri iz Naprednih Mikroprocesorskih Arhitektura o paralelnom programiranju


##How to setup:
-----------------------------------------------------------------------------------
Using gcc compiler. It should be standard with WSL environment.  

Verify with: `echo | cpp -fopenmp -dM | grep -i open`  

To install if it is missing:
``` bash
    sudo apt update 
    sudo apt install libomp-dev
```

To limit number of threads used by program: `export OMP_NUM_THREADS=4`  (or `setenv`)




##Run command:
-----------------------------------------------------------------------------------
`gcc -fopenmp app.c -o executable_app`  


