import engine #type: ignore
from enemy import Enemy

class Wave:
    finished = False
    def __init__(self,version):
        self.enemies = []
        self.version = version

    def start(self):
            print("Starting wave", self.version)
            match(self.version):
                case 0:
                    self.enemies = [Enemy(400,50)]
                case 1:
                    self.enemies = [Enemy(400,50),Enemy(200,50)]
                case 2:
                    self.enemies = [Enemy(400,50),Enemy(200,50)]

    def free_wave(self):
        for e in self.enemies:
            e.free()

    def update(self):
        num_alive = 0
        for e in self.enemies:
            e.update()
            if not e.dead:
                num_alive +=1
        if num_alive == 0:
            print("all enemies dead, going to next wave")
            self.finished = True
    
    def draw(self):
        #print("drawing wave", self.version)
        if not self.finished:
            for e in self.enemies:
                e.draw()

    def find_enemy(self,rb) -> Enemy:
        for e in self.enemies:
            if e.rb == rb:
                return e
        return None