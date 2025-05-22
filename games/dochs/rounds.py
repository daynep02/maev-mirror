import engine #type: ignore
from enemy import Enemy
from platform import Platform
from waves import Wave

class Round:
    current_wave = 0
    finished = False
    started = False
    def __init__(self,version):
        self.platforms = []
        self.version = version

    def start(self):
            match(self.version):
                case 0:
                    self.platforms = [Platform(300,300,100,10)]
                    self.waves = [Wave(0), Wave(1), Wave(2)]
                
            self.start_wave()

    def start_wave(self):
        self.waves[self.current_wave].start()
        self.started = True

    def free_round(self):
        for plat in self.platforms:
            engine.free_rigid_body(plat.rb)

    def update(self):
        if self.started:
            self.waves[self.current_wave].update()
            if self.waves[self.current_wave].finished:
                print("Starting next wave")
                self.waves[self.current_wave].free_wave()
                self.current_wave+=1
                if self.current_wave >= len(self.waves):
                    self.finished = True
                    self.current_wave -=1
                    return
                self.start_wave()

    
    def draw(self):
        #print("drawing round", self.version)
        self.waves[self.current_wave].draw()
        for p in self.platforms:
            p.draw()

    def find_enemy(self,rb) -> Enemy:
        return self.waves[self.current_wave].find_enemy(rb)