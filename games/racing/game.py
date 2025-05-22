import time
from controlBlock import ControlBlock
from asteroid import AsteroidList
import math
import engine
from title import Title
from gameOver import GameOver
from run import Run
from controls import Controls
from camera import Camera
from state import *



class Game:

    class Quit:
        def __init__(self):
            return

        def start(self):
            engine.exit()

    states = [None] * 5
    index = 0
    def __init__(self):

        w = engine.get_screen_width()
        h = engine.get_screen_height()

        self.camera = Camera(0,0, w, h)

        self.states[TITLE] = Title(self.camera)

        self.states[CONTROLS] = Controls()

        self.states[RUN] = Run(self.camera, rigid_body_callback)

        self.states[GAME_OVER] = GameOver(self.camera)

        self.states[QUIT] = Game.Quit()

        self.state = self.states[self.index]

        self.state.start()

        self.state_cooldown = engine.current_time()

    def update(self):

        self.index :int = self.state.update()

        if self.index >= 0:
            self.state = self.states[self.index]
            self.state.start()

        self.camera.update()


    def draw(self):
        self.state.draw()
    
        

game = None

def update():
    global game
    game.update()
    

def init():
    global game
    game = Game()

def draw():
    global game
    game.draw()

def rigid_body_callback(_, __):
    global game

    game.index = GAME_OVER

    game.state = game.states[game.index]

    game.state.start()


