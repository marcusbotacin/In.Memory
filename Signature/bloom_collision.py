#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Marcus Botacin - UFPR - 2018
# Bloom filter collision checker


import sys	# arguments
import random	# rand

# signature db
sigs=dict()

# open file
f=open(sys.argv[1],"r")
for i,line in enumerate(f):
	# store signature
	sigs[i]=line.strip()
	# save max lines
	lmax=i

# start detecting collisions
bloom = 0
count = 0
# while not collided yet
while(bloom!=int("F"*2*int(sys.argv[2]),16)):
	# pick a random number
	r = random.randint(0,lmax)
	# bloom or-ing
	bloom=bloom|int(sigs[r],16)
	# count the number of required signatures
	count=count+1
# display the number
print(count)
