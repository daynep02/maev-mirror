import engine

class Player:
    grounded = False
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
        if self.jumping:
            if engine.current_time()-self.jump_time > 0.5:
                self.jumping = False
            elif engine.key_is_pressed("Up"):
                engine.apply_force(self.rb, 0.0, -0.5)

        if engine.key_is_pressed("Up") and not self.jumping and self.grounded:
            engine.set_rigid_body_velocity(self.rb, (0.0, -300.0))
            self.jumping = True
            self.grounded = False
            self.jump_time = engine.current_time()

        if engine.key_is_pressed("Left"):
            engine.apply_force(self.rb,-1.0, 0.0)
        if engine.key_is_pressed("Right"):
            engine.apply_force(self.rb, 1.0, 0.0)