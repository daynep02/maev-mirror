import engine # type: ignore
from player import Player
from title import Title
from particles import ParticleHandler
from layers import Layer

from tutorial import Tutorial
from arena import Arena

class Game:
    def __init__(self):
        self.player = Player(on_hitbox_collision)
        engine.set_rigid_body_callback(self.player.rb,on_player_collision)
        #self.enemy = Enemy()

        # particle handler
        self.p_handler = ParticleHandler()

        # starting camera
        self.set_camera_size(600,400)
        engine.set_camera_position(engine.get_rigid_body_position(self.player.rb))

        self.tutorial = Tutorial(self.player, on_spike_collision,on_tutorial_start)

        self.arena = Arena(self.player, on_arena_start, on_arena_win, on_spike_collision)

        self.music = engine.create_music("../games/dochs/assets/ai.ogg")
        

        engine.set_gravity(0.0, 1463.0) # 2.48 before delta, 1463.0? after
    
    def update_game(self):
        #global my_list
        #print(f"delta: {engine.delta_time()}, gravity {0.62*4}, should be {engine.delta_time()*1000}")
        #my_list.append(engine.delta_time())
        engine.set_camera_position(engine.get_rigid_body_position(self.player.rb))
        self.player.update()
        self.tutorial.update()
        self.arena.update()
        self.p_handler.update()
    
    def draw_game(self):
        self.player.draw()
        self.tutorial.draw()
        self.arena.draw()
        self.p_handler.draw()
        
    def free_game(self):
        self.player.free()
        self.arena.free()

    def set_camera_size(self, width, height):
        engine.set_camera_size((width,height))

game = None
title = None
state = 0
game_over = None
game_won = None
button_cooldown = 0.0
happy = None

# Key Functions for Game
def init():
    global title, game_over, game_won, happy

    # collision layer settings
    engine.set_collision_layer_value(Layer.PLATFORM,Layer.PLATFORM,False)
    engine.set_collision_layer_value(Layer.ENEMY,Layer.ENEMY,False)
    engine.set_collision_layer_value(Layer.TRIGGER,Layer.PLATFORM, False)
    engine.set_collision_layer_value(Layer.TRIGGER,Layer.TRIGGER, False)
    engine.set_collision_layer_value(Layer.TRIGGER,Layer.SPIKE, False)
    engine.set_collision_layer_value(Layer.DEAD,Layer.DEAD, False)
    engine.set_collision_layer_value(Layer.DEAD,Layer.PLAYER, False)
    engine.set_collision_layer_value(Layer.DEAD,Layer.ENEMY, False)
    engine.set_collision_layer_value(Layer.DEAD,Layer.SPIKE, False)
    engine.set_collision_layer_value(Layer.SPIKE,Layer.PLATFORM, False)
    engine.set_collision_layer_value(Layer.SPIKE,Layer.TRIGGER, False)
    engine.set_collision_layer_value(Layer.SPIKE,Layer.SPIKE, False)
    engine.print_collision_layer_matrix()
    
    engine.set_on_close(on_close)
    engine.set_framerate_limit(240)
    
    happy = engine.create_music("../games/dochs/assets/boogie.ogg")
    engine.play_music(happy)

    title = Title(0)
    game_over = Title(1)
    game_won = Title(2)

def update():
    global game, title, state, game_over, game_won, button_cooldown, happy

    if state == 0:
        title.update_title()
        if engine.current_time() - button_cooldown > 1.0:
            if engine.key_is_pressed("E") or engine.key_is_pressed("ENTER"):
                if title.state == 0:
                    game = Game()
                    engine.pause_music(happy)
                    state = 1
                elif title.state == 1:
                    pass
                elif title.state == 2:
                    engine.exit()
    elif state == 1:
        game.update_game()
        if game.arena.state == 4:
            print("game swapping to game over")
            state = 2
            game.free_game()
    elif state == 2:
        game_over.update_title()
        if engine.current_time() - button_cooldown > 1.0:
            if engine.key_is_pressed("E") or engine.key_is_pressed("ENTER"):
                if game_over.state == 0:
                    game = Game()
                    state = 1
                elif game_over.state == 1:
                    state = 0
                    button_cooldown = engine.current_time()
                    engine.play_music(happy)
    elif state == 3:
        game_won.update_title()
        if engine.current_time() - button_cooldown > 1.0:
            if engine.key_is_pressed("E") or engine.key_is_pressed("ENTER"):
                if game_won.state == 0:
                    state = 0
                    button_cooldown = engine.current_time()

def draw():
    global game, title, state, game_over, game_won

    if state == 0:
        title.draw_title()
    if state == 1:
        game.draw_game()
    if state == 2:
        game_over.draw_title()
    if state == 3:
        game_won.draw_title()

def on_close():
    #print("Averge delta: ", (sum(my_list) / len(my_list)))
    print("\"Window closed\", said the Python!")

def on_player_collision(player_rb,collider_rb):
    global game
    p_pos = engine.get_rigid_body_position(player_rb)

    if engine.get_rigid_body_layer(collider_rb) == Layer.PLATFORM:
        plat_pos = engine.get_rigid_body_position(collider_rb)
        plat_size = engine.get_rigid_body_size(collider_rb)
        if p_pos[1]+23.0 < plat_pos[1]:
            game.player.grounded = True
        elif p_pos[1] > plat_pos[1]+plat_size[1]-2:
            # headbump
            # print("headbump")
            velocity = engine.get_rigid_body_velocity(player_rb)
            engine.set_rigid_body_velocity(player_rb, (velocity[0],10.0))
            game.player.jumping = False


    if engine.get_rigid_body_layer(collider_rb) == Layer.ENEMY and not game.player.invincible:
        e_pos = engine.get_rigid_body_position(collider_rb)
        px = p_pos[0] - e_pos[0]
        py = p_pos[1] - e_pos[1]
        
        direction = engine.normalize(engine.create_vector(px, py))
        damage = 0
        if collider_rb == game.tutorial.enemy.rb:
            damage = game.tutorial.enemy.damage
        else:
            damage = game.arena.get_enemy_damage(collider_rb)
        game.player.take_damage(damage, 500.0*engine.x(direction), 500.0*engine.y(direction))
        #print(direction)

        engine.cleanse_vectors()

def on_hitbox_collision(hit_bc,collider_rb):
    global game
    clayer = engine.get_rigid_body_layer(collider_rb)
    if clayer == Layer.ENEMY or clayer == Layer.DEAD:
        if collider_rb not in game.player.boxes_hit:
            #print(f"hit {hit_bc} collided with {collider_rb} with direction {game.player.attack_direction}")
            game.player.boxes_hit.append(collider_rb)
            # launch player
            game.player.launch(200.0*game.player.attack_direction[0]*-1, 400.0*game.player.attack_direction[1]*-1,0.1)
            # launch enemy
            #game.enemy.take_damage(game.player.damage, game.player.attack_direction[0], game.player.attack_direction[1])
            if collider_rb == game.tutorial.enemy.rb:
                game.tutorial.enemy.take_damage(game.player.damage,game.player.attack_direction[0], game.player.attack_direction[1])
            else:
                game.arena.deal_damage_to_enemy(collider_rb,game.player.damage,game.player.attack_direction[0], game.player.attack_direction[1])

            # start particles
            sposx, sposy = engine.get_rigid_body_position(collider_rb)
            game.p_handler.spawn_classic(sposx, sposy)
    

def on_spike_collision(spike_box,collider_rb):
    global game

    if spike_box == game.tutorial.spikes[0].box:
        s = game.tutorial.spikes[0]
        if collider_rb == game.tutorial.enemy.rb:
            print("enemy hit tutorial spike")
            game.tutorial.enemy.take_damage(5,s.kd[0],s.kd[1])
            return
        
    else:
        s = game.arena.find_spike(spike_box)
    clayer = engine.get_rigid_body_layer(collider_rb)
    if clayer == Layer.PLAYER and not game.player.invincible:
        game.player.take_damage(3, 400.0*s.kd[0], 400.0*s.kd[1])
    elif clayer == Layer.ENEMY:
        game.arena.deal_damage_to_enemy(collider_rb,5,s.kd[0], s.kd[1])
        # start particles
        sposx, sposy = engine.get_rigid_body_position(collider_rb)
        game.p_handler.spawn_classic(sposx, sposy)

def on_tutorial_start(start_box,player_rb):
    global game
    print("Arena Start callback")
    if engine.get_rigid_body_layer(player_rb) == Layer.PLAYER:
        game.tutorial.trigger_hit = True
        game.tutorial.spikes[0].set_trigger(True)
        engine.set_box_trigger(game.tutorial.spike_t,False)

def on_arena_start(start_box,player_rb):
    global game
    print("Arena Start callback")
    if engine.get_rigid_body_layer(player_rb) == Layer.PLAYER:
        game.arena.start()
        engine.play_music(game.music)

def on_arena_win(win_box, player_rb):
    global game, state, happy
    print("game won!")
    if engine.get_rigid_body_layer(player_rb) == Layer.PLAYER:
        game.free_game()
        state = 3
        engine.pause_music(game.music)
        engine.play_music(happy)
