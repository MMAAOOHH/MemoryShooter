# MemoryShooter
Small 2d Space Shooter done with SDL 

## Controls  
WASD/Arrow keys to move   
Space to shoot  
P - pause/unpause (Game's paused on startup)  

### Performance / Data oriented -practices in the project:   
ECS, components just being structs of data, systems transforming the data
Each system only gathering the data it needs  
Collisions split up between Broad and Narrow-phase reducing amount of collision checks 
Continous profiling throughout the project, trying to reduce unnecessary jumps around in memory.  
 
### Other topics researched:  
Cache coherence - SoA vs AoS  
Sparse set  
SIMD  

### Resources
ECS  
https://www.david-colson.com/2020/02/09/making-a-simple-ecs.html  
https://austinmorlan.com/posts/entity_component_system/  

DoD  
Data-Oriented Design book, https://www.dataorienteddesign.com/dodmain/  
Mike Acton, cpp-con, https://www.youtube.com/watch?v=rX0ItVEVjHc  
Casey Muratori, Handmade Hero, https://handmadehero.org/  

TODO:  
enemy variations  
spawn wave delays
spawn wave difference
scoring
win / lose state
powerups  
clean up
