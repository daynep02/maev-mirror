import engine #type: ignore
from platform import Platform
from spike import Spike
from layers import Layer
from enemy import Enemy

class Tutorial:
    def __init__(self,player,spike_callback,activate_spike):
        self.player = player
        #The platform to collide with
        self.platforms = [Platform(-1000,400,1000,20), # tutorial buttom platform
                          Platform(-1000,0,10,400),
                          Platform(-800,390,75,10),
                          Platform(-500,300,75,10),
                          Platform(-400,200,75,10)] 

        self.platforms[0].set_color((255,255,255,255))
        self.platforms[1].set_color((255,255,255,255))

        self.spikes = [Spike(-500,380,200,20,0,-1,spike_callback)]
        
        self.spike_t = engine.create_box_collider((-650,300),(100,100))
        engine.set_box_callback(self.spike_t,activate_spike)
        engine.set_box_layer(self.spike_t, Layer.SPIKE)
        self.trigger_hit = False
        
        self.enemy = Enemy(-100,350)

    def update(self):
        self.enemy.update()

    def draw(self):
        for plat in self.platforms:
            plat.draw()
        for s in self.spikes:
            s.draw()
        
        self.enemy.draw()
        #engine.draw_box(self.spike_t)