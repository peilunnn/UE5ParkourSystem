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