import engine
import random


class AsteroidList:

    path = "../games/racing/assets/PixelSpaceRage/128px/" 
    names = [
        "Asteroid_01_png_processed.png",
        "Asteroid_02_png_processed.png",
        "Asteroid_03_png_processed.png",
        "Asteroid_04_png_processed.png"
    ]

    asteroids = []

    def __init__(self, max_x, max_y):
        # randomly create up to 20 asteroids
        for i in range(random.randint(0, 20)):
            self.add((10, 10), (max_x, max_y))

    
    def draw(self):
        for roid in self.asteroids:
            # just call the draw function for every asteroid
            roid.draw()

    def update(self):
        for roid in self.asteroids:
            roid.update()


    def add(self, min_position: tuple, max_position: tuple):

        sprite_to_use = self.path + self.names[random.randint(0, 3)]

        position = (random.randint(min_position[0], max_position[0]), random.randint(min_position[1], max_position[1]))

        new_asteroid = self.Asteroid(sprite_to_use, position)

        self.asteroids.append(new_asteroid)


    class Asteroid:
        def __init__(self, name: str, position: tuple):

            # keep track of the position here so it can be changed later
            self.positon = position

            # create the sprite and get the id
            self.sprite :float = engine.create_sprite(name)

            # get the size of the sprite that was just loaded
            self.size: tuple = engine.get_sprite_size(self.sprite)


            # set the position to the randomized location
            engine.set_sprite_position(self.sprite, position)

            # create a rigid body at the same location
            self.rigid_body :float = engine.create_rigid_body(position, self.size)

            engine.set_rigid_body_velocity(self.rigid_body, (1.0, 100.0))




        def draw(self):
            engine.draw_sprite(self.sprite)
            pass

        def update(self):

            self.position = engine.get_rigid_body_position(self.rigid_body)

            engine.set_sprite_position(self.sprite, self.position)

            pass
