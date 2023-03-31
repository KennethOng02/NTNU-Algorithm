import random

n = 100000

with open("test.txt", "w") as f:
    f.write(f'{n}\n')
    for i in range(n):
        f.write(f'{random.randint(-2**30, 2**30)} {random.randint(-2**30, 2**30)}')
        if i != n - 1:
            f.write('\n')

