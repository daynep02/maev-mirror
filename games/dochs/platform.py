import engine #type: ignore
from layers import Layer
import random

class Platform:
    def __init__(self, x,y,w,h):
        self.x, self.y = x, y
        self.rb = engine.create_rigid_body((x,y),(w,h))
        engine.set_rigid_body_static(self.rb,True)
        engine.set_rigid_body_gravity(self.rb,False)
        engine.set_rigid_body_layer(self.rb, Layer.PLATFORM)

        self.sprite = engine.create_rect((w,h))
        engine.set_rect_fill_color(self.sprite,(128,128,128,255))
        engine.set_rect_position(self.sprite, (x,y))

    def set_position(self,x,y):
        engine.set_rigid_body_position(self.rb, (x,y))
        engine.set_rect_position(self.sprite, (x,y))
    
    def set_size(self, w, h):
        engine.set_rigid_body_size(self.rb, (w,h))
        engine.set_rect_size(self.sprite, (w,h))

    def jiggle(self):
        new_x = random.randrange(self.x-5,self.x+5)
        new_y = random.randrange(self.y-5,self.y+5)
        self.set_position(new_x,new_y)

    def draw(self):
        #engine.draw_rigid_body_collider(self.rb)
        engine.draw_rect(self.sprite)
    
    def free(self):
        engine.free_rigid_body(self.rb)