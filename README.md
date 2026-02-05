# NMA_Primeri
Primeri iz Naprednih Mikroprocesorskih Arhitektura o paralelnom programiranju
Dokument: 2-1-OpenMP-primeri.pdf


##How to setup:
-----------------------------------------------------------------------------------
Using gcc compiler. It should be standard with WSL environment.  

Verify with: 
``` bash
    echo | cpp -fopenmp -dM | grep -i open
```  

To install if it is missing:
``` bash
    sudo apt update 
    sudo apt install libomp-dev
```

To limit number of threads used by program: `export OMP_NUM_THREADS=4`  (or `setenv`)




##Run command:
-----------------------------------------------------------------------------------
``` bash  
gcc -fopenmp app.c -o executable_app
```   


