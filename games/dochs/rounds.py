import engine #type: ignore
from enemy import Enemy
from platform import Platform
from waves import Wave
from spike import Spike

class Round:
    current_wave = 0
    finished = False
    started = False
    def __init__(self,version,spike_callback):
        self.platforms = []
        self.spikes = []
        self.version = version
        self.spike_callback = spike_callback

    def start(self):
            match(self.version):
                case 0:
                    self.platforms = [Platform(250,300,100,10)]
                    self.waves = [Wave(0), Wave(1), Wave(2)]
                    self.spikes = []
                case 1:
                    self.platforms = [Platform(150,300,100,10),
                                      Platform(350,300,100,10),
                                      Platform(250,200,100,10),]
                    self.waves = [Wave(0), Wave(1)]
                    self.spikes = [Spike(10,10,10,390,1,0,self.spike_callback),
                                   Spike(590,10,10,390,-1,0,self.spike_callback),]

    def start_wave(self):
        self.waves[self.current_wave].start()
        self.started = True
    
    def start_spikes(self):
        for s in self.spikes:
            s.set_trigger(True)
    

    def jiggle(self):
        for plat in self.platforms:
            plat.jiggle()
        for spike in self.spikes:
            spike.jiggle()

    def free_round(self):
        for plat in self.platforms:
            engine.free_rigid_body(plat.rb)
        for s in self.spikes:
            engine.free_box_collider(s.box)

    def update(self):
        if self.started:
            self.waves[self.current_wave].update()
            if self.waves[self.current_wave].finished:
                
                self.waves[self.current_wave].free_wave()
                self.current_wave+=1
                if self.current_wave >= len(self.waves):
                    print(f"Round {self.version}: Finished")
                    self.finished = True
                    self.current_wave -=1
                    
                    return
                print(f"Round {self.version}: Starting next wave")
                self.start_wave()
    
    def draw(self):
        #print("drawing round", self.version)
        if self.started and not self.finished:
            self.waves[self.current_wave].draw()
        for p in self.platforms:
            p.draw()
        for s in self.spikes:
            s.draw()

    def find_enemy(self,rb) -> Enemy:
        return self.waves[self.current_wave].find_enemy(rb)

    def find_spike(self,box) -> Spike:
        for spike in self.spikes:
            if spike.box == box:
                return spike
        return None