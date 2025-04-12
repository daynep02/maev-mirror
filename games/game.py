import engine
import time
import math

class Ball:
    def __init__(self):
        self.circle = engine.create_circle(10.0)
        engine.set_circle_fill_color(self.circle,(0,255,0,255))
        self.x = 200
        self.y = 200

class Game:
    def __init__(self):
        self.ball = Ball()
        self.background = engine.create_sprite("inspiration.jpg")
        engine.set_sprite_position(self.background,(0,0))

game = None

# Key Functions for Game
def init():
    global game
    game = Game()
    #engine.free_sprite(game.background)

def update():
    global game

    t = time.time()

    game.ball.x = math.cos(t) * 50 + 200
    game.ball.y = math.sin(t) * 59 + 200
    engine.set_circle_position(game.ball.circle,(game.ball.x,game.ball.y))

def draw():
    global game

    ball = game.ball

    engine.draw_sprite(game.background)
    engine.draw_circle(ball.circle)
