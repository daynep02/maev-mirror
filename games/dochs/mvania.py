import engine # type: ignore
import time
import math
from player import Player


class Game:
    def __init__(self):

        self.player = Player()
        engine.set_rigid_body_callback(self.player.rb,on_player_collision)

        self.set_camera_size(600,400)

        #The platform to collide with
        self.platform = engine.create_rigid_body((0,300),(500,20))
        engine.set_rigid_body_static(self.platform,True)

        engine.set_gravity(0.0, .62)
    
    def set_camera_size(self, width, height):
        engine.set_camera_size((width,height))

def on_close():
    print("\"Window closed\", said the Python!")

game = None
first = True

# Key Functions for Game
def init():
    global game
    game = Game()
    engine.set_on_close(on_close)

def update():
    global game
    engine.set_camera_position(engine.get_rigid_body_position(game.player.rb))
    game.player.movement()


def draw():
    global game

    game.player.draw()
    engine.draw_rigid_body_collider(game.platform)

def on_player_collision(player_rb,collider_rb):
    global game
    if collider_rb == game.platform:
        game.player.grounded = True