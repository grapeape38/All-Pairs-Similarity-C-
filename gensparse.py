import random
n = 5000
r = 50 
sparse_chance = 0.8
for i in range(n):
    for j in range(r):
        b = random.random()
        v = random.randint(0, r - 1)
        d = random.random() * 5000
        if (b < 1 - sparse_chance):
            print(str(v) + ':' + str(d) + ' ', end='')
    print()

