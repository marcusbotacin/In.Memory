#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Marcus Botacin - UFPR - 2018
# K-means-based signature clustering


import sys				# arguments
import random				# rand	
from sklearn.cluster import KMeans	# clustering
import numpy as np			# data representation

# signature DB
sigs=[]

# open file
f=open(sys.argv[1],"r")
# one sig per line
for line in f:
	# signature as byte vector
	local_vector = []
	for byte in line.strip():
		# char to hex
		local_vector.append(int(byte,16))
	# signatures vector
	sigs.append(local_vector)

# convert to numpy
X = np.array(sigs)
# clusterize
kmeans = KMeans(n_clusters=int(sys.argv[2]), random_state=0).fit(X)
# print labels
for label in kmeans.labels_:
	print(label)
