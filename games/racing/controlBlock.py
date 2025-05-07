import engine

class ControlBlock:
    controlled = True
    sprite = None

    def __init__(self, min_x: float, min_y: float, size_x: float, size_y: float, sprite = None) -> None:

        self.position = (min_x, min_y)
        self.size = (size_x, size_y)

        self.id = engine.create_rigid_body(self.position, self.size)
        self.velocity = engine.get_rigid_body_velocity(self.id)

        self.max_x = 100
        self.max_y = 100

        self.edge_x = 100
        self.edge_y = 100

        if sprite:
         #   print("Setting sprite")
            self.set_sprite(sprite)
         #   print("Sprite = ", self.sprite)
    
    def set_terminal_velo(self, x: float, y: float) -> None:
        engine.set_terminal_velo(self.id, x, y)

    def set_static(self, x: bool) -> None:
        engine.set_rigid_body_satic(self.id, x)

    def set_gravity(self, x: bool) -> None:
        engine.set_rigid_body_gravity(self.id, x)

    def get_position(self) -> tuple:
        return engine.get_rigid_body_position(self.id)

    def update_velo(self) -> None:
        self.velocity = engine.get_rigid_body_velocity(self.id)

    def set_terminal_velo(self, x: float, y: float) -> None:
        engine.set_terminal_velo(self.id, x, y)

    def uncontrolledUpdate(self) -> None:
        appliedx = 0.0
        appliedy = 0.0

        if self.velocity[0] > 0.0:
            appliedx = -1.0

        if self.velocity[0] < 0.0:
            appliedx = 1.0

        if self.velocity[1] > 0.0:
            appliedy = -1.0

        if self.velocity[1] < 0.0:
            appliedy = 1.0

        engine.apply_force(self.id, appliedx, appliedy)

        return

    def set_sprite(self, sprite_name: str) -> None:

        self.sprite = engine.create_sprite(sprite_name)
        sprite_size = engine.get_sprite_size(self.sprite)
        scale = (self.size[0] / sprite_size[0], self.size[1] / sprite_size[1])

        engine.set_sprite_scale(self.sprite, scale)
        engine.set_sprite_position(self.sprite, self.position)

    def controlledUpdate(self) -> None:
        if self.velocity[1] > -self.max_y and engine.key_is_pressed("Up"):
            engine.apply_force(self.id, 0.0, -5.0)

        if self.velocity[1] < self.max_y and engine.key_is_pressed( "Down"):
            engine.apply_force(self.id, 0.0, 5.0)

        if self.velocity[0] > -self.max_x and engine.key_is_pressed("Left"):
            engine.apply_force(self.id,-5.0, 0.0)

        if  self.velocity[0] < self.max_x and engine.key_is_pressed("Right"):
            engine.apply_force(self.id, 5.0, 0.0)

        if self.position[0] <= 0:
            engine.set_rigid_body_position(self.id, (0, self.position[1]))

        if self.position[0] + self.size[0] >= self.edge_x:
            engine.set_rigid_body_position(self.id, (self.edge_x - self.size[0], self.position[1]))

        if self.position[1] <= 0:
            engine.set_rigid_body_position(self.id, (self.position[0], 0))

        if self.position[1] + self.size[1] >= self.edge_y:
            engine.set_rigid_body_position(self.id, (self.position[0], self.max_y - self.size[1]))
        return


    def update(self) -> None:

        self.update_velo()

        self.position = self.get_position()

        if self.sprite is not None: engine.set_sprite_position(self.sprite, self.position)

        if self.controlled: self.controlledUpdate()

        self.uncontrolledUpdate()

        return

    def draw(self) -> None:

        if self.sprite is not None: 
            engine.draw_sprite(self.sprite)
            
        else:
            engine.draw_rigid_body_collider(self.id)
