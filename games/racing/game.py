import time
from controlBlock import ControlBlock
from asteroid import AsteroidList
import math
import engine


class Vec:
    def __init__(self, x: float, y: float):
        self.x: float = x
        self.y: float = y

class Game:
    class Window:
        size: Vec = Vec(0,0)

    def __init__(self) -> None:

        self.controlAbles: list = [ControlBlock(40,40, 50,50 , "../games/racing/assets/PixelSpaceRage/256px/PlayerBlue_Frame_01_png_processed.png")]

        self.window: Game.Window= Game.Window()

        self.window.size.x, self.window.size.y = engine.get_screen_width(), engine.get_screen_height()

        for block in self.controlAbles:
            block.edge_x, block.edge_y = self.window.size.x, self.window.size.y

        print("Window x, y = ", self.window.size.x, self.window.size.y)

        self.aList: list = AsteroidList(self.window.size.x, self.window.size.y)

        return

    def update(self):
        for block in self.controlAbles:
            block.update()

    def draw(self):
        for block in self.controlAbles:
            block.draw()
        self.aList.draw()
        

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
