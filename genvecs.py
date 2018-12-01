import random
numdims = 25 
n = 5000
r = 1000
sparse_chance = 0.9
for i in range(n):
    for j in range(numdims):
        d = random.random() * r
        b = random.random()
        m = 0 if b >= 1 - sparse_chance else 1
        d *= m
        print(str(round(d,3)) + ' ', end='')
    print()

