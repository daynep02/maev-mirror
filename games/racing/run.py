import engine
from asteroid import AsteroidList
from state import *
from controlBlock import ControlBlock

class Run:

    def __init__(self, camera, collision_callback) -> None:

        self.camera = camera

        self.framerate = 60

        engine.set_framerate_limit(self.framerate)

        self.w, self.h = self.camera.get_size() 

        camera_pos = self.camera.get_position()

        self.right :float = camera_pos[0] + self.w / 2

        self.left :float = camera_pos[0] - self.w / 2

        self.bottom = self.h / 2

        self.top :float = camera_pos[1] - self.h / 2

        centerx, centery = (self.right + self.left) / 2, (self.top + self.bottom) /2 

        self.controlable :ControlBlock = ControlBlock(centerx, self.bottom - 50, 
                                                      50, 50, 
                                                      collision_callback, 
                                                      "../games/racing/assets/PixelSpaceRage/256px/PlayerBlue_Frame_01_png_processed.png")

        self.controlable.edge_x = self.w 

        self.controlable.edge_y = self.h

        self.aList: AsteroidList = AsteroidList(self.left, self.top, self.right, self.bottom)

        return

    def start(self):
        self.camera.set_velocity((0.0, 0.5))
        self.camera.set_position((0.0, 0.0))
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

