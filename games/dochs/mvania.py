import engine # type: ignore
import time
import math
from player import Player
from title import Title


class Game:
    def __init__(self):

        self.player = Player()
        engine.set_rigid_body_callback(self.player.rb,on_player_collision)

        self.set_camera_size(600,400)

        #The platform to collide with
        self.platform = engine.create_rigid_body((0,300),(500,20))
        engine.set_rigid_body_static(self.platform,True)

        engine.set_gravity(0.0, .62)
    
    def update_game(self):
        engine.set_camera_position(engine.get_rigid_body_position(self.player.rb))
        self.player.movement()
    
    def draw_game(self):
        self.player.draw()
        engine.draw_rigid_body_collider(self.platform)
    
    def set_camera_size(self, width, height):
        engine.set_camera_size((width,height))



game = None
title = None
state = 0

# Key Functions for Game
def init():
    global game, title, state

    engine.set_on_close(on_close)
    
    if state == 0:
        title = Title()
    if state == 1:
        game = Game()

def update():
    global game, title, state

    if state == 0:
        title.update_title()
        if engine.key_is_pressed("Enter") or engine.key_is_pressed("E"):
            if title.state == 0:
                game = Game()
                state = 1
            elif title.state == 1:
                pass
            elif title.state == 2:
                engine.exit()
    elif state == 1:
        game.update_game()

def draw():
    global game, title, state

    if state == 0:
        title.draw_title()
    if state == 1:
        game.draw_game()

def on_close():
    print("\"Window closed\", said the Python!")

def on_player_collision(player_rb,collider_rb):
    global game

    if collider_rb == game.platform:
        game.player.grounded = True