import engine # type: ignore
from layers import Layer

class Enemy:
    knockback = (0.0,0.0)
    kb_time = 0.0
    kb_decay_rate = 0.3
    kb_factor = (250.0,250.0)
    dead = False

    def __init__(self,x,y):
        self.rb = engine.create_rigid_body((x,y),(25,25))
        #print(f"creating enemy rigid: {self.rb}" )
        engine.set_terminal_velo(self.rb, 0.0, 400.0)
        engine.set_rigid_body_static(self.rb, False)
        engine.set_rigid_body_gravity(self.rb, True)
        engine.set_rigid_body_layer(self.rb, Layer.ENEMY)

        self.sprite = engine.create_circle(12.5)
        engine.set_circle_fill_color(self.sprite,(234,67,50,255))
        engine.set_circle_position(self.sprite, (x,y))

        self.damage_sound = engine.create_sound("../games/dochs/assets/hit.ogg")
        
        self.damage = 1
        self.hp = 5
        self.speed = 100.0
        self.direction = -1
        self.patrol_duration = 2.0
        self.patrol_time = engine.current_time()

    def update(self):
        if engine.current_time()-self.patrol_time>self.patrol_duration:
            self.direction = self.direction * -1
            self.patrol_time = engine.current_time()
        
        kb_lock = self.decay_knockback()

        #patrol in a direction
        velocity = engine.get_rigid_body_velocity(self.rb)
        if not self.dead and not kb_lock:
            if velocity[0] < self.speed + 10.0 and velocity[0] > -self.speed - 10.0:
                engine.set_rigid_body_velocity(self.rb, (self.speed*self.direction,velocity[1]))
        if self.dead and not kb_lock:
            #print("the dead can't move")
            engine.set_rigid_body_velocity(self.rb, (0.0,velocity[1]))
        
        x, y = engine.get_rigid_body_position(self.rb)
        engine.set_circle_position(self.sprite,(x,y))

    def draw(self) -> None:
        #engine.draw_rigid_body_collider(self.rb)
        engine.draw_circle(self.sprite)
    
    def free(self):
        engine.free_rigid_body(self.rb)
        engine.free_circle(self.sprite)

    def decay_knockback(self):
        # decay knockback
        velocity = engine.get_rigid_body_velocity(self.rb)
        decay_mult = 1.0-((engine.current_time()-self.kb_time)/self.kb_decay_rate)
        if engine.current_time()-self.kb_time < self.kb_decay_rate:
            kbx = self.knockback[0]*decay_mult
            kby = velocity[1]
            engine.set_rigid_body_velocity(self.rb, (kbx, kby))
            return True
        return False

    def take_damage(self,amount, lx, ly):
        if self.dead:
            return
        self.hp -= amount
        engine.play_sound(self.damage_sound)
        if self.hp < 0:
            self.dead = True
            engine.set_rigid_body_layer(self.rb,Layer.DEAD)
            engine.set_circle_fill_color(self.sprite, (255,255,255,255))

        #print(f"Enemy: took {amount} damage! Now at {self.hp} HP.")
        self.knockback = (lx*self.kb_factor[0],ly*self.kb_factor[1])
        self.kb_time = engine.current_time()
        engine.set_rigid_body_velocity(self.rb, self.knockback)