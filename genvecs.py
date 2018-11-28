import random
numdims = 50 
n = 1000 
r = 1000
for i in range(n):
    for j in range(numdims):
        d = random.random() * r
        b = random.random()
        m = 0 if b >= 0.2 else 1
        d *= m
        print(str(round(d,3)) + ' ', end='')
    print()
