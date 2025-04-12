import engine
import time
import math

class Ball:
    def __init__(self):
        self.x = 200
        self.y = 200

class Game:
    def __init__(self):
        self.ball = Ball()

game = None

def init():
    global game
    game = Game()

first = True

def update():
    global first
    global game

    t = time.time()

    game.ball.x = math.cos(t) * 50 + 200
    game.ball.y = math.sin(t) * 59 + 200

    if first and engine.key_is_pressed(0):
        print("A was pressed")
        first = False

    

def draw():
    global game

    ball = game.ball

    engine.draw_circle(int(ball.x), int(ball.y))
