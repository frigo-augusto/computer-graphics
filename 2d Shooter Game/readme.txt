Assignment 3 of CG (Computer Graphics)
Augusto Pagnossim Frigo
Everything specified was implemented and there are no known bugs.
Extra: Curved projectile trajectory (the projectile is not destroyed when hitting the enemy, it just stops updating the end point and continues its trajectory beyond t = 1).
Background loop with bitmap

Instructions
p: disable background (increases fps)
wasd: controls the square
mouse: moves the crosshair
mouse click: shoots
space: curved trajectory shot
Note: The curved trajectory shot has the nearest enemy as its final destination, and this destination is updated as the enemy moves (unlike all other projectiles)