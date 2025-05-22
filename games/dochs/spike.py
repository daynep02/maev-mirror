import engine #type: ignore
from layers import Layer
import random

class Spike:
    def __init__(self,x,y,w,h,dx,dy,callback):
        self.x, self.y = x, y
        self.box = engine.create_box_collider((x,y),(w,h))
        engine.set_box_layer(self.box, Layer.TRIGGER)
        engine.set_box_callback(self.box, callback)
        self.set_trigger(False)

        # knockback direction
        self.kd = (dx,dy)
    
    def set_trigger(self, b):
        engine.set_box_trigger(self.box, b)

    def set_position(self,x,y):
        engine.set_box_position(self.box, (x,y))
    
    def set_size(self, w, h):
        engine.set_box_size(self.box, (w,h))

    def jiggle(self):
        new_x = random.randrange(self.x-5,self.x+5)
        new_y = random.randrange(self.y-5,self.y+5)
        engine.set_box_position(self.box, (new_x,new_y))

    def draw(self):
        engine.draw_box(self.box)
    
    def free(self):
        engine.free_box_collider(self.box)