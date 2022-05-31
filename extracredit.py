# Authors: Data Niners
# Date: 05/30/2022
# Purpose: Sudoku Graphics

from cs1lib import *
import random


WIDTH = 800
HEIGHT = 800

mouse_press_x = 0
mouse_press_y = 0
mousepressed = False
check = False
new_puzzle = False

row = []
for i in range(9):
    column = [0, 0, 0, 0, 0, 0, 0, 0, 0]
    row.append(column)

def empty_location(board):
    for i in range(9):
        for j in range(9):
            if board[i][j] == 0:
                return (i, j)
    return (9, 9)

def shuffle():
    list = [1, 2, 3, 4, 5, 6, 7, 8, 9]
    random.shuffle(list)
    return list

def valid_input(board, row, col, num):
    for i in range(9):
        if i != col:
            if board[row][i] == num:
                return False

    for j in range(9):
        if j != row:
            if board[j][col] == num:
                return False

    row_mod = row % 3
    col_mod = col % 3
    for a in range(3):
        for b in range(3):
            if ((a + row - row_mod == row) and (b + col - col_mod)):
                continue
            if board[a + row - row_mod][b + col - col_mod] == num:
                return False
    return True


def solver_random(board):
    tuple = empty_location(board)
    the_row = tuple[0]
    col = tuple[1]
    if the_row == 9 and col == 9:
        return True

    for i in range(0, 9):
        list = [1, 2, 3, 4, 5, 6, 7, 8, 9]
        random.shuffle(list)
        if valid_input(board, the_row, col, list[i]):
            board[the_row][col] = list[i]

            if solver_random(board):
                return True

            board[the_row][col] = 0

    return False

def solver_forward(board):
    tuple = empty_location(board)
    the_row = tuple[0]
    col = tuple[1]
    if the_row == 9 and col == 9:
        return True

    for i in range(1, 10):
        if valid_input(board, the_row, col, i):
            board[the_row][col] = i

            if solver_forward(board):
                return True

            board[the_row][col] = 0

    return False

def solver_backward(board):
    tuple = empty_location(board)
    the_row = tuple[0]
    col = tuple[1]
    if the_row == 9 and col == 9:
        return True

    for i in range(9, 0, -1):

        if valid_input(board, the_row, col, i):
            board[the_row][col] = i

            if solver_backward(board):
                return True

            board[the_row][col] = 0

    return False

def sudoku_solve_random(board):
    if solver_random(board):
        return True
    else:
        return False

def board_print(board):
    for i in range(9):
        string = ""
        for j in range(9):
            string = string + str(board[i][j]) + " "
        print(string)

def copy(board):
    new_row = []
    for i in range(9):
        new_column = [0, 0, 0, 0, 0, 0, 0, 0, 0]
        new_row.append(new_column)
    for i in range(9):
        for j in range(9):
            new_row[i][j] = board[i][j]
    return new_row

def unique_solution(board):
    copyforward = copy(board)
    copybackward = copy(board)
    solver_forward(copyforward)
    solver_backward(copybackward)

    for i in range(9):
        for j in range(9):
            if copyforward[i][j] != copybackward[i][j]:
                return False
    return True



def remove_slots(board, empty_slots, emptied):
    row = 0
    col = 0
    while emptied < empty_slots:
        rand_row = random.randint(0, 8)
        rand_col = random.randint(0, 8)
        if board[rand_row][rand_col] != 0:
            copy = board[rand_row][rand_col]
            board[rand_row][rand_col] = 0
            if not unique_solution(board):
                board[rand_row][rand_col] = copy
                continue
            emptied+=1

def drawbox(min, max):
    draw_line(max / 3, min, max / 3, max)
    draw_line((2 * max) / 3, min, (2 * max) / 3, max)
    draw_line(min, max / 3, max, max / 3)
    draw_line(min, (2 * max) / 3, max, (2 * max) / 3)

def drawlines():
    for i in range(9):
        draw_line((i * (WIDTH / 9)), 0, i * (WIDTH / 9), HEIGHT)
    for j in range(9):
        draw_line(0, j * HEIGHT / 9, WIDTH, j * (HEIGHT / 9))

def drawgrid():
    set_stroke_color(0, 0, 0)
    set_stroke_width(8)
    drawbox(0, WIDTH)
    set_stroke_width(6)
    drawlines()

def drawnums(board):
    set_stroke_color(1, 0, 0)
    set_font_size(40)
    for i in range(9):
        for j in range(9):
            if board[i][j] != 0:
                draw_text(str(board[i][j]), WIDTH / 9 * i + 38, HEIGHT / 9 * j + 50)

def mousepress(mx, my):
    global mouse_press_x, mouse_press_y, mousepressed
    mouse_press_x = mx
    mouse_press_y = my
    mousepressed = True

def mouserelease(mx, my):
    global mousepressed, mouse_press_x, mouse_press_y
    mouse_press_x = mx
    mouse_press_y = my
    mousepressed = False


def createsudoku():
    empty_slots = 50
    emptied = 0

    sudoku_solve_random(row)

    remove_slots(row, empty_slots, emptied)

    return row

def keypress(value):
    global check, new_puzzle
    if value == " ":
        check = True


board = createsudoku()
answer = copy(board)
solver_backward(answer)


def drawfunc():
    global board, answer, mouse_press_x, mouse_press_y, check
    clear()
    drawgrid()
    drawnums(board)
    if mousepressed and not check:
        x = int(mouse_press_x / (HEIGHT / 9))
        y = int(mouse_press_y / (WIDTH / 9))
        i = 0
        while i < 1:
            num = input("num? ")
            i+=1


            board[x][y] = int(num)
            drawnums(board)
    if check and mousepressed:
        x = int(mouse_press_x / (HEIGHT / 9))
        y = int(mouse_press_y / (WIDTH / 9))
        board[x][y] = answer[x][y]
        drawnums(board)



start_graphics(drawfunc, width=WIDTH, height=HEIGHT, mouse_press=mousepress, mouse_release=mouserelease, key_press=keypress)

