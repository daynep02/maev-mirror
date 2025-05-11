import engine # type: ignore

class Player:
    grounded = False
    coyote_time = 0.0
    jumping = False
    jump_time = 0.0
    def __init__(self):
        self.rb = engine.create_rigid_body((125,0),(25,25))
        print(f"creating player rigid: {self.rb}" )
        self.set_terminal_velo(0.0, 200.0)
        self.set_static(False)
        self.set_gravity(True)
    
    def set_gravity(self, x: bool) -> None:
        engine.set_rigid_body_gravity(self.rb, x)

    def set_static(self, x: bool) -> None:
        engine.set_rigid_body_static(self.rb, x)
    
    def draw(self) -> None:
        engine.draw_rigid_body_collider(self.rb)

    def set_terminal_velo(self, x: float, y: float) -> None:
        engine.set_terminal_velo(self.rb, x, y)

    def movement(self) -> None:
        # jumping logic
        velocity = engine.get_rigid_body_velocity(self.rb)
        if self.jumping:
            if engine.current_time()-self.jump_time > 0.5:
                self.jumping = False
            elif engine.key_is_pressed("Up"):
                engine.apply_force(self.rb, 0.0, -0.6)

        if engine.key_is_pressed("Up") and not self.jumping and (self.grounded or engine.current_time()-self.coyote_time<0.15):
            engine.set_rigid_body_velocity(self.rb, (velocity[0], -240.0))
            self.jumping = True
            self.grounded = False
            self.jump_time = engine.current_time()

        # normal logic
        velocity = engine.get_rigid_body_velocity(self.rb)
        direction = 0
        if engine.key_is_pressed("Left"):
            direction += -1
        if engine.key_is_pressed("Right"):
            direction += 1

        if velocity[0] < 110.0 and velocity[0] > -110.0:
            engine.set_rigid_body_velocity(self.rb, (100.0*direction,velocity[1]))
        else:
            engine.apply_force(self.rb, 1.0*direction,0.0)

        if self.grounded:
            self.coyote_time = engine.current_time()
            self.grounded = False