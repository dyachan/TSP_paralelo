#!/usr/bin/env python3

import sys, random

f = open(sys.argv[1], 'r')
cant = f.readline()

lineas = []
while True:
  l = f.readline()
  if not l:
    break
    
  lineas.append(l)
f.close()

for i in range(len(lineas)):
  r = random.randint(0, len(lineas)-1)
  lineas[i], lineas[r] = lineas[r], lineas[i]

f = open(sys.argv[1]+".new", 'w')
f.write(cant)
for l in lineas:
  f.write(l)
f.close()
