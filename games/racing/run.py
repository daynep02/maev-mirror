import engine
from asteroid import AsteroidList
from state import *
from controlBlock import ControlBlock

class Run:
    def __init__(self) -> None:

        self.controlable = ControlBlock(40,40, 50,50 , "../games/racing/assets/PixelSpaceRage/256px/PlayerBlue_Frame_01_png_processed.png")

        #self.window: Game.Window= Game.Window()

        self.w, self.h = engine.get_screen_width(), engine.get_screen_height()

        self.controlable.edge_x, self.controlable.egde_x = self.w, self.h

        self.aList: list = AsteroidList(self.w, self.h)

        engine.set_camera_size((self.w, self.h))

        return

    def update(self):

        self.controlable.update()

        engine.set_camera_position(self.controlable.position)

        if (engine.key_is_pressed("ESCAPE")):
            return TITLE

        return NO_CHANGE

    def draw(self):
        self.controlable.draw()
        self.aList.draw()
