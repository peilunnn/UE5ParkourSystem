# Thought Process
1. Check if surface is climbable
- Use capsule trace
- We may get multiple hit results

2. Check if we have reached a ledge after climbing
- Use line trace from eye height

3. Manage climbing state
- attemptClimbing (on key press)
- canStartClimbing
- isClimbing

4. Physics for climbing
    1. Process climbable surfaces
        1. (Average) location
        2. (Average) normal (for making sure the character is always parallel to the surface when climbing a straight wall)
    2. Handle climb movement
        1. Velocity
        2. Rotation
        3. Snapping character to the surface
                        
                |     P
                |    /
                |   /  
                |  /  
                | /   ________Projected OP (onto ComponentForward)
                O←______Surface Normal
                →______SnapVector
                |______________ ComponentForward


        O: character's location
        
        P: climbable surface location (exaggerated for visualization, it's actually directly to the right of O)

        Projected OP: distance from the character to the climbable surface, but only in the direction the character is currently facing or moving towards

        SnapVector: length of the projection in the opposite direction of the surface normal

    3. Handle up down left right movement when character is climbing and no longer on the ground
        1. Get necessary vectors using cross product w LHR
    
    4. Stop climbing at ledge
        1. Get necessary vectors using dot product

                A     B
                |    / 
                |   /  
                |  /  
                | /
                O

        OA: surface normal of flat ground
        
        OB: surface normal of ledge

        When angle between these two vectors is smaller than some angle, we need to stop climbing
        
        a ⋅ b = ∣a∣ × ∣b∣ × cos(θ)
        
        When a and b are unit vectors, a.b = cos(θ)
        
        θ = cos−1 (a⋅b)

    5. Check if floor reached (to exit climbing more naturally)
        1. Check if line trace downwards from character hit anything, and
        2. Character's speed must be in the downwards direction
    
    6. Check if ledge reached (to begin climb up animation)
        1. Check if line trace starting from above the character, into the wall, hit anything
        2. If it didn't, it means there is open air so we have reached a ledge, and from that trace end, check if line trace directly downwards hit anything

    6. Check can climb down from ledge
        1. Check if line trace starting from slightly in front of character, to directly downwards hit anything
        2. If it did, it means character is standing on a walkable surface, and from slightly forward of that trace end, check if line trace directly downwards hit anything