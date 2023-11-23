# 3DViewer
Implementation of 3DViewer 

Part 1. 3DViewer
The program must provide the ability to:
Load a wireframe model from an obj file (vertices and surfaces list support only).
Translate the model by a given distance in relation to the X, Y, Z axes.
Rotate the model by a given angle relative to its X, Y, Z axes.
Scale the model by a given value.

GUI implementation, based on Qt

The graphical user interface must contain:

A button to select the model file and a field to output its name.
A visualisation area for the wireframe model.
Button/buttons and input fields for translating the model.
Button/buttons and input fields for rotating the model.
Button/buttons and input fields for scaling the model.
Information about the uploaded model - file name, number of vertices and edges.

Part 2. Bonus. Settings

The program must allow customizing the type of projection (parallel and central)
The program must allow setting up the type (solid, dashed)
The program must allow choosing the background color
Settings must be saved between program restarts

Part 3. Bonus. Record

The program must allow saving the captured (rendered) images as bmp and jpeg files.
The program must allow recording small screencasts by a special button - the current custom affine transformation of the loaded object into gif-animation (640x480, 10fps, 5s)
