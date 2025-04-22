Assignment 1 of Computer Graphics - Augusto Pagnossim Frigo

Implementations

- Insert/delete figure
- Figure color
- Edit figure size (via linear transformation)
- Edit figure orientation (via linear transformation)
- Send to front/back (via figure selection)
- Save to file and load from file

Extras

- Insertion of irregular figures with the mouse (can be any figure, points will be in the order you click on the scene)
- Insertion of any regular figure based on the circle equation, not limited to squares, triangles, circles, etc.
- Color palette (not very complex but looks nice)
- Collision detection for any irregular figures
- Graham's convex hull algorithm (reduce button)
- Indicate which figure is selected (turns yellow)
- Rotate the figure at any angle (via linear transformation) - The matrix button captures keyboard input, working for numbers and trigonometric functions ("-cos(1.57)", "sin(1.57)" "-4.32", "6.73")
- Concatenation of transformation matrices - Transformation matrices are stored in a stack and later applied in reverse order
- Concatenate two figures (Concatenates the points and applies Graham's convex hull to generate the new figure)
- Fill any figure - the description mentions circle, triangle, etc., but mine works for bizarre figures with multiple strokes (depends somewhat on how the algorithm understands what is "inside the figure" in these cases)
- Fill any figure with BMP image (the image doesn't scale with the figure, but is only rendered inside it)
- Apply encryption to the file (Caesar cipher)
- Panel with label for each figure (Figures are shown in selection order, with a limit of 10)
- Red, green, blue, and grayscale filters for BMP image
- Color inversion for BMP image
- BMP image histogram

Usage Instructions

Click on any color in the color palette. This will make your next drawing appear in that color. You need to click a color before drawing, unless you want an invisible polygon.

Buttons:
!regular - Starts creating an irregular figure - The next points you click will be added sequentially to form the figure. Press enter to finish creation.
bmp - Inserts a BMP figure inside the currently selected figure (it is rendered from the center of the figure, if it's too wide at the edges and narrow in the center, it may render little)
save - saves the figures (as they are currently being rendered, but without saving the fill and BMP image)
NOTE: The save stores the figures on disk as they are, so if you save a figure and then read it, the transformed figure will become the original.
read - clears the current list of figures and reads a file with previously saved figures.
regular - Inserts a new regular figure - note that there are keyboard buttons to control the parameters for generating this figure.
concat - Concatenates 2 figures, applying the convex hull to generate the smallest possible polygon from them (by implementation decision, they are concatenated from where they are) (does nothing if there are less than 2 figures)
delete - deletes the selected figure
fill - fills the selected figure

-- Linear Transformations --

To perform a linear transformation, use the matrix to the right of the buttons. It is pre-filled with the identity matrix. Click on the fields and edit them to add numbers to the transformation. The matrix supports trigonometric functions "sin(num)", "-sin(num), "cos(num)", "-cos(num)" and real numbers, as long as num follows a readable pattern ("-3.1415", "3.1415", "3", "-3"). The numbers in trigonometric functions are received in degrees.
After filling the matrix with the desired numbers, click "add". This will add the matrix to the transformation matrix stack. You can add as many matrices as you want, they will be concatenated (multiplied) in reverse order, so that the transformation can be applied to the image. That is, if you want to apply a rotation and then a scale, put the rotation matrix first and then the scale matrix. Transformations are always applied to the original points, never to the transformed ones. If you want to apply successive transformations, just concatenate the matrices.

Reduce: The reduce button serves to apply the convex hull algorithm to obtain the smallest possible polygon. Note that reduce is applied to the original figure, but when transforming, it's possible to obtain a transformation on the polygon made by the algorithm. That is, if you want to apply the convex hull algorithm, use the reduce button and then apply the linear transformation. The order (transformation -> convexHull / convexHull -> transformation) doesn't matter because there is no translation support. When "unapplying" the convex hull algorithm by clicking reduce again, the original figure will be restored.

Keyboard: (letters must be without caps lock)
u: Increases the number of vertices of the regular figure
j: Decreases the number of vertices of the regular figure
i: Increases the x radius of the regular figure by 50
k: Decreases the x radius of the regular figure by 50
o: Increases the y radius of the regular figure by 50
l: Decreases the y radius of the regular figure by 50
c: increases the number of vertices of the regular figure to 1000 (to approximate a circle)
p: restores the number of vertices of the regular figure to 5
enter: finishes the creation of the irregular figure

Keyboard (for bitmap figure manipulation - BMP must be loaded in the selected figure to work)

r: puts the figure in red scale
g: puts the figure in green scale
b: puts the figure in blue scale
v: puts the figure in grayscale
f: inverts the colors of the figure

Note: linear transformations are NOT applied to the BMP, but it adapts to the rendering of the new figure (that is, it doesn't go beyond the borders)