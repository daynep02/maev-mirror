import time
from controlBlock import ControlBlock
from asteroid import AsteroidList
import math
import engine
from title import Title
from run import Run
from controls import Controls
from state import *



class Game:

    states = [None] * 3
    index = 1
    def __init__(self):

        self.states[TITLE] = Title()
        self.states[CONTROLS] = Controls()
        self.states[RUN] = Run()

        self.state = self.states[self.index]

        self.state_cooldown = engine.current_time()

    def update(self):

        val :int = self.state.update()

        if val >= 0:
            self.state = self.states[val]


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
