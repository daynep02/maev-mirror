import engine #type: ignore
from layers import Layer

class Platform:
    def __init__(self, x,y,w,h):
        self.rb = engine.create_rigid_body((x,y),(w,h))
        engine.set_rigid_body_static(self.rb,True)
        engine.set_rigid_body_gravity(self.rb,False)
        engine.set_rigid_body_layer(self.rb, Layer.PLATFORM)

    def set_position(self,x,y):
        engine.set_rigid_body_position(self.rb, (x,y))
    
    def set_size(self, w, h):
        engine.set_rigid_body_size(self.rb, (w,h))

    def draw(self):
        engine.draw_rigid_body_collider(self.rb)