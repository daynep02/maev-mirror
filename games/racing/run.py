import engine
from asteroid import AsteroidList
from state import *
from controlBlock import ControlBlock

class Run:
    def __init__(self, camera) -> None:

        self.camera = camera

        self.controlable = ControlBlock(10,10, 50,50 , "../games/racing/assets/PixelSpaceRage/256px/PlayerBlue_Frame_01_png_processed.png")

        #self.window: Game.Window= Game.Window()

        self.w, self.h = self.camera.get_size()

        self.controlable.edge_x, self.controlable.egde_x = self.w, self.h

        self.aList: list = AsteroidList(self.w, self.h)


        return

    def start(self):
 #       self.camera.set_velocity((0.0, 0.5))
        pass

    def update(self):

     #   self.camera.set_velocity((0.0, 0.5))

        self.controlable.update()
        self.aList.update()


        #self.camera.set_position(self.controlable.get_position())
        self.camera.update()

        if (engine.key_is_pressed("ESCAPE")):
            return TITLE

        return NO_CHANGE

    def draw(self):
        self.controlable.draw()
        self.aList.draw()
