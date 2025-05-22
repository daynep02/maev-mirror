import engine

class Camera:
    def __init__(self, position_x: float, position_y: float, width: float, height: float):

        #engine.set_screen_size(width, height)
        self.w, self.h = engine.get_screen_width(), engine.get_screen_height()

        self.set_position((position_x, position_y))

        self.velocity = (0,0)

        self.set_size((width, height))

    def set_position(self, position: tuple) -> None:

        self.position = position

    def set_size(self, size: tuple) -> None:
        self.w = size[0]
        self.h = size[1]
        engine.set_camera_size(size)
        
    def get_size(self) -> tuple:

        return (self.w, self.h)

    def move(self, offset: tuple) -> None:
        self.position = (self.position[0] + offset[0], self.position[1] + offset[1])

    def update(self) -> None:
        engine.set_camera_position(self.position)


    def set_velocity(self, velo: tuple) -> None: 
        self.velocity = velo

    def get_position(self) -> tuple:
        return self.position


