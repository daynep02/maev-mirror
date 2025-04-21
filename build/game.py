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
        self.ball2 = Ball()
        self.vec1 = Vectorf()
        self.background = engine.create_sprite("../inspiration.jpg")
        print("made it 1")
        engine.set_sprite_position(self.background,(0,0))
        print("made it 2")

game = None
first = True

# Key Functions for Game
def init():
    global game
    game = Game()
    #engine.free_sprite(game.background)

def update():
    global game
    global first
    key = "NUM0"
    t = time.time()
    game.ball.x = math.cos(t) * 50 + 200
    game.ball.y = math.sin(t) * 59 + 200
    engine.set_circle_position(game.ball.circle,(game.ball.x,game.ball.y))

    game.ball2.x = math.cos(0) * 50 + 200
    game.ball2.y = math.sin(0) * 59 + 200
    engine.set_circle_position(game.ball2.circle,(game.ball2.x,game.ball2.y))

    

    # engine.collides_with(game.ball.circle,game.ball2.circle)
    if engine.collides_with(game.ball.circle,game.ball2.circle):
        print("Balls are colliding")

    #if first and engine.key_is_pressed(key):
    #    first = False
    #    print(f"{key} has been pressed")
    # print(engine.collides_with(game.ball.circle,game.ball2.circle))

def draw():
    global game

    ball = game.ball

    engine.draw_sprite(game.background)
    engine.draw_circle(ball.circle)
    engine.draw_circle(game.ball2.circle)

