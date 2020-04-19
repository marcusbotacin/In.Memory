#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Marcus Botacin - UFPR - 2018
# Dispatch Table for in-memory signature matching

import sys	# Arguments

# Matcher class
class Matcher():
	def __init__(self):
		self.tree = dict()

	# load signatures from file
	def load_sigs(self,sig_file):
		f=open(sig_file,"r")
		# one per line
		for line in f:
			# start on tree's top
			current = self.tree
			for c in line.strip():
				index = int(c,16)
				# create if not existing
				if index not in current:
					current[index]=dict()
				# recursively traverse the tree
				current=current[index]

	# method wrapper
	def test_sig(self,sig):
		# start with default db and from beginning
		return self.__test_sig(sig,self.tree,0)

	# test method
	def __test_sig(self,sig,tree,n):
		# end of signature, end of recursion
		if n==len(sig):
			return True
		index = int(sig[n],16)
		# while matching, recursive calls
		if index in tree:
			return self.__test_sig(sig,tree[index],n+1)
		# no matching
		else:
			return False

	# print loaded sigs for debugging purposes
	def print_sigs(self):
		print(self.tree)

	# match a signature file against database
	def match_file(self,m_file):
		f=open(m_file,"r")
		# one signature per line
		for line in f:
			print("Testing %s: %d" % (line.strip(),self.test_sig(line.strip())))				

class Parser():
	def __init__(self):
		return
	# parse arguments
	def parse(self,args):
		# check minimum number was supplied
		if(len(args)!=3):
			self.usage()
			sys.exit(0)
		# return files
		# fixed position -- it can be enhanced!
		return args[1],args[2]
	# display usage message
	def usage(self):
		print("./command <signature_file> <match_file>")

# Entry point
if __name__ == '__main__':

	# Instantiate things
	m = Matcher()
	p = Parser()

	# try parsing
	s_file,m_file = p.parse(sys.argv)

	# if ok,
	# load signatures from file
	m.load_sigs(s_file)
	# debug print
	m.print_sigs()
	# Match files
	m.match_file(m_file)
else:
	print("No module import support yet!")
