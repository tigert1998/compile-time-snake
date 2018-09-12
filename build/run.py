import os
import random
import click
from functools import reduce

HEIGHT = 9

def calc_width_height(snake_map):
    height = len(snake_map)
    width = len(snake_map[0])
    return (height, width)

def generate_food(snake_map, snake):
    height, width = calc_width_height(snake_map)
    while True:
        x = random.randint(1, height - 2)
        y = random.randint(1, width - 2)
        if (x, y) in snake:
            continue
        return (x, y)

def init(height, width):
    snake_map = [[2] * width for _ in range(height)]
    for i in range(1, height - 1):
        for j in range(1, width - 1):
            snake_map[i][j] = 0
    x = random.randint(2, height - 3)
    y = random.randint(2, width - 3)
    d = random.randint(0, 3)
    snake = [(x, y)]
    if d == 0:
        snake.append((x, y - 1))
    elif d == 1:
        snake.append((x + 1, y))
    elif d == 2:
        snake.append((x, y + 1))
    elif d == 3:
        snake.append((x - 1, y))
    x, y = generate_food(snake_map, snake)
    snake_map[x][y] = 1
    return d, snake_map, snake

def print_game(snake_map, snake):
    os.system("clear")
    height, width = calc_width_height(snake_map)
    output = [[0] * width for _ in range(height)]
    for i in range(height):
        for j in range(width):
            output[i][j] = snake_map[i][j]
    for x, y in snake:
        output[x][y] = 3
    for i in range(height):
        for j in range(width):
            v = output[i][j]
            if v == 0:
                print("\033[0;36;47m.\033[0m", end="")
            elif v == 1:
                print("\033[0;31;47m*\033[0m", end="")
            elif v == 2:
                print("\033[0;30;47m#\033[0m", end="")
            elif v == 3:
                print("\033[0;34;47m@\033[0m", end="")
        print()

def go():
    global is_dead
    global direction
    global snake_map
    global snake
    height, width = calc_width_height(snake_map)
    info = str(direction) + " " + str(len(snake))
    for x, y in snake:
        info += " " + str(x) + " " + str(y)
    info += " " + str(height) + " " + str(width)
    for i in range(height):
        for j in range(width):
            info += " " + str(snake_map[i][j])
    os.system("echo " + info + " | ../bin/generator > ../src/main.cpp")
    os.system("clang++ -std=c++11 ../src/main.cpp -o ../bin/main")
    new_state = os.popen("../bin/main").read()
    new_state = map(lambda x: int(x), filter(lambda x: x != '', new_state.replace('\n', ' ').split(' ')))
    is_dead = bool(next(new_state))
    if is_dead:
        return
    next(new_state)
    len_snake = next(new_state)
    snake = [(next(new_state), next(new_state)) for _ in range(len_snake)]
    next(new_state); next(new_state)
    for i in range(height):
        for j in range(width):
            snake_map[i][j] = next(new_state)

direction, snake_map, snake = init(HEIGHT, HEIGHT)
while True:
    print_game(snake_map, snake)
    key = click.getchar()
    if direction != 2 and (key == 'd' or key == 'D'):
        direction = 0
    elif direction != 3 and (key == 'w' or key == 'W'):
        direction = 1
    elif direction != 0 and (key == 'a' or key == 'A'):
        direction = 2
    elif direction != 1 and (key == 's' or key == 'S'):
        direction = 3
    go()
    if is_dead:
        print("\033[0;31;40mGame Over\033[0m")
        break
    food_total = sum(map(lambda row: reduce(lambda x, y: x + int(y == 1), row, 0), snake_map))
    if food_total == 0:
        x, y = generate_food(snake_map, snake)
        snake_map[x][y] = 1
