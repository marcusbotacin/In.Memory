# In.Memory

This repository contains additional material for the "In-Memory Malware Detection" paper (to be published)

## Organization

* The *Signature* directory contains code to simulate the hardware signature generation procedure 
    * The *bloom_collision.py* script counts how many signatures you can add to a bloom filter before creating a collision.
    * The *dispatch.py* script implements an exact match table.
    * The *kmeans.py* script clusters similar signatures.
* The *Interception* directory contains code to simulate a software-based memory inspector.
    * The *Windows* repository contains the implementation of a proto-AV based on [mhook](https://github.com/apriorit/mhook). Built using CMake.
    * The *Linux* repository contains the implementation of a proto-AV based on *LD_PRELOAD*. OpenSSL is used for MD5 computation.
