import sys
import random

print(sys.argv[1])
for _ in range(2 * int(sys.argv[1])):
    print(random.randint(0, 9), end='')
print(' ', end='')
print(int(sys.argv[2]))
for _ in range(int(sys.argv[2])):
    l = random.randint(0, int(sys.argv[1]) - 1)
    r = random.randint(l + 1, int(sys.argv[1]))
    print(2 * l, 2 * r, end = ' ')
    d = r - l
    l = random.randint(0, int(sys.argv[1]) - d)
    r = l + d
    print(2 * l, 2 * r)
