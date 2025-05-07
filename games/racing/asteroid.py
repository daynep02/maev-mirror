import engine
import random


class AsteroidList:

    path = "../assets/PixelSpaceRage/128px/"
    names = [
        "Asteroid 01_png_processed.png",
        "Asteroid 02_png_processed.png",
        "Asteroid 03_png_processed.png",
        "Asteroid 04_png_processed.png"
    ]

    asteroids = []

    def __init__(self, max_x, max_y):
        for i in range(random.randint(0, 20)):
            #sprit_to_use = self.path + self.names[random.randint(0, 3)]

            sprite_to_use = self.path + "Asteroid_01_png_processed.png",
            self.asteroids.append(self.Asteroid(sprite_to_use))
            pass
    
    def draw(self):
        for roid in self.asteroids:
            roid.draw()

    class Asteroid:
        def __init__(self, name):
            self.sprite = engine.create_sprite(name)
            return

        def draw(self):
            pass