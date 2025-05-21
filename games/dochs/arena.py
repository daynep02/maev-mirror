import engine #type: ignore
from platform import Platform
from enemy import Enemy
from rounds import Round

PAST = 0
PRESENT = 1
TRANSITION = 2
FUTURE = 3

class Arena:
    start_time = 0.0
    started = False
    state = PAST

    # rounds
    previous_round = -1
    current_round = -1
    
    
    def __init__(self, player, start_callback):
        self.player = player
        #The platform to collide with
        self.platforms = [Platform(0,400,610,20), # bottom platform
                          Platform(0,0,610,20), # bottom platform
                          Platform(0,0,10,300), # left platform
                          Platform(600,0,10,300)] # right platform
        
        self.left_gate = Platform(-5,200,10,100)
        self.right_gate = Platform(605,300,10,100)
        self.gate_movement = 100

        self.start_trigger = engine.create_box_collider((250,300),(100,100))
        engine.set_box_callback(self.start_trigger,start_callback)

        self.rounds = [Round(0)]
        
        
    def update(self):
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
                self.state = TRANSITION
                self.previous_round = self.current_round
                self.rounds[self.current_round].free_round()
                self.current_round+=1
                self.start_time = engine.current_time()
                if self.current_round >= len(self.rounds):
                    self.state = FUTURE
                    return
                self.rounds[self.current_round].start()
                
        elif self.state == TRANSITION:
            if self.current_round == 0:
                # shut gate
                if engine.current_time() - self.start_time > 0.5:
                    self.left_gate.set_position(-5, 300)
                    self.state = PRESENT
                    self.rounds[self.current_round].start()
                else:
                    percent = 1-(0.5-(engine.current_time() - self.start_time))/0.5
                    #print(percent)
                    self.left_gate.set_position(-5, 200+(100*percent))
            # jitter previous platforms
            pass
            # wait for a bit then start wave, and swap back to state PRESENT
        elif self.state == FUTURE:
            
            # open gate
            if engine.current_time() - self.start_time > 0.5:
                self.right_gate.set_position(605, 200)
                print("All rounds complete")
            else:
                percent = 1-(0.5-(engine.current_time() - self.start_time))/0.5
                #print(percent)
                self.right_gate.set_position(605, 300-(100*percent))
            

    def draw(self):
        #draw platforms
        #print("drawing arena")
        for plat in self.platforms:
            plat.draw()

        self.left_gate.draw()
        self.right_gate.draw()

        if self.state == PAST:
            if not self.started:
                engine.draw_box(self.start_trigger)
        elif self.state == PRESENT:
            self.rounds[self.current_round].draw()

    def start(self):
        print("Arena Started!")
        self.started = True
        self.start_time = engine.current_time()
        engine.free_box_collider(self.start_trigger)

    def deal_damage_to_enemy(self,rb,dmg,dx,dy):
        # send search to current_round
        enemy = self.rounds[self.current_round].find_enemy(rb)
        enemy.take_damage(dmg, dx, dy)

    def get_enemy_damage(self,rb):
        # send search to current_round
        enemy = self.rounds[self.current_round].find_enemy(rb)
        return enemy.damage