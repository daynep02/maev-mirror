import engine # type: ignore

class Enemy:
    knockback = (0.0,0.0)
    kb_time = 0.0
    kb_decay_rate = 0.5
    kb_factor = (250.0,250.0)

    def __init__(self):
        self.rb = engine.create_rigid_body((400,50),(25,35))
        print(f"creating enemy rigid: {self.rb}" )
        engine.set_terminal_velo(self.rb, 0.0, 400.0)
        engine.set_rigid_body_static(self.rb, False)
        engine.set_rigid_body_gravity(self.rb, True)
        
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
        
        self.decay_knockback()

        #patrol in a direction
        velocity = engine.get_rigid_body_velocity(self.rb)
        if velocity[0] < self.speed + 10.0 and velocity[0] > -self.speed - 10.0:
            engine.set_rigid_body_velocity(self.rb, (self.speed*self.direction,velocity[1]))

    def draw(self) -> None:
        engine.draw_rigid_body_collider(self.rb)

    def decay_knockback(self):
        # decay knockback
        velocity = engine.get_rigid_body_velocity(self.rb)
        decay_mult = 1.0-((engine.current_time()-self.kb_time)/self.kb_decay_rate)
        if engine.current_time()-self.kb_time < self.kb_decay_rate:
            kbx = self.knockback[0]*decay_mult
            kby = velocity[1]
            engine.set_rigid_body_velocity(self.rb, (kbx, kby))

    def take_damage(self,amount, lx, ly):
        self.hp -= amount
        print(f"Enemy: took {amount} damage! Now at {self.hp} HP.")
        self.knockback = (lx*self.kb_factor[0],ly*self.kb_factor[1])
        self.kb_time = engine.current_time()
        engine.set_rigid_body_velocity(self.rb, self.knockback)