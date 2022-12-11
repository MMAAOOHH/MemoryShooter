# MemoryShooter
Small 2d Space Shooter done with SDL 

### Performance focus / Data-orientation in the project:   
ECS, components just being structs of data, systems transforming the data  
Continous profiling throughout the project, trying to reduce unnecessary jumps around in memory.  
Each system only gathering the data it needs  
Collisions split up between Broad and Narrow-phase reducing amount of collision checks  



TODO:  
enemies  
spawn waves    
weapons  
clean up input  
