import engine #type: ignore
from platform import Platform
from enemy import Enemy
from rounds import Round
from layers import Layer

PAST = 0
PRESENT = 1
TRANSITION = 2
FUTURE = 3
GAME_OVER = 4

class Arena:
    start_time = 0.0
    started = False
    state = PAST

    # rounds
    previous_round = -1
    current_round = -1
    
    def __init__(self, player, start_callback, win_callback, spike_callback):
        self.player = player
        #The platform to collide with
        self.platforms = [Platform(0,400,610,20), # bottom platform
                          Platform(0,0,610,20), # bottom platform
                          Platform(0,0,10,300), # left platform
                          Platform(600,0,10,300), # right platform
                          Platform(610,400,200,20)] # win platform
        
        self.left_gate = Platform(-5,200,10,100)
        self.right_gate = Platform(605,300,10,100)
        self.gate_movement = 100

        self.square_queen = engine.create_rect((25,25))
        engine.set_rect_position(self.square_queen, (325,375))
        engine.set_rect_fill_color(self.square_queen, (255,192,203,255))

        self.start_trigger = engine.create_box_collider((250,300),(100,100))
        engine.set_box_callback(self.start_trigger,start_callback)
        engine.set_box_layer(self.start_trigger, Layer.TRIGGER)
        self.win_trigger = engine.create_box_collider((710,300),(100,100))
        engine.set_box_callback(self.win_trigger,win_callback)
        engine.set_box_layer(self.win_trigger, Layer.TRIGGER)

        self.rounds = [Round(0,spike_callback), Round(1,spike_callback)]
        
    def update(self):
        if self.player.dead:
            self.state = GAME_OVER
        if self.state == PAST:
            if self.started:
                if engine.current_time()-self.start_time > 1.0:
                    print("Rounds Start!")
                    self.state = TRANSITION
                    self.current_round = 0
                    self.start_time = engine.current_time()
        elif self.state == PRESENT:
            #update rounds
            self.rounds[self.current_round].update()
            if self.rounds[self.current_round].finished:
                # transition to round
                print("Going to next round")
                self.state = TRANSITION
                self.previous_round = self.current_round
                self.current_round+=1
                self.player.heal(3)
                self.start_time = engine.current_time()
                if self.current_round >= len(self.rounds):
                    self.state = FUTURE
                    engine.set_box_trigger(self.win_trigger,True)
                    self.rounds[self.previous_round].free_round()
                    return
                self.rounds[self.current_round].start()
        elif self.state == TRANSITION:
            if self.current_round == 0:
                # shut gate
                if engine.current_time() - self.start_time > 0.5:
                    self.left_gate.set_position(-5, 300)
                    self.state = PRESENT
                    self.rounds[self.current_round].start()
                    self.rounds[self.current_round].start_wave()
                else:
                    percent = 1-(0.5-(engine.current_time() - self.start_time))/0.5
                    #print(percent)
                    self.left_gate.set_position(-5, 200+(self.gate_movement*percent))
                return

            # wait for a bit then start wave, and swap back to state PRESENT
            if engine.current_time() - self.start_time > 2.0:
                self.state = PRESENT
                self.rounds[self.previous_round].free_round()
                self.rounds[self.current_round].start_wave()
                self.rounds[self.current_round].start_spikes()
            else:
                # jitter previous platforms
                self.rounds[self.previous_round].jiggle()
                pass
            
        elif self.state == FUTURE:
            # open gate
            if engine.current_time() - self.start_time > 0.5:
                self.right_gate.set_position(605, 200)
                #print("All rounds complete")
            else:
                percent = 1-(0.5-(engine.current_time() - self.start_time))/0.5
                #print(percent)
                self.right_gate.set_position(605, 300-(self.gate_movement*percent))
        elif self.state == GAME_OVER:
            print("Player Died")
            
    def draw(self):
        #draw platforms
        #print("drawing arena")
        for plat in self.platforms:
            plat.draw()

        self.left_gate.draw()
        self.right_gate.draw()
        #engine.draw_box(self.win_trigger)
        engine.draw_rect(self.square_queen)

        if self.state == PAST:
            if not self.started:
                #engine.draw_box(self.start_trigger)
                pass
        elif self.state == PRESENT:
            self.rounds[self.current_round].draw()
        elif self.state == TRANSITION:
            if self.current_round > 0:
                self.rounds[self.current_round].draw()
                self.rounds[self.previous_round].draw()
    
    def free(self):
        for plat in self.platforms:
            plat.free()

        self.left_gate.free()
        self.right_gate.free()
        engine.free_box_collider(self.win_trigger)

    def start(self):
        print("Arena Started!")
        self.started = True
        self.start_time = engine.current_time()
        engine.free_box_collider(self.start_trigger)
        engine.set_rect_position(self.square_queen,(785,375))
        self.win_trigger = engine.create_box_collider((710,300),(100,100))

    def deal_damage_to_enemy(self,rb,dmg,dx,dy):
        # send search to current_round
        enemy = self.rounds[self.current_round].find_enemy(rb)
        enemy.take_damage(dmg, dx, dy)

    def get_enemy_damage(self,rb):
        # send search to current_round
        enemy = self.rounds[self.current_round].find_enemy(rb)
        return enemy.damage

    def find_spike(self, box):
        s = self.rounds[self.current_round].find_spike(box)
        if s == None:
            s = self.rounds[self.previous_round].find_spike(box)
        return s