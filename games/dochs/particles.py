import engine #type: ignore
import random

# implementation adapted from https://www.lexaloffle.com/bbs/?tid=53826

class Particle:
    def __init__(self, x, y, dx, dy, radius, ttl, color):
        self.x = x
        self.y = y
        self.dx = dx
        self.dy = dy
        self.radius = radius
        self.life = ttl
        self.ttl = ttl
        self.color = color

        self.circle = engine.create_circle(self.radius)
        self.update_circle(self.radius)
    
    def update_circle(self, radius):
        engine.set_circle_position(self.circle, (self.x, self.y))
        engine.set_circle_radius(self.circle, radius)
        engine.set_circle_fill_color(self.circle, self.color)

class ParticleHandler:
    def __init__(self):
        self.classic = []

    def update(self):
        self.render_classic()

    def draw(self):
        self.draw_type(self.classic)
        
    def draw_type(self,particles):
        for p in particles:
            engine.draw_circle(p.circle)

    def spawn_classic(self, x, y):
        min_speed = 0.0
        max_speed = 200.0
        life = 0.5
        color = (255,255,255,255)
        for i in range(30):
            self.classic.append(Particle(x,y, # spawn location
                                         random.uniform(min_speed,max_speed)-(max_speed/2), # velocity x
                                         random.uniform(min_speed,max_speed)-(max_speed/2), # velocity y
                                         random.uniform(1,4), # starting size
                                         life,                 # time to live
                                         color))  # color
        #print("done spawing classic")

    def render_classic(self):
        if len(self.classic) == 0:
            return
        for i in range(len(self.classic)-1,-1,-1):
            self.classic[i].x += (self.classic[i].dx*engine.delta_time())*2
            self.classic[i].y += (self.classic[i].dy*engine.delta_time())*2
            self.classic[i].ttl -= engine.delta_time()
            
            # I want to decay the size here
            decay = 1-((self.classic[i].life-self.classic[i].ttl)/self.classic[i].life)

            self.classic[i].update_circle(self.classic[i].radius*decay)
            if self.classic[i].ttl < 0.0:
                engine.free_circle(self.classic[i].circle)
                del self.classic[i]