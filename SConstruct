env = Environment(CCFLAGS='-std=c++17 -Wall -O3')

targets = {}
for i in range(1, 10):
    name = 'p%d' % i
    targets[name] = name + '.cc'

for target in targets:
    objs = targets[target]
    env.Program(target, objs)
