import engine # type: ignore

class Player:
    # movement variables
    slide_left = 1
    slide_right = 1
    slide_time = 0.0
    grounded = False
    coyote_time = 0.0
    jumping = False
    jump_time = 0.0
    knockback = (0.0,0.0)
    kb_time = 0.0
    kb_decay_rate = 0.5

    # game variables
    hp = 5
    invincible = False
    invincible_time = 0.0

    def __init__(self):
        self.rb = engine.create_rigid_body((125,50),(25,25))
        print(f"creating player rigid: {self.rb}" )
        engine.set_terminal_velo(self.rb, 0.0, 400.0)
        engine.set_rigid_body_static(self.rb, False)
        engine.set_rigid_body_gravity(self.rb, True)

        self.speed = 200.0
        self.jump_speed = -480.0
    
    def draw(self) -> None:
        engine.draw_rigid_body_collider(self.rb)

    def take_damage(self,amount, lx, ly):
        if self.invincible:
            return
        self.hp -= amount
        print(f"Took {amount} damage! Now at {self.hp} HP.")
        self.knockback = (lx,ly)
        self.kb_time = engine.current_time()
        engine.set_rigid_body_velocity(self.rb, self.knockback)

        self.jumping = False
        self.invincible = True
        self.invincible_time = engine.current_time()

    def movement(self) -> None:
        # jumping logic
        #print(engine.delta_time())
        velocity = engine.get_rigid_body_velocity(self.rb)
        if self.jumping:
            if engine.current_time()-self.jump_time > 0.3:
                self.jumping = False
            elif engine.key_is_pressed(" "):
                engine.apply_force(self.rb, 0.0, self.jump_speed*engine.delta_time())
            else:
                engine.set_rigid_body_velocity(self.rb, (velocity[0],10.0))
                self.jumping = False

        if engine.key_is_pressed(" ") and not self.jumping and (self.grounded or engine.current_time()-self.coyote_time<0.15):
            engine.set_rigid_body_velocity(self.rb, (velocity[0], self.jump_speed))
            self.jumping = True
            self.grounded = False
            self.jump_time = engine.current_time()

        # decay knockback
        velocity = engine.get_rigid_body_velocity(self.rb)
        decay_mult = 1.0-((engine.current_time()-self.kb_time)/self.kb_decay_rate)
        if engine.current_time()-self.kb_time < self.kb_decay_rate:
            kbx = self.knockback[0]*decay_mult
            kby = velocity[1]
            engine.set_rigid_body_velocity(self.rb, (kbx, kby))

        # normal logic
        velocity = engine.get_rigid_body_velocity(self.rb)
        direction = 0
        if engine.key_is_pressed("Left"):
            direction += -1*self.slide_left
        if engine.key_is_pressed("Right"):
            direction += 1*self.slide_right
        
        #print(direction)

        if velocity[0] < self.speed + 10.0 and velocity[0] > -self.speed - 10.0:
            engine.set_rigid_body_velocity(self.rb, (self.speed*direction,velocity[1]))
        else:
            pass
            #engine.apply_force(self.rb, 10.0*direction,0.0)
            #print("Shouldn't be called")

        if self.grounded:
            self.coyote_time = engine.current_time()
            self.grounded = False
        
        if engine.current_time()-self.slide_time>0.30:
            self.slide_left = 1
            self.slide_right = 1
            self.slide_time = 0.0
        
        if engine.current_time()-self.invincible_time>1 and self.invincible:
            self.invincible_time = 0.0
            self.invincible = False
