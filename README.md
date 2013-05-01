PixelStencil
============

Create laser cut models for spray paint stencils from pixel graphics

For each color found in the input image own svg file is generated and each pixel is converted into a rectangle.
 
Usage: pixelStencil <img file> <pixel width mm> <pixel margin mm> <board margin mm> 

Running ./pixelStencil images/smb.png 20 5 20 on following image:


Generates following svg files:
