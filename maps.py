import random

SIZE = int(input("Holaaa! que tan grande quieres q sea tu mapa??: "))
LIST = ['0'] * int(input("que porcentaje quieres que sea aire? ")) + ['1'] * int(input("y cuanto quieres que sean paredes? "))

print('1' * (SIZE + 2))
for y in range(0, SIZE):
    print('1', end='')
    for x in range(0, SIZE):
        print(random.choice(LIST), end='')
    print('1')
print('1' * (SIZE + 2))