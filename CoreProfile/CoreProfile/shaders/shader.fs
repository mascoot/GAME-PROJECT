#version 330 core

uniform sampler2D texture;

in vec2 fragTexCoord;
out vec4 finalColor;

void main() 
{
    //note: the texture function was called texture2D in older versions of GLSL
    //finalColor = texture(texture, fragTexCoord);
	finalColor = vec4(1,0,0,1);
}