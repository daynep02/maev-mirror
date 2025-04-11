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

# Key Functions for Game
def init():
    global game
    game = Game()

def update():
    global game

    t = time.time()

    game.ball.x = math.cos(t) * 50 + 200
    game.ball.y = math.sin(t) * 59 + 200

def draw():
    global game

    ball = game.ball

    engine.draw_circle(int(ball.x), int(ball.y))
