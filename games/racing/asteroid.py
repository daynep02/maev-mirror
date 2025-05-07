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

            sprite_to_use = self.path + self.names[random.randint(0, 3)]

            self.position = (random.randint(0, max_x), random.randint(0, max_y))

            new_asteroid = self.Asteroid(sprite_to_use, self.position)

            self.asteroids.append(new_asteroid)
    
    def draw(self):
        for roid in self.asteroids:
            # just call the draw function for ever asteroid
            roid.draw()

    class Asteroid:
        def __init__(self, name: str, position: tuple):

            # create the sprite and get the id
            self.sprite :float = engine.create_sprite(name)

            # get the size of the sprite that was just loaded
            self.size: tuple = engine.get_sprite_size(self.sprite)


            # set the position to the randomized location
            engine.set_sprite_position(self.sprite, position)

            # create a rigid body at the same location
            self.rigid_body :float = engine.create_rigid_body(position, self.size)

            # make these static for now
            engine.set_rigid_body_static(self.rigid_body, True)

        def draw(self):
            engine.draw_sprite(self.sprite)
            pass