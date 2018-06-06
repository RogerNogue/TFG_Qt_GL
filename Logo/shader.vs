#version 330
in vec4 vertex;
out float oBSx;
out float oBSy;
out float oBSz;
out float vRPx;
out float vRPy;
out float vRPz;
out float uPx;
out float uPy;
out float uPz;
out float fovy;
out float aspect;
out float znear;
out float zfar;
out float widthpixels;
out float heightpixels;
out float time;
out float intLlumX;
out float intLlumY;
out float intLlumZ;

uniform float oBSxu;
uniform float oBSyu;
uniform float oBSzu;
uniform float vRPxu;
uniform float vRPyu;
uniform float vRPzu;
uniform float uPxu;
uniform float uPyu;
uniform float uPzu;
uniform float fovyu;
uniform float aspectu;
uniform float znearu;
uniform float zfaru;
uniform float widthpixelsu;
uniform float heightpixelsu;
uniform float timeu;
uniform float intLlumXu;
uniform float intLlumYu;
uniform float intLlumZu;

void main()
{
	oBSx = oBSxu;
	oBSy = oBSyu;
	oBSz = oBSzu;

	vRPx = vRPxu;
	vRPy = vRPyu;
	vRPz = vRPzu;

	uPx = uPxu;
	uPy = uPyu;
	uPz = uPzu;

	fovy = fovyu;
	aspect = aspectu;
	znear = znearu;
	zfar = zfaru;
	widthpixels = widthpixelsu;
	heightpixels = heightpixelsu;
	time = timeu;

	intLlumX = intLlumXu;
	intLlumY = intLlumYu;
	intLlumZ = intLlumZu;

    gl_Position = vec4(vertex.x, vertex.y, vertex.z, 1.0);
}