import engine
import random


class AsteroidList:

    startVelocity = 1.0

    path :str = "../games/racing/assets/PixelSpaceRage/128px/" 

    names :list = [
        "Asteroid_01_png_processed.png",
        "Asteroid_02_png_processed.png",
        "Asteroid_03_png_processed.png",
        "Asteroid_04_png_processed.png"
    ]

    asteroids :list = []

    def __init__(self, min_x, min_y, max_x, max_y):
        # randomly create up to 20 asteroids
        self.min_y = min_y
        self.min_x = min_x

        self.max_y = max_y
        self.max_x = max_x

        engine.set_collision_layer_value(1, 1, False)

        self.roid_interval :int = 5
        self.new_roid_timer :int = self.roid_interval

    
    def draw(self):
        for roid in self.asteroids:
            # just call the draw function for every asteroid
            roid.draw()

    def update(self):
        self.startVelocity += 1

        self.new_roid_timer -= 1

        for i, roid in enumerate(self.asteroids):
            roid.update()
            if roid.position[1] > self.max_y:
                self.remove(i)

        if len(self.asteroids) < 100 and self.new_roid_timer <= 0:
            self.add()
                


    def add(self):
        self.new_roid_timer = self.roid_interval
        sprite_to_use = self.path + self.names[random.randint(0, 3)]

        position = (random.uniform(self.min_x, self.max_x), self.min_y - 20)

        new_asteroid = self.Asteroid(sprite_to_use, position, self.startVelocity)
        self.asteroids.append(new_asteroid)

    def remove(self, place: int):
        roid = self.asteroids[place]
        engine.free_rigid_body(roid.rigid_body)
        engine.free_sprite(roid.sprite)
        del self.asteroids[place]



    class Asteroid:

        def __init__(self, name: str, position: tuple, fall_velocity: float):
            
            # keep track of the position here so it can be changed later
            self.positon = position

            # create the sprite and get the id
            self.sprite :int = engine.create_sprite(name)

            # get the size of the sprite that was just loaded
            self.size: tuple = engine.get_sprite_size(self.sprite)

            # set the position to the randomized location
            engine.set_sprite_position(self.sprite, position)

            # create a rigid body at the same location
            self.rigid_body :int = engine.create_rigid_body(position, self.size)

            engine.set_rigid_body_velocity(self.rigid_body, (0.0, fall_velocity))

            engine.set_rigid_body_layer(self.rigid_body, 1)

            engine.set_rigid_body_velocity(self.rigid_body, (1.0, 100.0))




        def draw(self):
            engine.draw_sprite(self.sprite)
            pass

        def update(self):


            self.position = engine.get_rigid_body_position(self.rigid_body)

            engine.set_sprite_position(self.sprite, self.position)
            pass
