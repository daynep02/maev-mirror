import time
from controlBlock import ControlBlock
import math


class Game:

    def __init__(self) -> None:
        self.controlAbles = [ControlBlock(40,40, 50,50 , "../games/racing/assets/soup.jpg")]
        return

    def update(self):
        for block in self.controlAbles:
            block.update()

    def draw(self):
        for block in self.controlAbles:
            block.draw()



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
