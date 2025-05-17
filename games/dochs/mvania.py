import engine # type: ignore
from player import Player
from enemy import Enemy
from title import Title

class Game:
    def __init__(self):

        self.player = Player()
        engine.set_rigid_body_callback(self.player.rb,on_player_collision)

        self.enemy = Enemy()

        self.set_camera_size(600,400)

        #The platform to collide with
        self.bottom_platform = engine.create_rigid_body((25,300),(700,20))
        engine.set_rigid_body_static(self.bottom_platform,True)
        engine.set_rigid_body_gravity(self.bottom_platform,False)

        #self.top_platform = engine.create_rigid_body((25,0),(500,20))
        #engine.set_rigid_body_static(self.top_platform,True)
        #engine.set_rigid_body_gravity(self.top_platform,False)
        self.left_platform = engine.create_rigid_body((20,10),(10,280))
        engine.set_rigid_body_static(self.left_platform,True)
        engine.set_rigid_body_gravity(self.left_platform,False)
        self.right_platform = engine.create_rigid_body((720,10),(10,280))
        engine.set_rigid_body_static(self.right_platform,True)
        engine.set_rigid_body_gravity(self.right_platform,False)

        engine.set_gravity(0.0, 0.62*4)
    
    def update_game(self):
        engine.set_camera_position(engine.get_rigid_body_position(self.player.rb))
        self.player.movement()
        self.enemy.update()
    
    def draw_game(self):
        self.player.draw()
        self.enemy.draw()

        #draw platforms
        engine.draw_rigid_body_collider(self.bottom_platform)
        #engine.draw_rigid_body_collider(self.top_platform)
        engine.draw_rigid_body_collider(self.left_platform)
        engine.draw_rigid_body_collider(self.right_platform)
    
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
        if engine.key_is_pressed("E") or engine.key_is_pressed("ENTER"):
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

    if collider_rb == game.bottom_platform:
        game.player.grounded = True
    elif collider_rb == game.left_platform:
        game.player.slide_left = 0
        game.player.slide_time = engine.current_time()
    elif collider_rb == game.right_platform:
        game.player.slide_right = 0
        game.player.slide_time = engine.current_time()

    if collider_rb == game.enemy.rb and not game.player.invincible:
        p_pos = engine.get_rigid_body_position(player_rb)
        e_pos = engine.get_rigid_body_position(collider_rb)
        px = p_pos[0] - e_pos[0]
        py = p_pos[1] - e_pos[1]
        
        direction = engine.normalize(engine.create_vector(px, py))
        game.player.take_damage(game.enemy.damage, 500.0*engine.x(direction), 500.0*engine.y(direction))
        print(direction)

        engine.cleanse_vectors()