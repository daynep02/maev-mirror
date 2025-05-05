import engine

class ControlBlock:
    controlled = True

    def __init__(self, min_x: float, min_y: float, size_x: float, size_y: float) -> None:
        self.id = engine.create_rigid_body((min_x, min_y), (size_x, size_y))
        self.velocity = engine.get_rigid_body_velocity(self.id)
        self.size = (size_x, size_y)
        self.max_x = 100
        self.max_y = 100
        print(type(self.velocity))
    
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
        return

    def controlledUpdate(self) -> None:

        position = self.get_position()

        if self.velocity[1] > -self.max_y and engine.key_is_pressed("Up"):
            engine.apply_force(self.id, 0.0, -1.0)

        if self.velocity[1] < self.max_y and engine.key_is_pressed( "Down"):
            engine.apply_force(self.id, 0.0, 1.0)

        if self.velocity[0] > -self.max_x and engine.key_is_pressed("Left"):
            engine.apply_force(self.id,-1.0, 0.0)

        if  self.velocity[0] < self.max_x and engine.key_is_pressed("Right"):
            engine.apply_force(self.id, 1.0, 0.0)

        if position[0] < 0:
            engine.set_rigid_body_position(self.id, (0, position[1]))

        if position[0] > 400:
            engine.set_rigid_body_position(self.id, (400, position[1])

        if position[1] < 0:
            engine.set_rigid_body_position(self.id, (position[0], 0))

        if position[1] > 400:
            engine.set_rigid_body_position(self.id, (position[0], 400))

        return

    def update(self) -> None:
        self.update_velo()
        if self.controlled: self.controlledUpdate()

        self.uncontrolledUpdate()
        return

    def draw(self) -> None:
        engine.draw_rigid_body_collider(self.id)
